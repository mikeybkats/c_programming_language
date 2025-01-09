CC=clang
CFLAGS=-g -Wall -Wextra -std=c99 
SRC_DIR=src
BUILD_DIR=build

# Stack Calculator specific
CALC_SRC_DIR=$(SRC_DIR)/stack_calculator
CALC_SRCS=$(wildcard $(CALC_SRC_DIR)/*.c)
CALC_OBJS=$(CALC_SRCS:$(CALC_SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
CALC_TARGET=$(BUILD_DIR)/calculator

# Other single-file programs
SINGLE_SRCS=$(filter-out $(CALC_SRCS), $(wildcard $(SRC_DIR)/*.c))
SINGLE_EXES=$(SINGLE_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%)

# Create build directory
$(shell mkdir -p $(BUILD_DIR))

all: $(SINGLE_EXES) calculator

calculator: $(CALC_TARGET)

singles: $(SINGLE_EXES)

$(CALC_TARGET): $(CALC_OBJS)
	$(CC) $(CFLAGS) $(CALC_OBJS) -o $@

$(BUILD_DIR)/%.o: $(CALC_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Direct compilation for single-file programs
$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean calculator