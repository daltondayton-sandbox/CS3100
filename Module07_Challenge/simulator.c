#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INF INT_MAX

typedef struct {
  int page;
  int in_mem;
  int r_bit;
} Entry;

double optimal(int frames, int pages, int *ref, int len) {
  Entry *table = malloc(pages * sizeof(Entry));
  for (int i = 0; i < pages; i++) {
    table[i].page = i;
    table[i].in_mem = 0;
  }
  Entry **mem = malloc(frames * sizeof(Entry *));
  for (int i = 0; i < frames; i++)
    mem[i] = NULL;
  int faults = 0;
  for (int i = 0; i < len; i++) {
    int p = ref[i], found = 0;
    for (int j = 0; j < frames; j++) {
      if (mem[j] && mem[j]->page == p) {
        found = 1;
        break;
      }
    }
    if (found)
      continue;
    faults++;
    int empty = -1;
    for (int j = 0; j < frames; j++) {
      if (mem[j] == NULL) {
        empty = j;
        break;
      }
    }
    if (empty != -1) {
      mem[empty] = &table[p];
      table[p].in_mem = 1;
    } else {
      int rep = -1, farthest = -1;
      for (int j = 0; j < frames; j++) {
        int next = INF;
        for (int k = i + 1; k < len; k++) {
          if (ref[k] == mem[j]->page) {
            next = k;
            break;
          }
        }
        if (next > farthest) {
          farthest = next;
          rep = j;
        }
      }
      mem[rep]->in_mem = 0;
      mem[rep] = &table[p];
      table[p].in_mem = 1;
    }
  }
  free(table);
  free(mem);
  return (double)faults / len * 100;
}

double fifo(int frames, int pages, int *ref, int len) {
  int *mem = malloc(frames * sizeof(int));
  for (int i = 0; i < frames; i++)
    mem[i] = -1;
  int faults = 0, pointer = 0;
  for (int i = 0; i < len; i++) {
    int p = ref[i], found = 0;
    for (int j = 0; j < frames; j++) {
      if (mem[j] == p) {
        found = 1;
        break;
      }
    }
    if (found)
      continue;
    faults++;
    mem[pointer] = p;
    pointer = (pointer + 1) % frames;
  }
  free(mem);
  return (double)faults / len * 100;
}

double second_chance(int frames, int pages, int *ref, int len) {
  typedef struct {
    int page, r;
  } Frame;
  Frame *mem = malloc(frames * sizeof(Frame));
  for (int i = 0; i < frames; i++) {
    mem[i].page = -1;
    mem[i].r = 0;
  }
  int faults = 0, pointer = 0;
  for (int i = 0; i < len; i++) {
    int p = ref[i], found = 0;
    for (int j = 0; j < frames; j++) {
      if (mem[j].page == p) {
        mem[j].r = 1;
        found = 1;
        break;
      }
    }
    if (found)
      continue;
    faults++;
    while (mem[pointer].r) {
      mem[pointer].r = 0;
      pointer = (pointer + 1) % frames;
    }
    mem[pointer].page = p;
    mem[pointer].r = 1;
    pointer = (pointer + 1) % frames;
  }
  free(mem);
  return (double)faults / len * 100;
}

int main(int argc, char **argv) {
  if (argc > 1) {
    printf("Usage: %s\nThis program does not accept command line parameters.\n",
           argv[0]);
    return 1;
  }

  int frames, pages, len;
  printf("Enter the number of frames in main memory: ");
  scanf("%d", &frames);
  printf("Enter the number of pages in the page table: ");
  scanf("%d", &pages);
  printf("Enter the length of the reference string: ");
  scanf("%d", &len);

  int *ref = malloc(len * sizeof(int));
  printf("Enter the reference string: ");
  for (int i = 0; i < len; i++) {
    scanf("%d", &ref[i]);
  }

  double op = optimal(frames, pages, ref, len);
  double f = fifo(frames, pages, ref, len);
  double sc = second_chance(frames, pages, ref, len);

  printf("\nOptimal page faults: %.2f\n", op);
  printf("FIFO page faults: %.2f\n", f);
  printf("Second-Chance page faults: %.2f\n", sc);

  free(ref);
  return 0;
}
