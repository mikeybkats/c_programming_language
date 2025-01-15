#include "test_scanner.h"

#include "../unity/unity.h"

#define SCANNER_INIT_SOURCE "123 + 111\0"

Scanner scanner;
Token   token;

void setUp_scanner() {
  scanner_init(&scanner, SCANNER_INIT_SOURCE);
  token_init(&token);
}

void tearDown_scanner() {
}

void test_is_at_end(void) {
  bool isEnd = is_at_end(&scanner);

  TEST_ASSERT_FALSE(isEnd);

  scanner.position = 9;
  isEnd            = is_at_end(&scanner);
  TEST_ASSERT_TRUE(isEnd);
}

void test_peek(void) {
}
void test_peek_next(void) {
}
void test_advance(void) {
}

void test_skip_whitespace(void) {
  scanner.source   = "   1 + 5";
  scanner.position = 0;
  skip_whitespace(&scanner);

  TEST_ASSERT_EQUAL_size_t(3, scanner.position);

  scanner_init(&scanner, SCANNER_INIT_SOURCE);
}

void test_match(void) {
}

void test_scan_token(void) {
  scan_token(&scanner, &token);

  printf("\nTEST: token type: %u\n", token.type);
  printf("TEST: token value: %f\n", token.value);

  TEST_ASSERT_EQUAL_INT(TOKEN_NUMBER, token.type);
  TEST_ASSERT_DOUBLE_WITHIN(0.01, 123.0, token.value);
}

void run_scanner_tests(void) {
  setUp_scanner();

  printf("\n-------------\n");
  printf("Scanner Tests");
  printf("\n-------------\n");

  RUN_TEST(test_is_at_end);
  RUN_TEST(test_skip_whitespace);
  RUN_TEST(test_scan_token);

  tearDown_scanner();
}