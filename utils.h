#include "stack.h"

STACK clear_null(struct STACK *target);
void get_input(struct STACK *target);
void stack_print(struct STACK *target);
int check_exception(struct STACK *target);
int isOper(char target);
STACK convert_postfix(struct STACK *target);
STACK reserve_stack(struct STACK *target);
STACK stack_push_stack(struct STACK *target,struct STACK *amount);