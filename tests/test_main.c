#include <stdlib.h>

#include "../unity/unity.h"
#include "test_scanner.h"
#include "test_stack.h"
#include "test_stack_calculator.h"

void setUp(void) {
}

void tearDown(void) {
}

int main(void) {
  UNITY_BEGIN();

  run_stack_tests();
  run_calculator_tests();
  run_scanner_tests();

  return UNITY_END();
}