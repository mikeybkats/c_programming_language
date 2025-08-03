#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>

#include "calculator_types.h"

typedef enum
{
  TOKEN_PLUS,         // +
  TOKEN_MINUS,        // -
  TOKEN_MULTIPLY,     // *
  TOKEN_DIVIDE,       // /
  TOKEN_POWER,        // ^
  TOKEN_SQRT,         // sqrt
  TOKEN_NUMBER,       // 123, 45.67
  TOKEN_AND,          // & - bitwise and
  TOKEN_OR,           // | - bitwise or
  TOKEN_XOR,          // x| - bitwise exlusive or
  TOKEN_NOT,          // ! - bitwise not
  TOKEN_LEFT_SHIFT,   // << - bitwise left shift
  TOKEN_RIGHT_SHIFT,  // >> - bitwise right shift
  TOKEN_MSB,          // msb - most significant bit
  TOKEN_EOF,          // end of input
  TOKEN_FLAG,         // : - begins with colon
  TOKEN_UNDEFINED
} TokenType;

/**
 * @brief Token structure
 *
 * @param type TokenType
 * @param value double (used for TOKEN_NUMBER)
 */
typedef struct
{
  TokenType type;
  double    value;  // used for TOKEN_NUMBER
} Token;

CalculatorError return_token_error(TokenError error);

TokenError token_init(Token* token);

// Helper functions
bool is_digit(char c);
bool is_alpha(char c);
bool is_operator(char c);

// Create tokens
// these functions only get called after making the appropriate checks
TokenError make_number(double value, Token* token);
TokenError make_operator(char op, Token* token);
TokenError make_eof(Token* token);

StackError evaluate_token(Token* token, Stack* stack);

#endif  // TOKEN_H