#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Sign_type{
    positive = 0,
    negative
};

typedef struct STACK{

    struct STACK *next;
    char data;
    enum Sign_type sign;
} STACK;

void push(struct STACK *target , char data);
char pop(struct STACK *target);
char head(struct STACK *target);
void head_set_sign(struct STACK *target,int sign);
void del_stack(struct STACK *target);