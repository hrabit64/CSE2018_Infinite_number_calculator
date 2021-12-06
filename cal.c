#include "cal.h"


STACK sum(struct STACK *a,struct STACK *b){
    stack_swap(a,b);
    STACK *a_int = malloc(sizeof(STACK));
    a_int->next = NULL;

    STACK *b_int = malloc(sizeof(STACK));
    b_int->next = NULL;

    STACK *a_float = malloc(sizeof(STACK));
    a_float->next = NULL;

    STACK *b_float = malloc(sizeof(STACK));
    b_float->next = NULL;

    STACK *res = malloc(sizeof(STACK));
    res->next = NULL;

    char a_num[10];
    char b_num[10];
    char acc_c[10];

    int round = 0;
    int acc = 0;
    

    int isFloat = 0;
    //a의 소수 부분과 정수부분 나눠줌
    while(1)
    {   
        *a_num = pop(a);
        if(*a_num == '.'){
            isFloat = 1;
            while(1){
                *a_num = pop(a);
                if(*a_num == '\0'){
                    break;
                }
                push(a_float,*a_num);
            }
            break;
        }
        if(*a_num == '\0') break;

        push(a_int,*a_num);
    }

    //b의 정수 부분과 소수 부분 나눠줌
    while(1)
    {   
        *b_num = pop(b);
        if(*b_num == '.'){
            isFloat = 1;
            while(1){
                *b_num = pop(b);
                if(*b_num == '\0'){
                    break;
                }
                push(b_float,*b_num);
            }
            break;
        }
        if(*b_num == '\0') break;

        push(b_int,*b_num);
    }
    if(isFloat == 1) make_same_decimal(a_float,b_float);
    make_same_digit(a_int,b_int);

    //float 부분 연산
    int isLastNum = 1;
    if(isFloat == 1){
        while(1)
        {
            *a_num = pop(a_float);
            *b_num = pop(b_float);

            if(*a_num == '\0' && *b_num == '\0') break;
            acc = atoi(a_num) + atoi(b_num);
            
            
            if(round > 0) acc++;
            
            round = acc / 10;
            acc = acc % 10;
            sprintf(acc_c,"%d",acc);

            
            //만약 0이고, 마지막 자리라면 push 하지 않음.
            //소숫점 끝 자리 0을 없애주기 위함.
            if(acc == 0 && isLastNum == 1) continue;

            //마지막 자리가 아니라면 그냥 push
            else{
                push(res,*acc_c);
                isLastNum = 0;
            }
            
        }
        push(res,'.');
    }

    // 정수 부분 연산
    while(1)
        {

        *a_num = pop(a_int);
        *b_num = pop(b_int);

        if(*a_num == '\0' && *b_num == '\0') break;
        acc = atoi(a_num) + atoi(b_num);
        
        if(round > 0) acc++;
        round = acc / 10;
        acc = acc % 10;
        sprintf(acc_c,"%d",acc);
        push(res,*acc_c);
    }
    // 만약 정수 부분에서 올림이 있으면 올려줌
    if(round >= 1) push(res,'1');

    // 더이상 불필요한 스택 제거
    del_stack(a_int);
    del_stack(b_int);
    del_stack(a_float);
    del_stack(b_float);

    //중간 로그 출력
    printf("sum res : ");
    stack_print(res);


    return *res;
}


STACK calculate(struct STACK *target){
    
    STACK *acc = malloc(sizeof(STACK));
    acc->next = NULL;
    push(acc,' ');
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

        if(isOper(*num) >= 1){
            // 공백제거
            *idx = pop(acc);
            printf("found oper %c\n",*num);
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
                if(*idx == ' ' || *idx == '\0') break;

                push(b,*idx);
            }

            
            switch (*num)
            {
            case '+':
                // sum
                *cal_res = sum(a,b);
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
            stack_push_stack(acc,cal_res);
            printf("acc:");
            stack_print(acc);
        }

        else{
            push(acc,*num);
            printf("acc:");
            stack_print(acc);
        } 
        

        
    }
    
    del_stack(a);
    del_stack(b);
    del_stack(cal_res);
    return *acc;
}