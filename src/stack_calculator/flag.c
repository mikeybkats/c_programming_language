#include "flag.h"

#include <stdio.h>
#include <stdlib.h>

#include "calculator_types.h"
#include "scanner.h"

void add_flag(Flags* flags, FlagType flag_type) {
  printf("adding flag\n");
  if (flags == NULL) {
    return;
  }

  FlagType* new_flags = realloc(flags->flags, sizeof(flags->flags) + 1);

  if (new_flags == NULL) {
    return;
  }

  flags->flags                = new_flags;
  flags->flags[flags->length] = flag_type;
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
            consume(scanner);
            return TOKEN_FLAG_OK;
          case 'H':
          case 'h':
            add_flag(flags, FLAG_HEX);
            consume(scanner);
            return TOKEN_FLAG_OK;
          case 'D':
          case 'd':
            add_flag(flags, FLAG_DEC);
            consume(scanner);
            return TOKEN_FLAG_OK;
          default:
            return TOKEN_UNKOWN_FLAG;
        }
      }
    }
  }
  return TOKEN_UNKOWN_FLAG;
}

StackError process_flags(Flags* flags, Stack* stack) {
  for (int i = 0; i < (int)flags->length; i++) {
    switch (flags->flags[i]) {
      case FLAG_BIN:
        printf("FLAG_BIN\n");
        return STACK_OK;
      case FLAG_HEX:
        printf("FLAG_HEX\n");
        return STACK_OK;
      case FLAG_DEC:
        printf("FLAG_DEC\n");
        return STACK_OK;
      default:
        return STACK_FLAG_ERROR;
    }
  }
  return STACK_FLAG_ERROR;
};

bool is_flag(char c) {
  return c == ':';
}

void init_flags(Flags* flags) {
  if (flags == NULL) {
    return;
  }
  flags->length = 0;
  flags->flags  = NULL;
}
