#include "flag.h"

#include <stdio.h>
#include <stdlib.h>

#include "calculator_types.h"
#include "print.h"
#include "scanner.h"

void add_flag(Flags* flags, FlagType flag_type) {
  if (flags == NULL) {
    return;
  }

  flags->flagType[flags->length] = flag_type;
  flags->length++;
}

TokenError queue_flags(Scanner* scanner, Flags* flags) {
  while (!is_at_end(scanner)) {
    skip_whitespace(scanner);

    if (match(scanner, ':')) {
      while (!is_at_end(scanner)) {
        char c = advance(scanner);
        switch (c) {
          case 'B':
          case 'b':
            add_flag(flags, FLAG_BIN);
            consume(scanner, 4);
            break;
          case 'H':
          case 'h':
            add_flag(flags, FLAG_HEX);
            consume(scanner, 4);
            break;
          case 'D':
          case 'd':
            add_flag(flags, FLAG_DEC);
            consume(scanner, 4);
            break;
          default:
            return TOKEN_UNKOWN_FLAG;
        }
      }
      return TOKEN_FLAG_OK;
    }
  }
  return TOKEN_UNKOWN_FLAG;
}

void process_flags(double value, Flags flags) {
  for (int i = 0; i < (int)flags.length; i++) {
    switch (flags.flagType[i]) {
      case FLAG_BIN:
        print_bits(value);
        break;
      case FLAG_HEX:
        print_hexadecimal(value);
        break;
      case FLAG_DEC:
        print_decimal(value);
        break;
      default:
        print_decimal(value);
    }
  }
};

bool is_flag(char c) {
  return c == ':';
}

void init_flags(Flags* flags) {
  if (flags == NULL) {
    return;
  }
  flags->length = 0;
}
