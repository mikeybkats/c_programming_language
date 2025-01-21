#include "calculator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculator_types.h"
#include "scanner.h"

CalculatorError calculator_evaluate(const char* input, Stack* stack) {
  Scanner         scanner;
  CalculatorError calc_error;
  scanner_init(&scanner, input);

  printf("Scanning line\n");
  printf("Line: %s\n", input);
  calc_error = scan_line(&scanner, stack);

  return calc_error;
}

void print_result(Stack* stack) {
  double result;

  stack_peek(stack, &result);

  printf("Result: %f\n", result);
}

char* get_stack_error_message(StackError error) {
  switch (error) {
    case STACK_OK:
      return "Stack ok";
    case STACK_OVERFLOW:
      return "Stack overflow";
    case STACK_UNDERFLOW:
      return "Stack underflow";
    case STACK_DIVISION_BY_ZERO:
      return "Division by zero";
    case STACK_NULL_POINTER:
      return "Null pointer";
    case STACK_NAN:
      return "Not a number";
    case STACK_EVAL_ERROR:
      return "Evaluation error";
  }
}

char* get_token_error_message(TokenError error) {
  switch (error) {
    case TOKEN_OK:
      return "Token ok";
    case TOKEN_INVALID_UNDEFINED:
      return "Invalid undefined";
    case TOKEN_INVALID_NUMBER:
      return "Invalid number";
    case TOKEN_INVALID_OPERATOR:
      return "Invalid operator";
    case TOKEN_NULL_POINTER:
      return "Null pointer";
  }
}

void handle_error(CalculatorError error) {
  char message[50];
  if (error.type == ERROR_STACK) {
    strcat(message, "Stack error: ");
    const char* stack_error_message =
        get_stack_error_message(error.error.stack_error);
    strcat(message, stack_error_message);
  }

  if (error.type == ERROR_TOKEN) {
    strcat(message, "Token error: ");
    const char* token_error_message =
        get_token_error_message(error.error.token_error);
    strcat(message, token_error_message);
  }

  if (error.type == ERROR_NONE) {
    strcat(message, "No error");
  }

  printf("%s\n", message);
}

void print_stack(Stack* stack) {
  printf("------\n");
  printf("Stack:\n");
  printf("------\n");
  for (int i = 0; i < stack->top; i++) {
    printf("Index: %d, Value: %f\n", i, stack->values[i]);
  }
  printf("\n");
}
