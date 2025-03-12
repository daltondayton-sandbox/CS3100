# Compiler and basic flags
CC = gcc
CFLAGS = -Wall -Wextra -fPIC -Iinclude
LDFLAGS = -shared

# Targets for our shared library and executable
LIB = libpaged_mem.so
EXE = main

# Default target builds both the shared library and the executable
all: $(LIB) $(EXE)

# Build the shared library from your paged memory source file
$(LIB): src/paged_mem.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(LIB) src/paged_mem.c

# Build the executable that will use the shared library
$(EXE): src/main.c
	$(CC) $(CFLAGS) -o $(EXE) src/main.c -L. -lpaged_mem -Wl,-rpath,.

# Clean up build artifacts
clean:
	rm -f $(LIB) $(EXE)

