# Paged Memory Simulator

This project simulates a paging-based memory management system in C. It provides a dynamically-linked shared library (`libpaged_mem.so`) that implements functions for virtual-to-physical address translation, as well as an interactive executable (`main`) that uses these functions. Unit tests are also included.

## Build Instructions

This project is built using a Makefile. Below are the commands and steps used for building the library, the executable, and unit tests.

### 1. Building the Shared Library

The shared library is built from `src/paged_mem.c` with the following command:

`gcc -Wall -Wextra -fPIC -Iinclude -shared -o libpaged_mem.so src/paged_mem.c`

- ` -Wall -Wextra`: Enable all warnings.
- ` -fPIC`: Generate position-independent code (required for shared libraries).
- ` -Iinclude`: Adds the `include` directory to the header search path.
- ` -shared`: Creates a shared library.
- ` -o libpaged_mem.so`: Names the output shared library.
- ` src/paged_mem.c`: The source file for the library.

### 2. Building the Main Executable

The executable is built from `src/main.c` and links with the shared library using:

`gcc -Wall -Wextra -fPIC -Iinclude -o main src/main.c -L. -lpaged_mem -Wl,-rpath,.`

- ` -L.`: Look for libraries in the current directory.
- ` -lpaged_mem`: Link with `libpaged_mem.so` (omit the `lib` prefix and `.so` extension).
- ` -Wl,-rpath,.`: Embed the runtime library search path to include the current directory so that the shared library can be found at runtime.

### 3. Building Unit Tests (Optional)

To compile the unit tests (which combine the test file with your library source):

`gcc -Wall -Wextra -Iinclude -o test_paged_mem tests/test_paged_mem.c src/paged_mem.c`

Then run the tests with:

`./test_paged_mem`

### 4. Using the Makefile

The provided Makefile includes targets for building everything and cleaning up build artifacts:

- **Build Everything (Library + Executable):**
  
  `make`

- **Run Unit Tests:**

  `make test`

- **Clean Build Artifacts:**

  `make clean`

### 5. Setting Environment Variables

Before running the executable, ensure that the dynamic linker can find the shared library by setting the `LD_LIBRARY_PATH`:

`export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH`

This command tells the system to look in the current directory for shared libraries.

## Run Instructions

After building the project, run the simulator by passing a memory file as a command-line argument. For example:

`./main memory_files/mem_file1`

The interactive session will display configuration details and allow you to use commands such as:

- **t <virtual_address>**: Translate a virtual address to its physical address.
- **r <virtual_address>**: Read the value stored at a virtual address.
- **w <virtual_address> <value>**: Write a value to a virtual address.
- **h**: Display a help message.
- **q**: Quit the simulation.

## Intermediate Steps (Optional)

If you wish to compile object files manually before linking (useful for debugging or incremental builds), you can run:

1. **Compile Object File for the Library:**

   `gcc -Wall -Wextra -fPIC -Iinclude -c src/paged_mem.c -o paged_mem.o`

2. **Link the Object File into a Shared Library:**

   `gcc -shared -o libpaged_mem.so paged_mem.o`

3. **Compile the Main Executable (Linking the Library):**

   `gcc -Wall -Wextra -fPIC -Iinclude -o main src/main.c -L. -lpaged_mem -Wl,-rpath,.`

## Summary of Commands

- **Build Shared Library:**
  
  `gcc -Wall -Wextra -fPIC -Iinclude -shared -o libpaged_mem.so src/paged_mem.c`

- **Build Main Executable:**
  
  `gcc -Wall -Wextra -fPIC -Iinclude -o main src/main.c -L. -lpaged_mem -Wl,-rpath,.`

- **Set Environment Variable:**
  
  `export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH`

- **Build Unit Tests:**
  
  `gcc -Wall -Wextra -Iinclude -o test_paged_mem tests/test_paged_mem.c src/paged_mem.c`

- **Run Unit Tests:**
  
  `./test_paged_mem`

- **Using the Makefile:**
  - Build All: `make`
  - Run Tests: `make test`
  - Clean: `make clean`

