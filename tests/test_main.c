#include <stdlib.h>

#include "../unity/unity.h"
#include "test_stack_calculator.h"

// void setUp(void) {
//   printf("Setting up unity\n");
// }

// void tearDown(void) {
//   printf("Tearing down unity\n");
// }

int main(void) {
  UNITY_BEGIN();

  run_calculator_tests();

  return UNITY_END();
}