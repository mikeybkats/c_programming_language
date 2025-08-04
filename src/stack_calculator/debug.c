#include <stdio.h>

#include "stack.h"
#include "stack_calculator.h"
#include "token.h"

void debug_token(Token token) {
  switch (token.type) {
    case TOKEN_PLUS:
      printf("+");
    case TOKEN_MINUS:
      printf("-");
    case TOKEN_MULTIPLY:
      printf("*");
    case TOKEN_DIVIDE:
      printf("/");
    case TOKEN_POWER:
      printf("^");
    case TOKEN_NUMBER:
      printf("%f", token.value);
    default:
      printf("Not a token type\n");
  }
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

void print_source(const char* source) {
  printf("Scanner source: %s", source);
};