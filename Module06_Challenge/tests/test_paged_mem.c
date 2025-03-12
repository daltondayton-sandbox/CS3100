#include "paged_mem.h"
#include <assert.h>
#include <stdio.h>

void test_is_power_of_2() {
  assert(is_power_of_2(1) == true);  // 1 = 2^0
  assert(is_power_of_2(2) == true);  // 2 = 2^1
  assert(is_power_of_2(3) == false); // 3 is not a power of 2
  assert(is_power_of_2(4) == true);  // 4 = 2^2
  // Optionally test 0, which is not a power of 2
  /*assert(is_power_of_2(0) == false);*/
  printf("is_power_of_2 tests passed.\n");
}

void test_get_physical_address() {
  // Setup a simple physical memory array.
  // For this test, we use offset_bits = 2, so page size is 2^2 = 4.
  int physical_memory[10] = {0};
  unsigned int page_table_loc = 0;
  unsigned int offset_bits = 2;

  // For virtual address 6:
  //   page_number = 6 >> 2 = 1,
  //   offset = 6 & (4 - 1) = 6 & 3 = 2.
  // Set page table entry for page 1 to frame number 3.
  physical_memory[page_table_loc + 1] = 3;

  // Expected physical address = (3 * 4) + 2 = 14.
  unsigned int virtual_address = 6;
  int physical_address = get_physical_address(virtual_address, offset_bits,
                                              page_table_loc, physical_memory);
  assert(physical_address == 14);

  printf("get_physical_address test passed.\n");
}

void test_read_write_value() {
  // We'll use a larger physical memory array.
  int physical_memory[16] = {0};
  unsigned int page_table_loc = 0;
  unsigned int offset_bits = 2; // using this as the basis for our page size
  // For this assignment, the second parameter in read_value/write_value is
  // called page_mask. In our tests we use the same value as offset_bits
  // (assuming our implementation handles it similarly).
  int page_mask = offset_bits;

  // Setup the page table:
  // For virtual address 6:
  //   page_number = 6 >> 2 = 1, offset = 2.
  // Set page table entry for page 1 to frame number 3.
  physical_memory[page_table_loc + 1] = 3;

  // That makes the physical address: (3 * 4) + 2 = 14.
  unsigned int virtual_address = 6;

  // Set an initial value at the computed physical address.
  physical_memory[14] = 42;

  int value =
      read_value(virtual_address, page_mask, page_table_loc, physical_memory);
  assert(value == 42);

  // Now write a new value.
  write_value(99, virtual_address, page_mask, page_table_loc, physical_memory);

  // Verify that read_value now returns the new value.
  value =
      read_value(virtual_address, page_mask, page_table_loc, physical_memory);
  assert(value == 99);

  // Also, the physical memory at index 14 should be updated.
  assert(physical_memory[14] == 99);

  printf("read_value and write_value tests passed.\n");
}

int main(void) {
  test_is_power_of_2();
  test_get_physical_address();
  test_read_write_value();
  printf("All tests passed!\n");
  return 0;
}

