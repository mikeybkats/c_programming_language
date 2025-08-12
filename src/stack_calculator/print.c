
#include <stdio.h>

#include "calculator_types.h"
#include "flag.h"

void print_bits(double num) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", ((int)num >> i) & 1);
    if (i % 4 == 0) {
      printf(" ");
    }
  }
  printf("\n");
}

void print_decimal(double num) {
  // Check if number has decimal part by comparing with its integer part
  if (num == (int)num) {
    printf("%.0f\n", num);  // Print without decimal
  } else {
    printf("%g\n", num);  // Print with decimal
  }
}

void print_hexadecimal(double num) {
  printf("%#.2x\n", (int)num);
}

void print_result(CalculatorResult* result) {
  if (result->type != RESULT_VALUE) {
    return;
  }

  if (result->as.value->flags.length == 0) {
    print_decimal(result->as.value->value);
    return;
  }

  process_flags(result->as.value->value, result->as.value->flags);
}