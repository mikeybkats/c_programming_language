CC=clang
CFLAGS=-g -Wall -Wextra -std=c99 
SRC_DIR=src
BUILD_DIR=build

# Stack Calculator specific
CALC_SRC_DIR=$(SRC_DIR)/stack_calculator
CALC_SRCS=$(wildcard $(CALC_SRC_DIR)/*.c)
# Fix: Change the object path to include stack_calculator subdirectory
CALC_OBJS=$(CALC_SRCS:$(SRC_DIR)/stack_calculator/%.c=$(BUILD_DIR)/stack_calculator/%.o)
CALC_TARGET=$(BUILD_DIR)/calculator

# Create build directories
$(shell mkdir -p $(BUILD_DIR)/stack_calculator)

all: $(SINGLE_EXES) calculator

calculator: $(CALC_TARGET)

singles: $(SINGLE_EXES)

$(CALC_TARGET): $(CALC_OBJS)
	$(CC) $(CFLAGS) $(CALC_OBJS) -o $@

# Fix: Update the object file path pattern
$(BUILD_DIR)/stack_calculator/%.o: $(CALC_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Direct compilation for single-file programs
$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean calculator