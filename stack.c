#include "stack.h"

//add new node and data at stack's head
void push(struct STACK *target, char data)
{
    struct STACK *pushNode = malloc(sizeof(struct STACK));
    pushNode -> next = target ->next;
    pushNode -> data = data;
    target -> next = pushNode;

}

//return target's top node data but it's tail, return \0(NULL)
char pop(struct STACK *target)
{
    char popData;

    if(target->next == NULL) return '\0';

    struct STACK *popNode = target->next;
    target -> next = popNode -> next;
    popData = popNode->data;

    free(popNode);
    
    return popData;

}
void del_head(struct STACK *target)
{

    if(target->next != NULL){
        
        struct STACK *popNode = target->next;
        target -> next = popNode -> next;
        free(popNode);
    }
        

}

char head(struct STACK *target)
{
    char popData[10];

    if(target->next == NULL) return '\0';

    struct STACK *headNode = target->next;
    *popData = headNode -> data;


    return *popData;
}

void head_set_sign(struct STACK *target,int sign){

    if(target->next == NULL);
    if(sign == 1) push(target,'$');
}

void del_stack(struct STACK *target)
{
    char idx[10];
    *idx = pop(target);
    while (*idx != '\0')
    {
        *idx = pop(target);
    }

    free(target);
    
}

