// stack.h
#ifndef STACK_CALC_H
#define STACK_CALC_H

#include <stdbool.h>
#include <stdlib.h>

#include "stack.h"

// Maximum size of the stack
#define STACK_MAX_SIZE 256

#define INT_MAX 2147483647

CalculatorError return_stack_error(StackError stack_error);

// Calculator operations
StackError calc_add(Stack* stack);
StackError calc_subtract(Stack* stack);
StackError calc_multiply(Stack* stack);
StackError calc_divide(Stack* stack);
StackError calc_square_root(Stack* stack);
StackError calc_power(Stack* stack);

#endif