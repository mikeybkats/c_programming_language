#include "test_stack.h"

#include "../unity/unity.h"

Stack stack;

void setUp_stack(void) {
  stack_init(&stack);
}

void tearDown_stack(void) {
  stack_free(&stack);
}

void test_stack_init(void) {
  TEST_ASSERT_EQUAL_size_t(0, stack.top);
  TEST_ASSERT_NOT_NULL(stack.values);
  TEST_ASSERT_EQUAL_size_t(STACK_MAX_SIZE, stack.capacity);
  TEST_PASS();
}

void test_stack_free(void) {
  stack_free(&stack);
  TEST_ASSERT_NULL(stack.values);
  TEST_ASSERT_EQUAL_size_t(0, stack.top);
  TEST_ASSERT_EQUAL_size_t(0, stack.capacity);
  TEST_PASS();

  stack_init(&stack);
}

void test_stack_push(void) {
  stack_push(&stack, 42);
  TEST_ASSERT_EQUAL_INT8(42, stack.values[stack.top - 1]);
  stack_push(&stack, 11);
  TEST_ASSERT_EQUAL_INT8(11, stack.values[stack.top - 1]);
  stack_push(&stack, 33);
  TEST_ASSERT_EQUAL_INT8(33, stack.values[stack.top - 1]);

  TEST_ASSERT_EQUAL_INT8(42, stack.values[stack.top - 3]);
  TEST_ASSERT_EQUAL_INT8(11, stack.values[stack.top - 2]);

  TEST_PASS();
}

void test_stack_pop(void) {
  // Verify initialization
  double v1, v2, v3;

  // first in last out
  stack_push(&stack, 10);
  stack_push(&stack, 11);
  stack_push(&stack, 22);

  // first in last out
  stack_pop(&stack, &v1);
  stack_pop(&stack, &v2);
  stack_pop(&stack, &v3);

  TEST_ASSERT_EQUAL(22, v1);
  TEST_ASSERT_EQUAL(11, v2);
  TEST_ASSERT_EQUAL(10, v3);

  TEST_PASS();
}

void test_stack_peek(void) {
  double r1, r2, r3;

  stack_push(&stack, 10);
  stack_peek(&stack, &r1);

  stack_push(&stack, 11);
  stack_peek(&stack, &r2);

  stack_push(&stack, 22);
  stack_peek(&stack, &r3);

  TEST_ASSERT_EQUAL(10, r1);
  TEST_ASSERT_EQUAL(11, r2);
  TEST_ASSERT_EQUAL(22, r3);

  TEST_PASS();
}

void run_stack_tests(void) {
  setUp_stack();

  printf("\n-----------\n");
  printf("Stack Tests");
  printf("\n-----------\n");

  RUN_TEST(test_stack_init);
  RUN_TEST(test_stack_push);
  RUN_TEST(test_stack_pop);
  RUN_TEST(test_stack_peek);
  RUN_TEST(test_stack_free);
  tearDown_stack();
}