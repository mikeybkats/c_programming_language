#include "stack_calculator.h"

#include <stdlib.h>

void stack_init(Stack* stack) {
  stack->top      = 0;
  stack->values   = (double*)malloc(sizeof(double) * STACK_MAX_SIZE);
  stack->capacity = STACK_MAX_SIZE;
}

void stack_free(Stack* stack) {
  free(stack->values);
  stack->values   = NULL;
  stack->top      = 0;
  stack->capacity = 0;
}

StackError stack_push(Stack* stack, double value) {
  // first check if the stack is full
  if (stack->top == stack->capacity) {
    // if it is, grow the stack
    size_t  new_capacity = stack->capacity *= 2;
    double* new_values   = realloc(stack->values, new_capacity);

    // if memory allocation failed
    if (new_values == NULL) {
      return STACK_OVERFLOW;
    }

    stack->capacity = new_capacity;
    stack->values   = new_values;
    stack->top++;
  }

  // else, just add the value to the stack
  stack->values[stack->top] = value;
  stack->top++;
  return STACK_OK;
}

StackError stack_pop(Stack* stack, double* value) {
  // check if the stack is below zero
  if (stack->top == 0) {
    return STACK_UNDERFLOW;
  }

  // set the new top to top - 1. (remember top is an empty spot)
  stack->top--;

  // take the top value off the stack and put it in the value
  *value = stack->values[stack->top];

  return STACK_OK;
}

/**
 * ## Function: stack_peek
 *
 * @brief Similar to pop() -- it looks at the top value of the stack, but does
 * not remove the value.
 */
StackError stack_peek(const Stack* stack, double* result) {
  if (result == NULL || stack == NULL) {
    return STACK_NULL_POINTER;
  }

  if (stack->top == 0) {
    return STACK_UNDERFLOW;
  }

  *result = stack->values[stack->top - 1];

  return STACK_OK;
}