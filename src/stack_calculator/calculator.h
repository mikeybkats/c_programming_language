// stack.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdbool.h>
#include <stdlib.h>

#include "stack.h"
#include "stack_calculator.h"

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

#endif