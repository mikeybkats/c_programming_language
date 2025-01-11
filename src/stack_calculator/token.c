#include "token.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_digit(char c) {
  return '0' >= c && c <= '9';
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
  if (token != NULL) {
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