#include "scanner.h"

#include <assert.h>
#include <stdio.h>

#define MAX_NUMBER_LENGTH 32

void scanner_init(Scanner* scanner, const char* source) {
  // stack allocated scanner
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

char advance(Scanner* scanner) {
  assert(scanner != NULL && scanner->source != NULL &&
         "scanner -- peek_advance -- Null pointer error.");

  scanner->position++;
  return scanner->source[scanner->position - 1];
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
        return;
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

TokenError scan_token(Scanner* scanner, Token* token) {
  // // get current character
  char current = peek(scanner);

  // // if it's a digit
  if (is_digit(current)) {
    char string_number[MAX_NUMBER_LENGTH];
    int  count = 0;

    while (is_digit(current)) {
      if (count > MAX_NUMBER_LENGTH) {
        return TOKEN_INVALID_NUMBER;
      }

      string_number[count] = advance(scanner);  // returns char just consumed
      current              = peek(scanner);     // returns new current char

      count++;
    }

    return make_number(atof(string_number), token);
  }

  if (is_operator(current)) {
    return make_operator(advance(scanner), token);
  }

  return TOKEN_INVALID_UNDEFINED;
}

CalculatorError scan_line(Scanner* scanner, Stack* stack) {
  while (!is_at_end(scanner)) {
    skip_whitespace(scanner);

    Token token;
    token_init(&token);

    TokenError err_t = scan_token(scanner, &token);

    if (err_t != TOKEN_OK) {
      return return_token_error(err_t);
    }

    StackError err_s = evaluate_token(&token, stack);

    if (err_s != STACK_OK) {
      return return_stack_error(err_s);
    }
  }

  CalculatorError err;
  err.type = ERROR_NONE;
  return err;
}
