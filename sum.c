#include "sum.h"

STACK sum(struct STACK *a,struct STACK *b){
    STACK *res = malloc(sizeof(STACK));
    res->next = NULL;
    return *res;
}
