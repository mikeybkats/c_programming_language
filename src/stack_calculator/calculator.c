#include "calculator.h"

#include <stdio.h>

void print_number(double num) {
  // Check if number has decimal part by comparing with its integer part
  if (num == (int)num) {
    printf("%.0f\n", num);  // Print without decimal
  } else {
    printf("%g\n", num);  // Print with decimal
  }
}

void print_result(Stack* stack) {
  double result;

  stack_peek(stack, &result);

  print_number(result);
}
