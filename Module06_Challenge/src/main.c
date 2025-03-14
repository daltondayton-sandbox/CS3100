#include "paged_mem.h"
#include <stdio.h>
#include <stdlib.h>

// Prints the usage message if the memory file argument is missing.
void print_usage(const char *progname) {
  fprintf(stderr, "Usage: %s <memory_file>\n", progname);
}

// Prints help information for the available commands.
void print_help() {
  printf("Commands:\n");
  printf("t <virtual_address>         - Translate virtual address to physical "
         "address\n");
  printf("r <virtual_address>         - Read value at virtual address\n");
  printf("w <virtual_address> <value> - Write value to virtual address\n");
  printf("h                         - Help\n");
  printf("q                         - Quit\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  // Open the memory file.
  char *memory_file = argv[1];
  FILE *fp = fopen(memory_file, "r");
  if (!fp) {
    perror("Error opening memory file");
    return EXIT_FAILURE;
  }

  // Read header values from the file.
  // Format:
  // 1. Number of words in virtual memory (Must be a power of 2)
  // 2. Number of words in physical memory (Must be a power of 2)
  // 3. Number of words per page or frame (Must be a power of 2)
  // 4. Location of the page table (Must be divisible by page/frame size)
  unsigned int virtual_mem_size, physical_mem_size, words_per_page,
      page_table_loc;
  if (fscanf(fp, "%u", &virtual_mem_size) != 1 ||
      fscanf(fp, "%u", &physical_mem_size) != 1 ||
      fscanf(fp, "%u", &words_per_page) != 1 ||
      fscanf(fp, "%u", &page_table_loc) != 1) {
    fprintf(stderr, "Error reading header values from file\n");
    fclose(fp);
    return EXIT_FAILURE;
  }

  // Allocate an array for physical memory.
  int *memory = malloc(physical_mem_size * sizeof(int));
  if (!memory) {
    fprintf(stderr, "Memory allocation failed\n");
    fclose(fp);
    return EXIT_FAILURE;
  }

  // Read the memory contents into the array.
  for (unsigned int i = 0; i < physical_mem_size; i++) {
    if (fscanf(fp, "%d", &memory[i]) != 1) {
      fprintf(stderr, "Error reading memory contents at index %u\n", i);
      free(memory);
      fclose(fp);
      return EXIT_FAILURE;
    }
  }
  fclose(fp);

  // Compute offset_bits from words_per_page (page size).
  // Since words_per_page is a power of 2, offset_bits = log2(words_per_page).
  unsigned int offset_bits = 0;
  unsigned int temp = words_per_page;
  while (temp > 1) {
    offset_bits++;
    temp >>= 1;
  }

  // Print out configuration details.
  printf("Configuration:\n");
  printf("Virtual Memory Size: %u\n", virtual_mem_size);
  printf("Physical Memory Size: %u\n", physical_mem_size);
  printf("Words Per Page: %u\n", words_per_page);
  printf("Page Table Location: %u\n", page_table_loc);
  printf("Offset Bits: %u\n", offset_bits);

  // Print help for available commands.
  print_help();

  // Interactive simulation loop.
  char input[256];
  char cmd;
  unsigned int virtual_address;
  int value;

  while (1) {
    printf("> ");
    if (!fgets(input, sizeof(input), stdin))
      break; // Exit on EOF or error.

    // Process command input.
    if (input[0] == 'q') {
      break; // Quit the simulation.
    } else if (input[0] == 'h') {
      print_help();
    } else if (input[0] == 't') {
      // Command format: t <virtual_address>
      if (sscanf(input, " %c %u", &cmd, &virtual_address) == 2) {
        int phys_addr = get_physical_address(virtual_address, offset_bits,
                                             page_table_loc, memory);
        printf("%u -> %d\n", virtual_address, phys_addr);
      } else {
        printf("Invalid command. Usage: t <virtual_address>\n");
      }
    } else if (input[0] == 'r') {
      // Command format: r <virtual_address>
      if (sscanf(input, " %c %u", &cmd, &virtual_address) == 2) {
        int read_val =
            read_value(virtual_address, offset_bits, page_table_loc, memory);
        printf("%u: %d\n", virtual_address, read_val);
      } else {
        printf("Invalid command. Usage: r <virtual_address>\n");
      }
    } else if (input[0] == 'w') {
      // Command format: w <virtual_address> <value>
      if (sscanf(input, " %c %u %d", &cmd, &virtual_address, &value) == 3) {
        write_value(value, virtual_address, offset_bits, page_table_loc,
                    memory);
        // Confirm the write.
        int read_val =
            read_value(virtual_address, offset_bits, page_table_loc, memory);
        printf("%u: %d\n", virtual_address, read_val);
      } else {
        printf("Invalid command. Usage: w <virtual_address> <value>\n");
      }
    } else {
      printf("Unknown command. Type 'h' for help.\n");
    }
  }

  free(memory);
  return EXIT_SUCCESS;
}

