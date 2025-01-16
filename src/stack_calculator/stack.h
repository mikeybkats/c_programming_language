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
  STACK_NULL_POINTER,
  STACK_NAN,
  STACK_EVAL_ERROR
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

/**
 * ## Function: stack_peek
 *
 * @brief Similar to pop() -- it looks at the top value of the stack, but does
 * not remove the value.
 */
StackError stack_peek(const Stack* stack, double* result);

/**
 * ## Function: stack_size
 *
 * @brief returns the number of values on the stack
 */
size_t stack_size(const Stack* stack);

/**
 * ## Function: stack_is_empty
 */
bool stack_is_empty(const Stack* stack);

#endif