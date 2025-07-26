#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void stack_init(Stack* stack) {
  if (stack == NULL) {
    return;
  }

  stack->top      = 0;
  stack->capacity = STACK_MAX_SIZE;
  stack->values   = (double*)malloc(sizeof(double) * STACK_MAX_SIZE);

  if (stack->values == NULL) {
    stack->capacity = 0;
    return;
  }
}

void stack_free(Stack* stack) {
  if (stack->values != NULL) {
    free(stack->values);
    stack->values   = NULL;
    stack->top      = 0;
    stack->capacity = 0;
  }
}

StackError stack_push(Stack* stack, double value) {
  // first check if the stack is full
  if (stack->top == stack->capacity) {
    // if it is, grow the stack
    size_t new_capacity = stack->capacity * 2;

    double* new_values = realloc(stack->values, new_capacity * sizeof(double));
    if (new_values == NULL) {
      return STACK_OVERFLOW;
    }

    stack->capacity = new_capacity;
    stack->values   = new_values;
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

size_t stack_size(const Stack* stack) {
  // crash the program if stack pointer is NULL
  assert(stack != NULL && "Stack pointer cannot be NULL in stack_size");

  return stack->top;
}

bool stack_is_empty(const Stack* stack) {
  // crash the program if stack pointer is NULL
  assert(stack != NULL && "Stack pointer cannot be NULL in stack_is_empty");

  return stack->top == 0;
}

void print_stack(const Stack* stack) {
  if (stack->top > INT_MAX) {
    // Handle error case
    printf("Stack too large for int conversion\n");
    return;
  }

  printf("------\n");
  printf("Stack:\n");
  printf("------\n");

  for (int i = 0; i < (int)stack->top; i++) {
    printf("Index: %d, Value: %f\n", i, stack->values[i]);
  }
  printf("\n");
}
