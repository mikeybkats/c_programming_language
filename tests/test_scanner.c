#include "test_scanner.h"

#include <math.h>

#include "../unity/unity.h"

#define SCANNER_INIT_SOURCE "123 111 +"

Scanner scanner;
Token   token;

void setUp_scanner() {
  scanner_init(&scanner, SCANNER_INIT_SOURCE, MODE_FILE);
  token_init(&token);
}

void tearDown_scanner() {
  free(scanner.source);
  scanner.source = NULL;
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
  char scratch[] = "   1 + 5";
  free(scanner.source);
  scanner.source   = scratch;
  scanner.position = 0;
  scanner.mode     = MODE_FILE;
  skip_whitespace(&scanner);

  TEST_ASSERT_EQUAL_size_t(3, scanner.position);

  scanner_init(&scanner, SCANNER_INIT_SOURCE, MODE_FILE);
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
  Stack               stack;
  double              result = 0;
  StackError          peek_error;
  CalculatorResult* calc_result;

  stack_init(&stack);

  free(scanner.source);
  scanner_init(&scanner, "10 13 +", MODE_FILE);
  calc_result = scan_line(&scanner, &stack);
  TEST_ASSERT_NOT_NULL(calc_result);
  TEST_ASSERT_EQUAL(RESULT_VALUE, calc_result->type);
  free_calculator_result(calc_result);
  peek_error = stack_peek(&stack, &result);
  TEST_ASSERT_EQUAL(STACK_OK, peek_error);
  TEST_ASSERT_DOUBLE_WITHIN(0.01, 23.0, result);

  free(scanner.source);
  scanner_init(&scanner, "5 4 ^", MODE_FILE);
  calc_result = scan_line(&scanner, &stack);
  TEST_ASSERT_NOT_NULL(calc_result);
  TEST_ASSERT_EQUAL(RESULT_VALUE, calc_result->type);
  free_calculator_result(calc_result);
  peek_error = stack_peek(&stack, &result);
  TEST_ASSERT_EQUAL(STACK_OK, peek_error);
  TEST_ASSERT_DOUBLE_WITHIN(0.01, pow(5, 4), result);

  free(scanner.source);
  scanner_init(&scanner, "5 5 *", MODE_FILE);
  calc_result = scan_line(&scanner, &stack);
  TEST_ASSERT_NOT_NULL(calc_result);
  TEST_ASSERT_EQUAL(RESULT_VALUE, calc_result->type);
  free_calculator_result(calc_result);
  peek_error = stack_peek(&stack, &result);
  TEST_ASSERT_EQUAL(STACK_OK, peek_error);
  TEST_ASSERT_DOUBLE_WITHIN(0.01, 25.0, result);

  free(scanner.source);
  scanner_init(&scanner, "5 20 -", MODE_FILE);
  calc_result = scan_line(&scanner, &stack);
  TEST_ASSERT_NOT_NULL(calc_result);
  TEST_ASSERT_EQUAL(RESULT_VALUE, calc_result->type);
  free_calculator_result(calc_result);
  peek_error = stack_peek(&stack, &result);
  TEST_ASSERT_EQUAL(STACK_OK, peek_error);
  TEST_ASSERT_DOUBLE_WITHIN(0.01, -15.0, result);

  free(scanner.source);
  scanner_init(&scanner, "20 5 /", MODE_FILE);
  calc_result = scan_line(&scanner, &stack);
  TEST_ASSERT_NOT_NULL(calc_result);
  TEST_ASSERT_EQUAL(RESULT_VALUE, calc_result->type);
  free_calculator_result(calc_result);
  peek_error = stack_peek(&stack, &result);
  TEST_ASSERT_EQUAL(STACK_OK, peek_error);
  TEST_ASSERT_DOUBLE_WITHIN(0.01, 4.0, result);

  free(scanner.source);
  scanner_init(&scanner, "2 3 4 + *", MODE_FILE);
  calc_result = scan_line(&scanner, &stack);
  TEST_ASSERT_NOT_NULL(calc_result);
  TEST_ASSERT_EQUAL(RESULT_VALUE, calc_result->type);
  free_calculator_result(calc_result);
  peek_error = stack_peek(&stack, &result);
  TEST_ASSERT_EQUAL(STACK_OK, peek_error);
  TEST_ASSERT_DOUBLE_WITHIN(0.01, 14.0, result);

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