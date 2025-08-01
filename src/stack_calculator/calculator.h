// stack.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdbool.h>
#include <stdlib.h>

#include "scanner.h"
#include "stack.h"
#include "stack_calculator.h"

CalculatorError calculator_evaluate(Stack* stack, Scanner* scanner);

void print_result(Stack* stack);

#endif