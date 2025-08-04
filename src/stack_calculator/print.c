
#include <stdio.h>

#include "stack.h"

void print_bits(double num) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", ((int)num >> i) & 1);
    if (i % 4 == 0) {
      printf(" ");
    }
  }
  printf("\n");
}

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