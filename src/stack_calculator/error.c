#include <stdio.h>
#include <string.h>

#include "calculator_types.h"

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
    case STACK_FLAG_ERROR:
      return "Flag Error";
    default:
      return "Unknown stack error";
  }
}

char* get_token_error_message(TokenError error) {
  switch (error) {
    case TOKEN_OK:
      return "Token ok";
    case TOKEN_INVALID_UNDEFINED:
      return "Invalid undefined symbol or token";
    case TOKEN_INVALID_NUMBER:
      return "Invalid number";
    case TOKEN_INVALID_OPERATOR:
      return "Invalid operator";
    case TOKEN_NULL_POINTER:
      return "Null pointer";
    case TOKEN_INVALID_ALPHA:
      return "Invalid alphabetical";
    default:
      return "Unknown token error";
  }
}

void handle_error(CalculatorError error, char current) {
  char message[100];  // Increased buffer size to handle longer error messages
  message[0] = '\0';  // Initialize the string properly

  if (error.type == ERROR_STACK) {
    strcat(message, "Stack error: ");
    const char* stack_error_message =
        get_stack_error_message(error.error.stack_error);
    strcat(message, stack_error_message);
  } else if (error.type == ERROR_TOKEN) {
    strcat(message, "Token error -- at char: ");

    // Handle non-printable characters safely
    if (current >= 32 && current <= 126) {
      // Printable ASCII character
      char current_str[2] = {current, '\0'};
      strcat(message, current_str);
    } else {
      // Non-printable character - show hex value
      char hex_str[8];
      snprintf(hex_str, sizeof(hex_str), "0x%02x -- ", (unsigned char)current);
      strcat(message, hex_str);
    }

    const char* token_error_message =
        get_token_error_message(error.error.token_error);
    strcat(message, token_error_message);
  } else if (error.type == ERROR_NONE) {
    strcat(message, "No error");
  } else {
    strcat(message, "Unknown error type");
  }

  printf("%s\n", message);
}