#include "stack.h"

STACK clear_null(struct STACK *target);
void get_input(struct STACK *target);
void stack_print(struct STACK *target);
int check_exception(struct STACK *target);
int check_NULL_exception(struct STACK *target);
int isOper(char target);
int isOperSign(char target);
STACK convert_postfix(struct STACK *target);
STACK reserve_stack(struct STACK *target);
STACK stack_push_stack(struct STACK *target,struct STACK *amount);
STACK formula_edit(struct STACK *target);
void make_same_decimal(struct STACK *a,struct STACK *b);
void make_same_digit(struct STACK *a,struct STACK *b);
void stack_swap(struct STACK *a,struct STACK *b);