#include "paged_mem.h"

bool is_power_of_2(unsigned int value) {
  //
  return (value & (value - 1)) == 0;
}

int get_physical_address(unsigned int virtual_address, unsigned int offset_bits,
                         unsigned int page_table_loc, int *physical_memory) {
  unsigned int page_size = 1 << offset_bits;
  unsigned int offset = virtual_address & (page_size - 1);
  unsigned int page_number = virtual_address >> offset_bits;
  unsigned int frame_number = physical_memory[page_table_loc + page_number];

  return (frame_number * page_size) + offset;
}

int read_value(int virtual_address, int page_mask, int page_table_loc,
               int *physical_memory) {
  int physical_address = get_physical_address(virtual_address, page_mask,
                                              page_table_loc, physical_memory);
  return physical_memory[physical_address];
}

void write_value(int value, int virtual_address, int page_mask,
                 int page_table_loc, int *physical_memory) {
  int physical_address = get_physical_address(virtual_address, page_mask,
                                              page_table_loc, physical_memory);
  physical_memory[physical_address] = value;
}
