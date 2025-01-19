#include "test_scanner.h"

#include "../unity/unity.h"

#define SCANNER_INIT_SOURCE "123 111 +\0"

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
  skip_whitespace(&scanner);
  scan_token(&scanner, &token);

  TEST_ASSERT_EQUAL_INT(TOKEN_NUMBER, token.type);
  TEST_ASSERT_DOUBLE_WITHIN(0.01, 123.0, token.value);

  token_init(&token);
  skip_whitespace(&scanner);
  scan_token(&scanner, &token);

  TEST_ASSERT_EQUAL_INT(TOKEN_NUMBER, token.type);

  skip_whitespace(&scanner);
  scan_token(&scanner, &token);

  TEST_ASSERT_EQUAL_INT(TOKEN_PLUS, token.type);
}

void test_scan_line(void) {
  Stack           stack;
  double          result = 0;
  StackError      peek_error;
  CalculatorError calc_error;

  stack_init(&stack);

  scanner_init(&scanner, "10 13 +");
  calc_error = scan_line(&scanner, &stack);
  peek_error = stack_peek(&stack, &result);
  TEST_ASSERT_EQUAL(STACK_OK, peek_error);
  TEST_ASSERT_EQUAL_INT(23, result);

  scanner_init(&scanner, "5 4 ^");
  calc_error = scan_line(&scanner, &stack);
  peek_error = stack_peek(&stack, &result);
  TEST_ASSERT_EQUAL(STACK_OK, peek_error);
  TEST_ASSERT_EQUAL_INT(pow(5, 4), result);

  scanner_init(&scanner, "5 5 *");
  calc_error = scan_line(&scanner, &stack);
  peek_error = stack_peek(&stack, &result);
  TEST_ASSERT_EQUAL(STACK_OK, peek_error);
  TEST_ASSERT_EQUAL_INT(5 * 5, result);

  scanner_init(&scanner, "5 20 -");
  calc_error = scan_line(&scanner, &stack);
  peek_error = stack_peek(&stack, &result);
  TEST_ASSERT_EQUAL(STACK_OK, peek_error);
  TEST_ASSERT_EQUAL_INT(-15, result);

  scanner_init(&scanner, "20 5 /");
  calc_error = scan_line(&scanner, &stack);
  peek_error = stack_peek(&stack, &result);
  TEST_ASSERT_EQUAL(STACK_OK, peek_error);
  TEST_ASSERT_EQUAL_INT(4, result);

  TEST_ASSERT_EQUAL(ERROR_NONE, calc_error.type);

  stack_free(&stack);
}

void run_scanner_tests(void) {
  setUp_scanner();

  printf("\n-------------\n");
  printf("Scanner Tests");
  printf("\n-------------\n");

  RUN_TEST(test_is_at_end);
  RUN_TEST(test_skip_whitespace);
  RUN_TEST(test_scan_token);
  RUN_TEST(test_scan_line);

  tearDown_scanner();
}