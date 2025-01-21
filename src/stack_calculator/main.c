#include <stdio.h>

#include "calculator.h"
#include "stack.h"
#include "stack_calculator.h"

static void repl(Stack* stack) {
  char line[1024];

  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    CalculatorError calc_error = calculator_evaluate(line, stack);

    if (calc_error.type != ERROR_NONE) {
      printf("Error: %s\n", handle_error(calc_error));
    } else {
      print_result(stack);
    }
  }
}
int main() {
  Stack stack;
  stack_init(&stack);

  repl(&stack);

  stack_free(&stack);

  return 0;
}