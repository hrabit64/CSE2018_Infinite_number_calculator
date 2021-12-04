#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct STACK{
    struct STACK *next;
    char data;

} STACK;

void push(struct STACK *target , char data);
char pop(struct STACK *target);
char head(struct STACK *target);
void del_stack(struct STACK *target);