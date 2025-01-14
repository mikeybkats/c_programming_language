#ifndef TEST_SCANNER_H
#define TEST_SCANNER_H

#include "../src/stack_calculator/scanner.h"

void test_is_at_end(void);
void test_peek(void);
void test_peek_next(void);
void test_advance(void);
void test_skip_whitespace(void);
void test_match(void);
void test_scan_token(void);
void run_scanner_tests(void);

#endif