#ifndef FLAG_H
#define FLAG_H

#include "calculator_types.h"
#include "scanner.h"


bool is_flag(char c);
void init_flags(Flags* flags);
void add_flag(Flags* flags, FlagType flag_type);
TokenError queue_flags(Scanner* scanner, Flags* flags);
void process_flags(double value, Flags flags);

#endif