#include <stdio.h>
#include <string.h>

#include "calculator_types.h"
#include "scanner.h"

TokenError queue_flags(Scanner* scanner, char** flags) {
  int count = 0;
  while (!is_at_end(scanner)) {
    skip_whitespace(scanner);

    if (match(scanner, ':')) {
      char flag[10];
      int  flagCount = 0;

      while (!is_at_end(scanner)) {
        char c          = advance(scanner);
        flag[flagCount] = c;
        flagCount++;

        if (flagCount == 3) {
          flag[3] = '\0';
          break;
        }
      }

      flags[count] = malloc(((strlen(flag) + 1) * sizeof(char)));
      if (flags[count] == NULL) {
        return TOKEN_INVALID_UNDEFINED;
      }

      strcpy(flags[count], flag);

      count++;
    }
  }

  return TOKEN_UNKOWN_FLAG;
}

StackError process_flags(char** flags, Stack* stack);

bool is_flag(char c) {
  return c == ':';
}
