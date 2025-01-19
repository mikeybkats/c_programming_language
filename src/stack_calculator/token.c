#include "token.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "calculator_types.h"
#include "stack_calculator.h"

CalculatorError return_token_error(TokenError token_error) {
  CalculatorError error;
  error.type              = ERROR_TOKEN;
  error.error.token_error = token_error;

  return error;
}

TokenError token_init(Token* token) {
  token->type  = TOKEN_UNDEFINED;
  token->value = NAN;

  return TOKEN_OK;
}

bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

bool is_operator(char c) {
  switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case 's':
      return true;
    default:
      return false;
  }
}

TokenError make_number(double value, Token* token) {
  if (!isnan(value)) {
    token->type  = TOKEN_NUMBER;
    token->value = value;
    return TOKEN_OK;
  }

  return TOKEN_INVALID_NUMBER;
}

TokenError make_operator(char op, Token* token) {
  if (token == NULL) {
    return TOKEN_NULL_POINTER;
  }

  switch (op) {
    case '+':
      token->type = TOKEN_PLUS;
      break;
    case '-':
      token->type = TOKEN_MINUS;
      break;
    case '*':
      token->type = TOKEN_MULTIPLY;
      break;
    case '/':
      token->type = TOKEN_DIVIDE;
      break;
    case '^':
      token->type = TOKEN_POWER;
      break;
    case 's':
      token->type = TOKEN_SQRT;
      break;
  }

  return TOKEN_OK;
}

TokenError make_eof(Token* token) {
  if (token == NULL) {
    return TOKEN_NULL_POINTER;  // Using our new error type
  }

  token->type = TOKEN_EOF;
  return TOKEN_OK;
}

StackError evaluate_token(Token* token, Stack* stack) {
  switch (token->type) {
    case TOKEN_PLUS:
      return calc_add(stack);
    case TOKEN_MINUS:
      return calc_subtract(stack);
    case TOKEN_MULTIPLY:
      return calc_multiply(stack);
    case TOKEN_DIVIDE:
      return calc_divide(stack);
    case TOKEN_POWER:
      return calc_power(stack);
    case TOKEN_SQRT:
      return calc_square_root(stack);
    case TOKEN_NUMBER:
      return stack_push(stack, token->value);

    default:
      return STACK_EVAL_ERROR;
  }
}
