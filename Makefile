# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -std=c11

# Directories
INCLUDE_DIR = include
SRC_DIR = src
TEST_DIR = test
BIN_DIR = bin
LIBS_DIR = libs

# Executable name
BINARY = virus

# Main program source files
MAIN_SOURCES = $(wildcard $(SRC_DIR)/*.c)
MAIN_OBJECTS = $(MAIN_SOURCES:$(SRC_DIR)/%.c=$(LIBS_DIR)/%.o)
MAIN_EXECUTABLE = $(BIN_DIR)/$(BINARY)

# Test program source files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c) $(wildcard $(SRC_DIR)/*.c) externals/munit/munit.c
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(LIBS_DIR)/%.o)
TEST_EXECUTABLE = $(BIN_DIR)/$(BINARY)-test

# Include paths
INCLUDE_PATHS = -I$(INCLUDE_DIR) -Iexternals/munit

# Default target
all: main tests

# Create bin and libs directories if they don't exist
$(BIN_DIR) $(LIBS_DIR):
	mkdir -p $@
	@echo "Created $@ directory."

# Rule to build object files for main program
$(LIBS_DIR)/%.o: $(SRC_DIR)/%.c | $(LIBS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@
	@echo "Compiled $< to $@"

# Rule to build the main program executable
$(MAIN_EXECUTABLE): $(MAIN_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "Linked main program executable: $@"

# Rule to build object files for test program
$(LIBS_DIR)/%.o: $(TEST_DIR)/%.c | $(LIBS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@
	@echo "Compiled $< to $@"

# Rule to build the test program executable
$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) $^ -o $@
	@echo "Linked test program executable: $@"

# Target for running tests
tests: $(BIN_DIR) $(TEST_EXECUTABLE)
	@$(TEST_EXECUTABLE)
	@echo "Tests executed successfully."

# Target for building main program
main: $(BIN_DIR) $(MAIN_EXECUTABLE)
	@echo "Main program build completed successfully."

# Clean up
clean:
	@rm -rf $(LIBS_DIR) $(BIN_DIR)
	@echo "Cleaned up the project."
