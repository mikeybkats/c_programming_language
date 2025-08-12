#include "calculator_types.h"

char * get_stack_error_message(StackError error);
char* get_token_error_message(TokenError error);
void handle_error(CalculatorError* error, char current);