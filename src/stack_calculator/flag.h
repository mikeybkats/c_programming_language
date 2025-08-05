#ifndef FLAG_H
#define FLAG_H

#include "calculator_types.h"
#include "scanner.h"

typedef enum
{
  FLAG_BIN,  // binary
  FLAG_HEX,  // hexadecimal
  FLAG_DEC   // decimal
} FlagType;


typedef struct {
 size_t length;
 FlagType* flagType;
} Flags;

bool is_flag(char c);
void init_flags(Flags* flags);
void add_flag(Flags* flags, FlagType flag_type);
TokenError queue_flags(Scanner* scanner, Flags* flags);
StackError process_flags(Flags* flags, Stack* stack);

#endif