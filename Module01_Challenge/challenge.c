#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  // Print a welcome message
  printf("Hello C World\n");

  // Print the PID of the program
  pid_t pid = getpid(); // Get the process ID of the current program
  printf("This is PID %d speaking\n", pid);

  // List PIDs and cmdline values of accessible processes
  DIR *proc_dir = opendir("/proc"); // Open the /proc directory
  if (proc_dir == NULL) {
    perror("Failed to open /proc"); // Handle errors gracefully
    return 1;
  }

  struct dirent *entry;
  while ((entry = readdir(proc_dir)) != NULL) {
    // Skip non-numeric entries
    if (!isdigit(entry->d_name[0])) {
      continue;
    }

    // Construct the path to the cmdline file
    char path[256];
    snprintf(path, sizeof(path), "/proc/%s/cmdline", entry->d_name);

    // Open the cmdline file
    FILE *cmdline_file = fopen(path, "r");
    if (cmdline_file == NULL) {
      continue; // Skip if the file cannot be opened
    }

    // Read the cmdline content
    char cmdline[1024];
    if (fgets(cmdline, sizeof(cmdline), cmdline_file) != NULL) {
      // Replace null characters with spaces for readability
      for (char *ptr = cmdline; *ptr != '\0'; ++ptr) {
        if (*ptr == '\0') {
          *ptr = ' ';
        }
      }
      printf("%s\t%s\n", entry->d_name, cmdline); // Print PID and cmdline
    }

    fclose(cmdline_file); // Close the cmdline file
  }

  closedir(proc_dir); // Close the /proc directory

  return 0;
}
