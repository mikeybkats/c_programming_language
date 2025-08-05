#include "flag.h"

#include <stdio.h>
#include <stdlib.h>

#include "calculator_types.h"
#include "print.h"
#include "scanner.h"
#include "stack.h"

void add_flag(Flags* flags, FlagType flag_type) {
  if (flags == NULL) {
    return;
  }

  FlagType* new_flags = realloc(flags->flagType, sizeof(flags->flagType) + 1);

  if (new_flags == NULL) {
    return;
  }

  flags->flagType                = new_flags;
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
          case 'H':
          case 'h':
            add_flag(flags, FLAG_HEX);
            consume(scanner, 4);
          case 'D':
          case 'd':
            add_flag(flags, FLAG_DEC);
            consume(scanner, 4);
          default:
            return TOKEN_UNKOWN_FLAG;
        }
      }
      return TOKEN_FLAG_OK;
    }
  }
  return TOKEN_UNKOWN_FLAG;
}

StackError process_flags(Flags* flags, Stack* stack) {
  StackError err    = STACK_FLAG_ERROR;
  double*    result = malloc(sizeof(double));
  for (int i = 0; i < (int)flags->length; i++) {
    switch (flags->flagType[i]) {
      case FLAG_BIN:
        err = stack_peek(stack, result);
        print_bits(*result);
      case FLAG_HEX:
        err = stack_peek(stack, result);
        print_hexadecimal(*result);
      case FLAG_DEC:
        err = stack_peek(stack, result);
        print_decimal(*result);
      default:
        return err;
    }
  }
  return err;
};

bool is_flag(char c) {
  return c == ':';
}

void init_flags(Flags* flags) {
  if (flags == NULL) {
    return;
  }
  flags->length   = 0;
  flags->flagType = NULL;
}
