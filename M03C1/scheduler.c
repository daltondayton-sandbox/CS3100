#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Process structure
typedef struct {
  int pid;        // Process ID
  int active;     // 1 if the process is ready/active, 0 otherwise
  int arrival;    // Arrival time
  int total;      // Total CPU time required
  int remaining;  // Remaining CPU time
  int turnaround; // Turnaround time (computed when the process finishes)
} Process;

// Print table of processes
void print_table(Process proc[], int n) {
  int i;
  printf("PID\tActive\tArrival\tTotal\tRemain\tTurnaround\n");
  for (i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].active,
           proc[i].arrival, proc[i].total, proc[i].remaining,
           proc[i].turnaround);
  }
  printf("\n");
}

// Reset processes:
// Set remaining = total, turnaround = 0, and reset active flag
// Active becomes 1 only if the process arrived at time 0.
void reset_processes(Process proc[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    proc[i].remaining = proc[i].total;
    proc[i].turnaround = 0;
    if (proc[i].arrival == 0)
      proc[i].active = 1;
    else
      proc[i].active = 0;
  }
}

// Checks if all processes have finished (remaining CPU time <= 0)
int all_terminated(Process proc[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (proc[i].remaining > 0)
      return 0; // Found a process that still needs CPU time
  }
  return 1;
}

// Checks if there is at least one process available at time t
int available_process(Process proc[], int n, int t) {
  int i;
  for (i = 0; i < n; i++) {
    if (proc[i].active && proc[i].remaining > 0 && proc[i].arrival <= t)
      return 1;
  }
  return 0;
}

// Simulate scheduling algorithm
// 0 = FCFS, 1 = SJF, 2 = SRT
void simulate(Process proc[], int n, int algo, const char *algo_name) {
  int t = 0; // simulation time
  int current_running =
      -1; // index of currently running process (-1 means none)
  int i, chosen;
  int total_turnaround = 0;

  printf("----------\nRunning scheduling algorithm: %s\n", algo_name);

  // Run the simulation until all processes have finished
  while (!all_terminated(proc, n)) {
    // Activate any process whose arrival time is equal to the current time
    for (i = 0; i < n; i++) {
      if (proc[i].arrival == t) {
        proc[i].active = 1;
      }
    }

    // If no process is available at time t, print IDLE and increment time
    if (!available_process(proc, n, t)) {
      printf("Time: %d - IDLE\n", t);
      t++;
      continue;
    }

    // Choose the process to run at this time step
    chosen = -1;
    if (algo == 0) {
      // FCFS (non-preemptive): If a process is already running, keep it
      if (current_running != -1 && proc[current_running].remaining > 0 &&
          proc[current_running].arrival <= t) {
        chosen = current_running;
      } else {
        // Otherwise, pick the process with the earliest arrival time
        for (i = 0; i < n; i++) {
          if (proc[i].active && proc[i].remaining > 0 && proc[i].arrival <= t) {
            if (chosen == -1 || proc[i].arrival < proc[chosen].arrival) {
              chosen = i;
            }
          }
        }
      }
    } else if (algo == 1) {
      // SJF (non-preemptive): If a process is already running, keep it
      if (current_running != -1 && proc[current_running].remaining > 0 &&
          proc[current_running].arrival <= t) {
        chosen = current_running;
      } else {
        // Otherwise, choose the process with the smallest total CPU time
        for (i = 0; i < n; i++) {
          if (proc[i].active && proc[i].remaining > 0 && proc[i].arrival <= t) {
            if (chosen == -1 || proc[i].total < proc[chosen].total) {
              chosen = i;
            }
          }
        }
      }
    } else if (algo == 2) {
      // SRT (preemptive): Always choose the process with the smallest remaining
      // time
      for (i = 0; i < n; i++) {
        if (proc[i].active && proc[i].remaining > 0 && proc[i].arrival <= t) {
          if (chosen == -1 || proc[i].remaining < proc[chosen].remaining) {
            chosen = i;
          }
        }
      }
    }

    // If a process was chosen, simulate one time unit of its execution
    if (chosen != -1) {
      printf("Time: %d - PID: %d\n", t, proc[chosen].pid);
      proc[chosen].remaining--; // Use one time unit
      // If the process finishes, mark it inactive and record turnaround time
      if (proc[chosen].remaining == 0) {
        proc[chosen].active = 0;
        proc[chosen].turnaround = (t + 1) - proc[chosen].arrival;
      }
      // For non-preemptive algorithms, remember the current process
      current_running = chosen;
    } else {
      // This should not happen if available_process() returned true
      printf("Time: %d - IDLE\n", t);
    }
    t++; // Move to the next time step
  }

  // Compute and print the average turnaround time
  for (i = 0; i < n; i++) {
    total_turnaround += proc[i].turnaround;
  }
  printf("%s: Average Turnaround Time = %.2f\n", algo_name,
         (double)total_turnaround / n);
  printf("----------\n\n");
}

int main(int argc, char *argv[]) {
  int n, k, min_time, max_time;
  int i;
  Process *proc;

  // Use default values if no parameters are provided
  if (argc == 1) {
    n = 10;
    k = 100;
    min_time = 7;
    max_time = 15;
  } else if (argc == 5) {
    n = atoi(argv[1]);
    k = atoi(argv[2]);
    min_time = atoi(argv[3]);
    max_time = atoi(argv[4]);
    if (n <= 0 || k < 0 || min_time <= 0 || max_time < min_time) {
      fprintf(stderr, "Error: invalid parameter values.\n");
      fprintf(stderr, "Usage: %s [n k min_time max_time]\n", argv[0]);
      return 1;
    }
  } else {
    fprintf(stderr, "Usage: %s [n k min_time max_time]\n", argv[0]);
    fprintf(stderr, "Defaults: n = 10, k = 100, min_time = 7, max_time = 15\n");
    return 1;
  }

  // Seed the random number generator
  srand((unsigned)time(NULL));

  // Allocate an array for n processes
  proc = (Process *)malloc(n * sizeof(Process));
  if (proc == NULL) {
    fprintf(stderr, "Error: could not allocate memory.\n");
    return 1;
  }

  // Initialize the process table
  for (i = 0; i < n; i++) {
    proc[i].pid = i;
    proc[i].arrival = rand() % (k + 1); // Arrival time in [0, k]
    proc[i].total =
        min_time + (rand() % (max_time - min_time + 1)); // Total CPU time
    proc[i].remaining = proc[i].total;
    proc[i].turnaround = 0;
    // Set active flag to 1 if arrival time is 0, else 0
    if (proc[i].arrival == 0)
      proc[i].active = 1;
    else
      proc[i].active = 0;
  }

  // Print the initial process table
  print_table(proc, n);

  // Run the simulation for each scheduling algorithm.
  // 0 = FCFS, 1 = SJF, 2 = SRT
  simulate(proc, n, 0, "FCFS");
  reset_processes(proc, n);

  simulate(proc, n, 1, "SJF");
  reset_processes(proc, n);

  simulate(proc, n, 2, "SRT");
  reset_processes(proc, n);

  free(proc);
  return 0;
}
