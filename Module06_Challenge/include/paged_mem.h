#ifndef PAGED_MEM_H
#define PAGED_MEM_H

#include <stdbool.h>

// Check if a value is a power of two. One way to perform this check is to do a
// binary & between the value and the value minus 1. When the value is a power
// of two this will produce a 0 for all other values it will be non-zero.
bool is_power_of_2(unsigned int value);

// Takes a virtual address and converts it to a physical address. The virtual
// address, the number of bits used for the offset, the starting location of the
// page table(s), and a pointer to the physical memory are also passed as
// parameters.
int get_physical_address(unsigned int virtual_address, unsigned int offset_bits,
                         unsigned int page_table_loc, int *physical_memory);

// Takes a virtual address and returns the value at the corresponding physical
// address. The virtual address, the number of bits used for the offset, the
// starting location of the page table(s), and a pointer to the physical memory
// are also passed as parameters.
int read_value(int virtual_address, int page_mask,

               int page_table_loc, int *physical_memory);

// Takes a value and a virtual address and stores the value at the corresponding
// physical address. The virtual address, the number of bits used for the
// offset, the starting location of the page table(s), and a pointer to the
// physical memory are also passed as parameters.
void write_value(int value, int virtual_address, int page_mask,
                 int page_table_loc, int *physical_memory);

#endif // PAGED_MEM_H
