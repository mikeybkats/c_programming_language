#ifndef SCANNER_H
#define SCANNER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "stack.h"
#include "token.h"

typedef struct
{
  const char* source;
  size_t      position;  // current position in source
  size_t      start;     // start of current token
} Scanner;

// Initialize a scanner with source text
void scanner_init(Scanner* scanner, const char* source);

// Check if we've reached the end of input
bool is_at_end(Scanner* scanner);

// Look at current character without consuming it
char peek(Scanner* scanner);

// Look at next character without consuming it
char peek_next(Scanner* scanner);

// Consume the current character. Increment the scanner. Return the char of the
// char just moved past
char advance(Scanner* scanner);

// Skip any whitespace characters
void skip_whitespace(Scanner* scanner);

// Check if current character matches expected, if it does advance the scanner,
// if it doesn't return false.
bool match(Scanner* scanner, char expected);

// Skip any whitespace first
// Then look at the current character and decide:

// If it's a digit: scan the full number
// If it's an operator: create an operator token
// If it's end of input: create EOF token
TokenError scan_token(Scanner* scanner, Token* token);

void scan_line(Scanner* scanner, Stack* stack);

#endif  // SCANNER_H