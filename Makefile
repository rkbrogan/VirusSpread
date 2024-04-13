# Compiler
CC = clang

# Directories
SRCDIR = src
INCDIR = include
LIBDIR = libs
BINDIR = bin
TESTDIR = test
EXTERNALDIR = externals

# Executable name
BINARY = virus

# Files
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(LIBDIR)/%.o, $(SRC))
TESTSRC = $(wildcard $(TESTDIR)/*.c) $(EXTERNALDIR)/munit/munit.c
TESTOBJ = $(patsubst $(TESTDIR)/%.c, $(LIBDIR)/%.o, $(TESTSRC))

# Flags
CFLAGS = -I$(INCDIR) -Wall -Wextra -g
LDFLAGS = 

# Targets
EXECUTABLE = $(BINDIR)/$(BINARY)
TEST_EXECUTABLE = $(BINDIR)/$(BINARY)-unit-tests

.PHONY: all clean tests

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(LIBDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(LIBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

tests: CFLAGS += -I$(EXTERNALDIR)/munit
tests: $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(filter-out $(LIBDIR)/main.o, $(OBJ)) $(TESTOBJ)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
	@echo "\nRunning tests...\n"
	@./$(TEST_EXECUTABLE)

$(LIBDIR)/%.o: $(TESTDIR)/%.c
	@mkdir -p $(LIBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BINDIR) $(LIBDIR)
	@echo rm -rf $(BINDIR) $(LIBDIR)
	@echo "\nProject cleaned.\n"