#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>

#include "stack.h"

typedef enum
{
  TOKEN_OK,
  TOKEN_INVALID_UNDEFINED,
  TOKEN_INVALID_NUMBER,
  TOKEN_INVALID_OPERATOR,
  TOKEN_NULL_POINTER
} TokenError;

typedef enum
{
  TOKEN_PLUS,      // +
  TOKEN_MINUS,     // -
  TOKEN_MULTIPLY,  // *
  TOKEN_DIVIDE,    // /
  TOKEN_POWER,     // ^
  TOKEN_SQRT,      // s
  TOKEN_NUMBER,    // 123, 45.67
  TOKEN_EOF,       // end of input
  TOKEN_UNDEFINED
} TokenType;

typedef struct
{
  TokenType type;
  double    value;  // used for TOKEN_NUMBER
} Token;

TokenError token_init(Token* token);

// Helper functions
bool is_digit(char c);
bool is_operator(char c);

// Create tokens
// these functions only get called after making the appropriate checks
TokenError make_number(double value, Token* token);
TokenError make_operator(char op, Token* token);
TokenError make_eof(Token* token);

StackError evaluate_token(Token* token, Stack* stack);

#endif  // TOKEN_H