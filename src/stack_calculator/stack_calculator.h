// stack.h
#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>

// Maximum size of the stack
#define STACK_MAX_SIZE 256

// Error codes
typedef enum
{
  STACK_OK,
  STACK_OVERFLOW,
  STACK_UNDERFLOW,
  STACK_DIVISION_BY_ZERO,
  STACK_NULL_POINTER
} StackError;

// Stack structure
typedef struct
{
  double* values;
  size_t  top;  // the next available spot (which is always empty)
  size_t  capacity;
} Stack;

// Core stack operations
void       stack_init(Stack* stack);
void       stack_free(Stack* stack);
StackError stack_push(Stack* stack, double value);
StackError stack_pop(Stack* stack, double* result);
StackError stack_peek(const Stack* stack, double* result);
size_t     stack_size(const Stack* stack);
bool       stack_is_empty(const Stack* stack);

// Calculator operations
StackError calc_add(Stack* stack);
StackError calc_subtract(Stack* stack);
StackError calc_multiply(Stack* stack);
StackError calc_divide(Stack* stack);
StackError calc_square_root(Stack* stack);
StackError calc_power(Stack* stack);

// String parsing and evaluation
typedef struct
{
  const char* input;
  size_t      position;
  Stack*      stack;
  StackError  error;
} Calculator;

void       calculator_init(Calculator* calc, const char* input, Stack* stack);
StackError calculator_evaluate(Calculator* calc);

// Error handling
const char* stack_error_string(StackError error);

#endif  // STACK_i