# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -fPIC -Iinclude
LDFLAGS = -shared

# Directories
SRCDIR = src
INCDIR = include
TESTDIR = tests

# Targets for the shared library and main executable
LIB = libpaged_mem.so
EXE = main

# Default target: build both library and executable
all: $(LIB) $(EXE)

# Build the shared library from src/paged_mem.c
$(LIB): $(SRCDIR)/paged_mem.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(LIB) $(SRCDIR)/paged_mem.c

# Build the main executable from src/main.c, linking with the shared library
$(EXE): $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o $(EXE) $(SRCDIR)/main.c -L. -lpaged_mem -Wl,-rpath,.

# Build the test executable that compiles tests/test_paged_mem.c with the library
TEST_EXE = test_paged_mem
test: $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE): $(TESTDIR)/test_paged_mem.c $(SRCDIR)/paged_mem.c
	$(CC) $(CFLAGS) -o $(TEST_EXE) $(TESTDIR)/test_paged_mem.c $(SRCDIR)/paged_mem.c

# Clean up all built files
clean:
	rm -f $(LIB) $(EXE) $(TEST_EXE)

