#
#
# Makefile for Virus Project
#
# Author: Riley Brogan
#
#

# Binary name
BINARY := virus

# Main
MAIN := main

# Gets the Operating system name
OS := $(shell uname -s)

# Source code directory structure
#DIRS   := Simulate Analyze Visualize
BINDIR := bin
SRCDIR := src
LOGDIR := log
INCDIR := include
LIBDIR := libs
EXTDIR := externals
TESTDIR := test

# Source code file extension
SRCEXT := c

# Header file extension
HEADEXT := h

# Defines the C Compiler
CC := gcc

# Defines the language standards for GCC
STD := -std=c11 # See man gcc for more options

# Protection for stack-smashing attack
STACK := -fstack-protector-all -Wstack-protector

# Specifies to GCC the required warnings
WARNS := -Wall -Wextra -pedantic # -pedantic warns on language standards

TEST_WARNS := -Wno-unused-parameter
# TEST_WARNS := -Wunused-parameter

TEST_FLAGS := -DMUNIT_TEST_NAME_LEN=60 -DMUNIT_NO_FORK

# Flags for compiling
CFLAGS := $(STD) $(STACK) $(WARNS) -I$(INCDIR)

# Debug options
DEBUG := -g3 -DDEBUG=1

# Dependency files
DEPS := $(INCDIR)

# Dependency libraries
LIBS := -Ilib

# Test libraries
TEST_LIBS := -I$(EXTDIR)/munit

# Tests binary file
TEST_BINARY := $(BINARY)_test_runner

# Source files
SRC_FILES := $(wildcard $(dir) $(SRCDIR)/*.c)

# %.o file names
NAMES := $(notdir $(basename $(wildcard $(SRCDIR)/$(SRC_FILES))))
OBJECTS :=$(patsubst %,$(LIBDIR)/%.o,$(NAMES))


#
# COMPILATION RULES
#

default: all

# Help message
help:
	@echo "C Project Template"
	@echo
	@echo "Target rules:"
	@echo "    all      - Compiles and generates binary file"
	@echo "    tests    - Compiles with cmocka and run tests binary file"
	@echo "    start    - Starts a new project using C project template"
	@echo "    valgrind - Runs binary file using valgrind tool"
	@echo "    clean    - Clean the project by removing binaries"
	@echo "    help     - Prints a help message with target rules"


# Starts a new project using C project template
start:
	@echo "Creating project: $(PROJECT_NAME)"
	@mkdir -pv $(PROJECT_PATH)
	@echo "Copying files from template to new directory:"
	@cp -rvf ./* $(PROJECT_PATH)/
	@echo
	@echo "Go to $(PROJECT_PATH) and compile your project: make"
	@echo "Then execute it: bin/$(BINARY) --help"
	@echo "Happy hacking o/"


all: main tests

# Rule for link and generate the binary file
main: $(OBJECTS)
	@echo -en "$(BROWN)LD $(END_COLOR)";
	$(CC) $(SRC_FILES) $(SRCDIR)/main/main.c -o $(BINDIR)/$(BINARY) $+ $(DEBUG) $(CFLAGS) $(LIBS)
	@echo -en "\n--\nBinary file placed at" \
			  "$(BROWN)$(BINDIR)/$(BINARY)$(END_COLOR)\n";


# Rule for object binaries compilation
$(LIBDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo -en "$(BROWN)CC $(END_COLOR)";
	$(CC) -c $^ -o $@ $(DEBUG) $(CFLAGS) $(LIBS)


# Rule for run valgrind tool
# TODO: setup valgrind for test binary (reset line 126 to '$(BINDIR)/$(BINARY)')
valgrind:
	valgrind \
		--track-origins=yes \
		--leak-check=full \
		--leak-resolution=high \
		--log-file=$(LOGDIR)/$@.log \
		$(BINDIR)/$(TEST_BINARY)
	@echo -en "\nCheck the log file: $(LOGDIR)/$@.log\n"


# Compile tests and run the test binary
tests:
	@echo SRC_FILES $(SRC_FILES);
	@echo -en "$(BROWN)CC $(END_COLOR)";
	$(CC) $(TEST_FLAGS) $(EXTDIR)/munit/munit.c $(SRC_FILES) $(TESTDIR)/*.$(SRCEXT) -o $(BINDIR)/$(TEST_BINARY) $(DEBUG) $(CFLAGS) $(TEST_WARNS) $(LIBS) $(TEST_LIBS)
	@which ldconfig && ldconfig -C /tmp/ld.so.cache || true # caching the library linking
	@echo -en "$(BROWN) Running tests: $(END_COLOR)";
	./$(BINDIR)/$(TEST_BINARY)


# Rule for cleaning the project
clean:
	@rm -rvf $(BINDIR)/* $(LIBDIR)/* $(LOGDIR)/*;


