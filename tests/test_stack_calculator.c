#include "test_stack_calculator.h"

#include "../unity/unity.h"

Stack stack;

void setUp_calculator(void) {
  stack_init(&stack);
}

void tearDown_calculator(void) {
  stack_free(&stack);
}

void test_calc_add(void) {
  int x, y;
  x = 10;
  y = 11;

  stack_push(&stack, x);
  stack_push(&stack, y);
  calc_add(&stack);

  TEST_ASSERT_EQUAL_INT(21, stack.values[stack.top - 1]);
};

void test_calc_subtract(void) {
  double x, y;
  x = 11;
  y = 31;

  stack_push(&stack, x);
  stack_push(&stack, y);
  calc_subtract(&stack);

  TEST_ASSERT_EQUAL_INT(-20, stack.values[stack.top - 1]);
};

void test_calc_multiply(void) {
  double x, y;
  x = 10;
  y = 11;

  stack_push(&stack, x);
  stack_push(&stack, y);
  calc_multiply(&stack);

  TEST_ASSERT_EQUAL_INT(110, stack.values[stack.top - 1]);
};

void test_calc_divide(void) {
  double x, y;
  x = 100;
  y = 10;

  stack_push(&stack, x);
  stack_push(&stack, y);
  calc_divide(&stack);

  TEST_ASSERT_EQUAL_INT(10, stack.values[stack.top - 1]);
};

void test_calc_square_root(void) {
  double x;
  x = 100;

  stack_push(&stack, x);
  calc_square_root(&stack);

  TEST_ASSERT_EQUAL_INT(10, stack.values[stack.top - 1]);
};

void test_calc_power(void) {
  double x, y;
  x = 10;
  y = 2;

  stack_push(&stack, x);
  stack_push(&stack, y);
  calc_power(&stack);

  TEST_ASSERT_EQUAL_INT(100, stack.values[stack.top - 1]);
};

void run_calculator_tests(void) {
  setUp_calculator();

  printf("\n----------------\n");
  printf("Calculator Tests");
  printf("\n----------------\n");

  RUN_TEST(test_calc_add);
  RUN_TEST(test_calc_subtract);
  RUN_TEST(test_calc_multiply);
  RUN_TEST(test_calc_divide);
  RUN_TEST(test_calc_square_root);
  RUN_TEST(test_calc_power);

  tearDown_calculator();
}