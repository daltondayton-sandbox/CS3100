#include "paged_mem.h"
#include <assert.h>
#include <stdio.h>

void test_is_power_of_2() {
  // Test various cases for is_power_of_2
  assert(is_power_of_2(1) == true);  // 1 = 2^0
  assert(is_power_of_2(2) == true);  // 2 = 2^1
  assert(is_power_of_2(3) == false); // 3 is not a power of 2
  assert(is_power_of_2(4) == true);  // 4 = 2^2
  // Optionally test zero if you expect it to return false
  /*assert(is_power_of_2(0) == false);*/
  printf("is_power_of_2 tests passed.\n");
}

void test_get_physical_address() {
  // For this test, we'll create a dummy physical_memory array.
  // Assume offset_bits = 2, so page size is 2^2 = 4.
  // We'll place the page table at location 0.
  // For a given virtual address:
  //   virtual_address = 6
  // Then:
  //   page_number = 6 >> 2 = 1
  //   offset = 6 & (4 - 1) = 6 & 3 = 2
  // Suppose the page table entry for page 1 is frame number 3.
  // Then the physical address should be: (3 * 4) + 2 = 14.
  int physical_memory[10] = {0}; // A simple array for our test
  unsigned int page_table_loc = 0;
  unsigned int offset_bits = 2;

  // Setup the page table: for page number 1, set frame number to 3.
  physical_memory[page_table_loc + 1] = 3;

  unsigned int virtual_address = 6;
  int physical_address = get_physical_address(virtual_address, offset_bits,
                                              page_table_loc, physical_memory);
  assert(physical_address == 14);

  printf("get_physical_address test passed.\n");
}

int main(void) {
  test_is_power_of_2();
  test_get_physical_address();
  printf("All tests passed!\n");
  return 0;
}
