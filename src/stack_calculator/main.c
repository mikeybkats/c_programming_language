#include <stdio.h>
#include <string.h>

#include "calculator.h"
#include "scanner.h"
#include "stack.h"

void evaluate(Stack* stack, Scanner* scanner) {
  CalculatorError calc_error = scan_line(scanner, stack);

  if (calc_error.type != ERROR_NONE) {
    handle_error(calc_error);

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
    strcat(scanner->source, "\n");

    evaluate(stack, scanner);
  }
}

static char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");

  // This can happen if the file doesn’t exist or the user doesn’t have access
  // to it. It’s pretty common—people mistype paths all the time.
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
  }

  // classic c trick. we need to know the size of the file to allocate an
  // appropriate buffer. start by seeking to the end
  fseek(file, 0L, SEEK_END);
  // then get the current position - that's the file size
  size_t fileSize = ftell(file);
  // then rewind to beginning
  rewind(file);

  // allocate the filesize + 1 (to make room for the null byte \0)
  char* buffer = (char*)malloc(fileSize + 1);

  // This is a much rarer error. if the user's machine can't allocate enough
  // memory to run this, then their is likely a larger systemic error.
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }

  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  // an unlikely failure. but should still check for it.
  if (bytesRead < fileSize) {
    fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(74);
  }

  buffer[bytesRead] = '\0';

  fclose(file);

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