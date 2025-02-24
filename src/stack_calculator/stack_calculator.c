#include "stack_calculator.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

CalculatorError return_stack_error(StackError stack_error) {
  CalculatorError error;
  error.type              = ERROR_STACK;
  error.error.stack_error = stack_error;

  return error;
}

StackError calc_add(Stack* stack) {
  if (stack->top < 2) {
    return STACK_UNDERFLOW;
  }

  double     add1, add2;
  StackError r1, r2;

  r1 = stack_pop(stack, &add2);
  r2 = stack_pop(stack, &add1);

  assert(r1 == STACK_OK &&
         "calc_add -- Stack memory error. Processing r1 from stack_pop.");
  assert(r2 == STACK_OK &&
         "calc_add -- Stack memory error. Processing r2 from stack_pop.");

  return stack_push(stack, add1 + add2);
}

StackError calc_subtract(Stack* stack) {
  if (stack->top < 2) {
    return STACK_UNDERFLOW;
  }

  double     base, subtractor;
  StackError r1, r2;

  r1 = stack_pop(stack, &subtractor);
  r2 = stack_pop(stack, &base);

  assert(r1 == STACK_OK &&
         "calc_subtract -- Stack memory error. Processing r1 - subtractor from "
         "stack_pop.");
  assert(r2 == STACK_OK &&
         "calc_subtract -- Stack memory error. Processing r2 - base from "
         "stack_pop.");

  return stack_push(stack, base - subtractor);
}

StackError calc_multiply(Stack* stack) {
  if (stack->top < 2) {
    return STACK_UNDERFLOW;
  }

  double     multiplier1, multiplier2;
  StackError r1, r2;

  r1 = stack_pop(stack, &multiplier1);
  r2 = stack_pop(stack, &multiplier2);

  assert(r1 == STACK_OK &&
         "calc_multiply -- Stack memory error. Processing r1 - multiplier1 "
         "from stack_pop.");
  assert(r2 == STACK_OK &&
         "calc_multiply -- Stack memory error. Processing r2 - multiplier2 "
         "from stack_pop.");

  return stack_push(stack, multiplier1 * multiplier2);
}

StackError calc_divide(Stack* stack) {
  if (stack->top < 2) {
    return STACK_UNDERFLOW;
  }

  double     divisor, base;
  StackError r1, r2;

  r1 = stack_pop(stack, &divisor);
  r2 = stack_pop(stack, &base);

  assert(r1 == STACK_OK &&
         "calc_divide -- Stack memory error. Processing r1 from stack_pop.");
  assert(r2 == STACK_OK &&
         "calc_divide -- Stack memory error. Processing r2 from stack_pop.");

  if (divisor == 0) {
    return STACK_DIVISION_BY_ZERO;
  }

  return stack_push(stack, base / divisor);
}

StackError calc_square_root(Stack* stack) {
  if (stack->top < 1) {
    return STACK_UNDERFLOW;
  }

  double     n1;
  StackError r1;

  r1 = stack_pop(stack, &n1);

  assert(
      r1 == STACK_OK &&
      "calc_square_root -- Stack memory error. Processing r1 from stack_pop.");

  if (n1 < 0) {
    return STACK_NAN;
  }

  return stack_push(stack, sqrt(n1));
}

StackError calc_power(Stack* stack) {
  if (stack->top < 2) {
    return STACK_UNDERFLOW;
  }

  double     exponent, base;
  StackError r1, r2;

  r1 = stack_pop(stack, &exponent);
  r2 = stack_pop(stack, &base);

  assert(r1 == STACK_OK &&
         "calc_power -- Stack memory error. Processing r1 exponent from "
         "stack_pop.");
  assert(
      r2 == STACK_OK &&
      "calc_power -- Stack memory error. Processing r2 base from stack_pop.");

  return stack_push(stack, pow(base, exponent));
}