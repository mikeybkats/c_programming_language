#ifndef CALCULATOR_TYPES_H
#define CALCULATOR_TYPES_H

#include <stdlib.h>

#define MAX_FLAGS 16 
#define INT_MAX 2147483647

typedef enum
{
  MODE_REPL,
  MODE_FILE
} CalculatorMode;

typedef enum
{
  ERROR_STACK,
  ERROR_TOKEN,
  ERROR_FLAG,
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
  STACK_EVAL_ERROR,
  STACK_FLAG_ERROR
} StackError;

typedef enum
{
  TOKEN_OK,
  TOKEN_FLAG_OK,
  TOKEN_INVALID_ALPHA,
  TOKEN_INVALID_UNDEFINED,
  TOKEN_INVALID_NUMBER,
  TOKEN_INVALID_OPERATOR,
  TOKEN_NULL_POINTER,
  TOKEN_UNKOWN_FLAG
} TokenError;

typedef enum {
  FLAG_OK,
  FLAG_UNKOWN
} FlagError;

typedef struct
{
  ErrorType type;
  union {
    StackError stack_error;
    TokenError token_error;
    FlagError flag_error;
  } error;
} CalculatorError;

typedef enum {
  RESULT_VALUE,
  RESULT_ERROR,
  RESULT_NONE
} ResultType;


typedef enum
{
  FLAG_BIN,  // binary
  FLAG_HEX,  // hexadecimal
  FLAG_DEC   // decimal
} FlagType;

typedef struct {
 size_t length;
 FlagType flagType[MAX_FLAGS];
} Flags;

typedef struct {
   Flags flags;
   double value;
} CalculatorValue;

typedef struct 
{
  ResultType type;
  union {
    CalculatorError* error;
    CalculatorValue* value;
  } as;
} CalculatorResult;

#define CALCULATOR_OK 0

#endif