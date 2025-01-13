#include "test_scanner.h"

#include "../unity/unity.h"

Scanner scanner;
Token   token;

void setUp_scanner() {
  scanner_init(&scanner, "123 + 111");
  token_init(&token);
}

void tearDown_scanner() {
}

void test_scan_token(void) {
  printf("scanner source: %s\n", scanner.source);
  printf("scanner position: %zu\n", scanner.position);
  printf("scanner start: %zu\n", scanner.start);

  printf("token type: %u\n", token.type);
  printf("token value: %f\n", token.value);

  scan_token(&scanner, &token);

  TEST_FAIL();
}

void run_scanner_tests(void) {
  setUp_scanner();

  printf("\n-------------\n");
  printf("Scanner Tests");
  printf("\n-------------\n");

  RUN_TEST(test_scan_token);

  tearDown_scanner();
}