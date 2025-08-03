#ifndef FLAG_H
#define FLAG_H

#include "calculator_types.h"
#include "scanner.h"

typedef enum
{
  BIN,  // binary
  HEX,  // hexadecimal
  DEC   // decimal
} FlagType;

bool is_flag(char c);
TokenError queue_flags(Scanner* scanner, char** flags);

#endif