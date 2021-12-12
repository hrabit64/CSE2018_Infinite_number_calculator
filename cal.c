#include "cal.h"
// b - a
STACK sub(struct STACK *a,struct STACK *b){
    printf("sub...\n");
    stack_print(a);
    stack_print(b);
    //부호처리
    // - b + a
    if(head(a) == '$' && head(b) == '$'){
        del_head(a);
        return sub(b,a);
    }
    else if(head(a) == '$'){
        del_head(a);
        return sum(a,b);
    }
    // -b - a
    // - (b+a)
    else if(head(b) == '$'){
        push(a,'$');
        return sum(a,b);
    }
    //정수 부분 저장할 스택
    STACK *a_int = malloc(sizeof(STACK));
    a_int->next = NULL;

    STACK *b_int = malloc(sizeof(STACK));
    b_int->next = NULL;

    //소수 부분 저장할 스택
    STACK *a_float = malloc(sizeof(STACK));
    a_float->next = NULL;

    STACK *b_float = malloc(sizeof(STACK));
    b_float->next = NULL;

    //결과 저정할 스택
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

    int isneg = 1;

    //대소 비교
    STACK *a_next = malloc(sizeof(STACK));
    STACK *b_next = malloc(sizeof(STACK));
    
    //두 스택을 스압할지 여부
    int dochange = 0;

    //두 스택이 같은지 확인
    int isSame = 1;

    //정수부분 비교
    *a_int = reserve_stack(a_int);
    *b_int = reserve_stack(b_int);
    a_next = a_int ->next;
    b_next = b_int ->next;

    while (1)
    {   
        *a_num = a_next -> data;
        *b_num = b_next -> data;
        //b가 더 크다면 while문 종료
        if(*b_num > *a_num){
            dochange = 1;
            isSame = 0;
            break;
            }
        
        if(*b_num < *a_num){
            dochange = 0;
            isSame = 0;
            
            break;
            }

        a_next = a_next ->next;
        b_next = b_next ->next;

        if(a_next == NULL) break;
    }
    *a_int = reserve_stack(a_int);
    *b_int = reserve_stack(b_int);

    // *a_int = reserve_stack(a_int);
    // *b_int = reserve_stack(b_int);
    if(isSame != 0 && isFloat == 1)
    {
    //정수가 동일하다면, 소수점 비교
    *a_float = reserve_stack(a_float);
    *b_float = reserve_stack(b_float);
    a_next = a_float ->next;
    b_next = b_float ->next;
        
        while (1)
        {   
            *a_num = a_next -> data;
            *b_num = b_next -> data;

            //b가 더 크다면 while문 종료
            if(*b_num > *a_num){
                dochange = 1;
                isSame = 0;
                break;
                }
            
            if(*b_num < *a_num){
                dochange = 0;
                isSame = 0;
                break;
                }

            a_next = a_next ->next;
            b_next = b_next ->next;

            if(a_next == NULL) break;
        }
        *a_float = reserve_stack(a_float);
        *b_float = reserve_stack(b_float);
    }
    
    if(isSame == 1){
        push(res,'0');
        return *res;
    }

    if(dochange != 0){
        stack_swap(a_int,b_int);
        stack_swap(a_float,b_float);
        isneg = 0;
    }

    //float 부분 연산

    int isLastNum = 1;

    if(isFloat == 1){
        while(1)
        {
            *a_num = pop(a_float);
            *b_num = pop(b_float);

            if(*a_num == '\0') break;
            acc = atoi(a_num) - atoi(b_num);
            if(round == 1)
            {
                acc -= 1;
            }

            if(acc < 0)
            {
                acc += 10;
                round = 1;
            } 

            else round = 0;

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
        if(isLastNum == 0){
            push(res,'.');
        }
        
    }
    
    // 정수 부분 연산
    while(1)
        {

        *a_num = pop(a_int);
        *b_num = pop(b_int);

        if(*a_num == '\0') break;

        acc = atoi(a_num) - atoi(b_num);
            if(round == 1)
            {
                acc -= 1;
            }

            if(acc < 0)
            {
                acc += 10;
                round = 1;
            } 
            else round = 0;

            sprintf(acc_c,"%d",acc);
            push(res,*acc_c);
    }
    //앞에 0을 제거해줌
    while (1)
    {
        if(head(res) == '0'){
            del_head(res);
            if(head(res) == '.'){
                push(res,'0');
                break;
            }
        }
        else if(head(res) == ' ') continue;
        else break;
    }
    
    // 만약 정수 부분에서 올림이 있으면 올려줌
    // 더이상 불필요한 스택 제거
    del_stack(a_int);
    del_stack(b_int);
    del_stack(a_float);
    del_stack(b_float);

    //부호 지정
    printf("------\n");
    head_set_sign(res,isneg);
    stack_print(res);
    return *res;
}


//-----------------------------------------------------
//-----------------------------------------------------
STACK sum(struct STACK *a,struct STACK *b){
    printf("sum...\n");
    stack_print(a);
    stack_print(b);
    int isneg = 0;

    // 부호처리
    if(head(a) == '$' && head(b) == '$'){
        isneg = 1;
        del_head(a);
        del_head(b);
    }
    else if(head(a) == '$'){
        del_head(a);
        return sub(a,b);
    }

    else if(head(b) == '$') {
        del_head(b);
        return sub(b,a);
    }


    //정수 부분 저장할 스택
    STACK *a_int = malloc(sizeof(STACK));
    a_int->next = NULL;

    STACK *b_int = malloc(sizeof(STACK));
    b_int->next = NULL;

    //소수 부분 저장할 스택
    STACK *a_float = malloc(sizeof(STACK));
    a_float->next = NULL;

    STACK *b_float = malloc(sizeof(STACK));
    b_float->next = NULL;

    //결과 저정할 스택
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

            if(*a_num == '\0') break;
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

        if(*a_num == '\0') break;
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
    
    head_set_sign(res,isneg);
    return *res;
}

//-----------------------------------------------------
//-----------------------------------------------------
//b*a
STACK multi(struct STACK *a,struct STACK *b){
    printf("multi...\n");
    stack_print(a);
    stack_print(b);
    int isneg = 0;

    //소수점 자리를 셀 스택 선언
    STACK *float_counter = malloc(sizeof(STACK));
    float_counter->next = NULL;

    STACK *one = malloc(sizeof(STACK));
    one->next = NULL;

    push(float_counter,'0');
    push(one,'1');
    // 부호처리

    if(head(a) == '$' && head(b) == '$'){
        isneg = 0;
        del_head(a);
        del_head(b);
    }
    else if(head(a) == '$') isneg = 1;
    else if(head(b) == '$') isneg = 1;

    //결과 저정할 스택
    STACK *res = malloc(sizeof(STACK));
    res->next = NULL;

    push(res,'0');
    //소숫점 자리수를 셈 (세면서 소숫점 나오면 제거)
    //a
    STACK *idx = malloc(sizeof(STACK));
    idx->next = NULL;
    char num[10];
    //.이 나온 직후 부터 숫자 셈
    int start_counter = 0;
    while (1)
    {   
        *num = pop(a);
        if(*num == '\0') break;
        if(*num == '.'){
            start_counter = 1;

            continue;
        }
        if(start_counter == 1){
            *float_counter = sum(float_counter,one);
            push(one,'1');
        }
        push(idx,*num);
    }
    stack_swap(a,idx);
    
    //b도 세어줌
    start_counter = 0;

    while (1)
    {   
        *num = pop(b);
        if(*num == '\0') break;
        if(*num == '.'){
            start_counter = 1;
            continue;
        }
        if(start_counter == 1){
            *float_counter = sum(float_counter,one);
            push(one,'1');
        }
        push(idx,*num);
    }
    stack_swap(b,idx);
    
    

    char a_num[10];
    char b_num[10];
    char acc_c[10];

    int round = 0;
    int acc = 0;

    STACK *zero_counter = malloc(sizeof(STACK));
    zero_counter->next = NULL;

    STACK *zero_counter_using = malloc(sizeof(STACK));
    zero_counter_using->next = NULL;

    push(zero_counter,'0');
    push(zero_counter_using,'0');

    STACK *next_node = malloc(sizeof(STACK));
    while (1)
    {
        *a_num = pop(a);
        if(*a_num == '\0') break;

        next_node = b->next;
        *b_num = next_node -> data;

        while (1)
        {
            acc = atoi(a_num) * atoi(b_num);
        
            if(round > 0) acc += round;
            round = acc / 10;
            acc = acc % 10;
            sprintf(acc_c,"%d",acc);
            push(idx,*acc_c);

            next_node = next_node -> next;
            if(head(next_node) == '\0') break;
            *b_num = next_node -> data;
        }
        *zero_counter = sum(zero_counter,one);
        push(one,'1');
        stack_copy(zero_counter,zero_counter_using);

        while (1)
        {
            *num = head(zero_counter_using);
            if(*num == '0') break;
            push(idx,'0');
            *zero_counter_using = sub(one,zero_counter_using);
            push(one,'1');

        }
        
        *res = sum(res,idx);
    }
    stack_print(zero_counter);
    return *res;
}

//-----------------------------------------------------
//-----------------------------------------------------

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

        if(isOperSign(*num) >= 1){


            // 공백제거
            *idx = pop(acc);

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
                *cal_res = sub(a,b);
                break;

            case '*':
                //multi
                *cal_res = multi(a,b);
                break;

            case '/':
                //multi
                *cal_res = sum(a,b);
                break;

            default:
                break;
            }
            if(head(acc) != ' ') push(acc,' ');
            stack_push_stack(acc,cal_res);
            if(head(acc) != '\0'){
            printf("acc:\n");
            stack_print(acc);
        }
        }

        else{
            push(acc,*num);
            if(head(acc) != '\0'){
            printf("acc:\n");
            stack_print(acc);
        }
        } 

        

        
    }
    
    del_stack(a);
    del_stack(b);
    del_stack(cal_res);
    return *acc;
}