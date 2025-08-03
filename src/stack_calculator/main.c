#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "error.h"
#include "scanner.h"
#include "stack.h"

void print_number(double num) {
  // Check if number has decimal part by comparing with its integer part
  if (num == (int)num) {
    printf("%.0f\n", num);  // Print without decimal
  } else {
    printf("%g\n", num);  // Print with decimal
  }
}

void print_result(Stack* stack) {
  double result;

  stack_peek(stack, &result);

  print_number(result);
}

void evaluate(Stack* stack, Scanner* scanner) {
  CalculatorError calc_error = scan_line(scanner, stack);

  if (calc_error.type != ERROR_NONE) {
    handle_error(calc_error, scanner->source[scanner->position]);

    print_stack(stack);
  } else {
    print_result(stack);
  }
}

static void repl(Stack* stack, Scanner* scanner) {
  char line[1024];

  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    strcat(scanner->source, line);

    evaluate(stack, scanner);
  }
}

static char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");

  // This can happen if the file doesn’t exist or the user doesn’t have access
  // to it. It’s pretty common—people mistype paths all the time.
  if (file == NULL) {
    int error = fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(error);
  }

  // classic c trick. we need to know the size of the file to allocate an
  // appropriate buffer. start by seeking to the end
  if (fseek(file, 0L, SEEK_END) != 0) {
    int error =
        fprintf(stderr, "Could not seek to end of file \"%s\".\n", path);
    (void)fclose(file);
    exit(error);
  }
  // then get the current position - that's the file size
  size_t fileSize = ftell(file);
  // then rewind to beginning
  // rewind(file);
  if (fseek(file, 0L, SEEK_SET) != 0) {
    int error =
        fprintf(stderr, "Could not seek to beginning of file \"%s\".\n", path);
    (void)fclose(file);
    exit(error);
  }

  // allocate the filesize + 1 (to make room for the null byte \0)
  char* buffer = (char*)malloc(fileSize + 1);

  // This is a much rarer error. if the user's machine can't allocate enough
  // memory to run this, then their is likely a larger systemic error.
  if (buffer == NULL) {
    int error = fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(error);
  }

  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  // an unlikely failure. but should still check for it.
  if (bytesRead < fileSize) {
    int error = fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(error);
  }

  buffer[bytesRead] = '\0';

  (void)fclose(file);

  return buffer;
}

int main(int argc, char* argv[]) {
  Stack   stack;
  Scanner scanner;

  stack_init(&stack);

  if (argc == 1) {
    scanner_init(&scanner, NULL, MODE_REPL);
    repl(&stack, &scanner);
  } else {
    if (argv[1] == NULL) {
      printf("No file provided\n");
      return 1;
    }

    char* file_contents = readFile(argv[1]);

    scanner_init(&scanner, file_contents, MODE_FILE);

    evaluate(&stack, &scanner);

    return 0;
  }

  stack_free(&stack);

  return 0;
}