// stack.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdbool.h>
#include <stdlib.h>

#include "stack.h"
#include "stack_calculator.h"

CalculatorError calculator_evaluate(const char* input, Stack* stack);

void print_result(Stack* stack);

void print_stack(Stack* stack);

// Error handling
void handle_error(CalculatorError error);

#endif