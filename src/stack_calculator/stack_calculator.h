// stack.h
#ifndef STACK_CALC_H
#define STACK_CALC_H

#include <stdbool.h>
#include <stdlib.h>

#include "stack.h"
#include "token.h"

// Maximum size of the stack
#define STACK_MAX_SIZE 256

typedef enum
{
  ERROR_STACK,
  ERROR_TOKEN,
  ERROR_NONE
} ErrorType;

typedef struct
{
  ErrorType type;
  union {
    StackError stack_error;
    TokenError token_error;
  } error;
} CalculatorError;

CalculatorError return_stack_error(StackError stack_error);

// Calculator operations
StackError calc_add(Stack* stack);
StackError calc_subtract(Stack* stack);
StackError calc_multiply(Stack* stack);
StackError calc_divide(Stack* stack);
StackError calc_square_root(Stack* stack);
StackError calc_power(Stack* stack);

#endif