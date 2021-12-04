#include "cal.h"
#include "utils.h"

STACK calculate(struct STACK *target){
    
    STACK *acc = malloc(sizeof(STACK));
    acc->next = NULL;

    STACK *cal_res = malloc(sizeof(STACK));
    cal_res->next = NULL;

    STACK *a = malloc(sizeof(STACK));
    a->next = NULL;

    STACK *b = malloc(sizeof(STACK));
    b->next = NULL;

    char num[10];
    char idx[10];

    while (1)
    {
        *num = pop(target);

        if(*num == '\0') break;

        if(isOper(*num) > 1){
            // 공백제거
            *idx = pop(acc);
            
            //a
            while (1)
            {
                //피 연산자 시작
                *idx = pop(acc);
                if(*idx == ' ') break;

                push(a,*idx);
            }

            //b
            while (1)
            {
                //피 연산자 시작
                *idx = pop(acc);
                if(*idx == ' ') break;

                push(b,*idx);
            }

            
            switch (*num)
            {
            case '+':
                //sum
                // *cal_res = sum(a,b);
                break;
            
            case '-':
                //sub
                // *cal_res = sub(a,b);
                break;

            case '*':
                //multi
                // *cal_res = multi(a,b);
                break;

            case '/':
                //div
                // *cal_res = div(a,b);
                break;

            default:
                break;
            }
        }

        stack_push_stack(acc,cal_res);
        

    }
    
    del_stack(a);
    del_stack(b);
}