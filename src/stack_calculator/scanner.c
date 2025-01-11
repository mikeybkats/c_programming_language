#include "scanner.h"

#include <assert.h>

void scanner_init(Scanner* scanner, const char* source) {
  scanner->source   = source;
  scanner->position = 0;
  scanner->start    = 0;
}

bool is_at_end(Scanner* scanner) {
  assert(scanner != NULL && scanner->source != NULL &&
         "scanner -- is_at_end -- Null pointer error.");

  return scanner->source[scanner->position] == '\0';
}

char peek(Scanner* scanner) {
  assert(scanner != NULL && scanner->source != NULL &&
         "scanner -- peek -- Null pointer error.");

  if (is_at_end(scanner)) {
    return '\0';
  }

  return scanner->source[scanner->position];
}

char peek_next(Scanner* scanner) {
  assert(scanner != NULL && scanner->source != NULL &&
         "scanner -- peek_next -- Null pointer error.");

  if (is_at_end(scanner)) {
    return '\0';
  }

  return scanner->source[scanner->position + 1];
}

void advance(Scanner* scanner) {
  assert(scanner != NULL && scanner->source != NULL &&
         "scanner -- peek_advance -- Null pointer error.");

  scanner->position++;
}

void skip_whitespace(Scanner* scanner) {
  assert(scanner != NULL && scanner->source != NULL &&
         "scanner -- skip_whitespace -- Null pointer error.");

  while (!is_at_end(scanner)) {
    switch (scanner->source[scanner->position]) {
      case '\t':
      case '\r':
      case '\n':
      case ' ':
        advance(scanner);
        break;

      default:
        break;
    }
  }
}

bool match(Scanner* scanner, char expected) {
  assert(scanner != NULL && scanner->source != NULL &&
         "scanner -- match -- Null pointer error.");

  if (peek(scanner) == expected) {
    advance(scanner);
    return true;
  }
  return false;
}