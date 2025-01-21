#ifndef CALCULATOR_TYPES_H
#define CALCULATOR_TYPES_H

typedef enum
{
  ERROR_STACK,
  ERROR_TOKEN,
  ERROR_NONE
} ErrorType;

typedef enum
{
  STACK_OK,
  STACK_OVERFLOW,
  STACK_UNDERFLOW,
  STACK_DIVISION_BY_ZERO,
  STACK_NULL_POINTER,
  STACK_NAN,
  STACK_EVAL_ERROR
} StackError;

typedef enum
{
  TOKEN_OK,
  TOKEN_INVALID_UNDEFINED,
  TOKEN_INVALID_NUMBER,
  TOKEN_INVALID_OPERATOR,
  TOKEN_NULL_POINTER
} TokenError;

typedef struct
{
  ErrorType type;
  union {
    StackError stack_error;
    TokenError token_error;
  } error;
} CalculatorError;

#define CALCULATOR_OK 0

#endif