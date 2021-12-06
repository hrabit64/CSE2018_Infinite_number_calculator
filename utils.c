#include "utils.h"


// clear null space and return cleaned stack
STACK clear_null(struct STACK *target){

    STACK *clear_stack = malloc(sizeof(STACK));
    clear_stack->next = NULL;
    
    char num[10]; 
    *num = pop(target);
    while (*num != '\0')
    {
        if(*num != ' ') {
            push(clear_stack,*num);
        }     
        *num = pop(target);  
    }
    return *clear_stack;
}



//get input while it get \n
void get_input(struct STACK *target){

    char num[10];
    scanf("%c",num);
    while (*num != '\n')
    {
        push(target,*num);
        scanf("%c",num);
    }

}



//print target stack
void stack_print(struct STACK *target){
    char out[10];
    STACK *next_node = malloc(sizeof(STACK));

    next_node = target->next;
    *out = next_node -> data;

    while (next_node != NULL) 
    {     
        printf("%c",*out);
        next_node = next_node -> next;
        if(next_node != NULL) *out = next_node -> data;
    } 

    printf("\n");
}


// 오류가 있는지 확인함. 만약 오류가 없다면 0을, 오류가 있다면 1을 반환함.
int check_exception(struct STACK *target){
    STACK *chcker = malloc(sizeof(STACK));
    chcker = target->next;

    // 괄호 갯수
    int left_bracket_counter = 0;
    int right_bracket_counter = 0;

    //피연산자 갯수
    int target_num_counter = 0;
    
    //연산자 갯수
    int oper_counter = 0;

    //이전 문자를 저장할 변수
    char pre_char[10];

    //현재 문자를 저장할 변수
    char check_char[10];

    //앞에 올 수 있는 것들
    //- , ( , 1~9
    //나머지는 오류 처리

    *pre_char = chcker -> data;

    if(!( (*pre_char == '-') || (*pre_char == '(') || (*pre_char > '0') || (*pre_char <= '9'))) 
    {
        printf("수식 맨 첫 문자로 나올 수 없는 문자입니다. : %c\n",*pre_char);
        return 1;
    }
    
    while(1){

        chcker = chcker -> next;
        if(chcker == NULL) break;
        *check_char = chcker -> data;

        //연산자가 두 번 연속으로 나오면 오류
        //단 (-1) 이런건 허용 처리
        if(*pre_char > '0' && *check_char > '0')
        {
            if(!((*pre_char == '(') || (*check_char == ')'))) 
            {
                printf("연산자는 두번 연속으로 나올 수 없습니다. 1: %c 2: %c\n",*pre_char,*check_char);
                return 1;
            }
        }

        //연산자 다음으로 나오는 첫 피연산자의 숫자가 0일 경우 예외처리
        // if(isOper(*pre_char) > 0 && *check_char == '0') 
        // {
        //     printf("피 1: %c 2: %c\n",*pre_char,*check_char);
        //     return 1;
        // }

        //연산자라면 연산자 갯수에 + 1
        if(isOper(*check_char) > 0) oper_counter++;

        //만약 피 연산자라면 0~9가 맞는지 확인하고 피 연산자의 갯수 + 1
        if(isOper(*check_char) == 0){
            if(!('0' <= *check_char <='9')) {
                printf("피 연산자는 0~9의 숫자로 구성되어야 합니다. %c\n",*check_char);
                return 1;
                }
            target_num_counter++;
        }

        if(isOper(*check_char) == 3){
            if(*check_char == ')') right_bracket_counter++;
            else if(*check_char == '(') left_bracket_counter++;
        }

        //왼쪽 괄호가 안나왔는데 오른쪽 괄호가 나오면 오류
        if(isOper(*check_char) == 3){
            if(*check_char == ')' && left_bracket_counter == 0) {
                printf("왼쪽 괄호 없이 오른쪽 괄호는 사용할 수 없습니다.\n");
                return 1;
                }
        }
        //이전 문자를 현재 문자로 업데이트
        *pre_char = *check_char;
    }
    //연산자가 없으면 오류
    if(oper_counter == 0) {
        printf("연산자가 존재하지 않습니다\n");
        return 1;
    }

    // 괄호 갯수가 다르면 오류
    if(left_bracket_counter != right_bracket_counter) {
        printf("괄호의 갯수가 다릅니다. left : %d  right : %d\n",left_bracket_counter,right_bracket_counter);
        return 1;
    }

    //피연산자가 없어도 오류
    if(target_num_counter == 0) {
        printf("피 연산자는 2개 이상 필요합니다.\n");
        return 1;
    }

    return 0;
}

int isOper(char target){
    
    switch (target)
    {
    case '(':
    case ')':
        return 3;


    case '+':
    case '-':
        return 1;


    case '*':
    case '/':
        return 2;

    
    default:
        return 0;

    }
}

// make postfix
STACK convert_postfix(struct STACK *target){

    STACK *postfix_stack = malloc(sizeof(STACK));
    postfix_stack->next = NULL;
    
    STACK *oper_stack = malloc(sizeof(STACK));
    oper_stack->next = NULL;


    int oper_priority = 0;
    char num[10];

    while(1){

        *num = pop(target);
        if(*num == '\0') break;

        oper_priority = isOper(*num);

        // 피 연산자일 때
        if(oper_priority < 1) push(postfix_stack,*num);

        //연산자 일 때
        else{

            //공백으로 피연산자랑 분리
            if(head(postfix_stack) != ' ') push(postfix_stack,' ');

            // )라면 ( 가 나올 때 까지 모든 연산자 출력
            if(*num == ')'){
                
                while (1)
                {   
                    *num = pop(oper_stack);
                    if(*num == '(') break;
                    push(postfix_stack,*num);
                }
            }

            // 앞에 들어있는거 보다 우선순위가 높거나, 괄호라면 oper stack에 푸쉬
            else if(oper_priority > isOper(head(oper_stack)) || isOper(head(oper_stack)) == 3) 
            {   
                push(oper_stack,*num);
            }
            
            // 우선순위가 같거나 낮으면 자신이 우선순위가 높을 때 까지 oper stack에서 pop
            else{
                while (1)
                {   
                    if(isOper(head(oper_stack)) < oper_priority) {
                        push(oper_stack,*num);
                        
                        break;
                    }
                    push(postfix_stack,pop(oper_stack));
                    if(head(postfix_stack) != ' ') push(postfix_stack,' ');
                }
            }
        }       
    }

    if(head(postfix_stack) != ' ') push(postfix_stack,' ');

    // 모든 피 연산자를 출력했다면, oper stack에 남은 요소 모두 출력
    while (1)
    {
        *num = pop(oper_stack);
        if(*num == '\0') break;
        push(postfix_stack,*num);
        if(head(postfix_stack) != ' ') push(postfix_stack,' ');
    }

    del_stack(oper_stack);
    
    return *postfix_stack;
}

//stack 뒤집기
STACK reserve_stack(struct STACK *target){
    
    STACK *reserve_stack = malloc(sizeof(STACK));
    reserve_stack->next = NULL;
    
    char num[10]; 
    *num = pop(target);
    while (*num != '\0')
    {
        push(reserve_stack,*num);
        *num = pop(target);  
    }

    return *reserve_stack;
}

// amount의 값을 모두 팝하여 target 스택에 푸쉬함.
STACK stack_push_stack(struct STACK *target,struct STACK *amount){
    char num[10];

    while (1)
    {
        *num = pop(amount);
        if(*num == '\0') break;
        push(target,*num);
    }
    
    return *target;
}
//소수점 동일하게
void make_same_decimal(struct STACK *a,struct STACK *b){

    STACK *a_output = malloc(sizeof(STACK));
    a_output->next = NULL;

    STACK *b_output = malloc(sizeof(STACK));
    b_output->next = NULL;

    char a_num[10];
    char b_num[10];

    *a = reserve_stack(a);
    *b = reserve_stack(b);
    


    while (1)
    {   
        *a_num = pop(a);
        *b_num = pop(b);

        if(*a_num == '\0'){
            while (1)
            {   
                if(*b_num == '\0'){
                    break;
                }
                push(b_output,*b_num);
                push(a_output,'0');
                *b_num = pop(b);
            }
            break;
        }

        else if(*b_num == '\0'){
            while (1)
            {   
                if(*a_num == '\0'){
                    break;
                    
                }
                push(a_output,*a_num);
                push(b_output,'0');
                *a_num = pop(b);
            }
            break;
        }

        else if(*a_num == '\0'&&*b_num == '\0'){
            push(a_output,*a_num);
            push(b_output,*b_num);
            break;
        }

        else{
            push(a_output,*a_num);
            push(b_output,*b_num);

        }
    }
    
    stack_push_stack(a,a_output);
    stack_push_stack(b,b_output);
    del_stack(b_output);
    del_stack(a_output);
}
//자리수 동일하게
void make_same_digit(struct STACK *a,struct STACK *b){

    STACK *a_output = malloc(sizeof(STACK));
    a_output->next = NULL;

    STACK *b_output = malloc(sizeof(STACK));
    b_output->next = NULL;

    char a_num[10];
    char b_num[10];    

    while (1)
    {   
        *a_num = pop(a);
        *b_num = pop(b);

        if(*a_num == '\0'){
            while (1)
            {   
                if(*b_num == '\0'){
                    break;
                }
                push(b_output,*b_num);
                push(a_output,'0');
                *b_num = pop(b);
            }
            break;
        }

        else if(*b_num == '\0'){
            while (1)
            {   
                if(*a_num == '\0'){
                    break;
                    
                }
                push(a_output,*a_num);
                push(b_output,'0');
                *a_num = pop(a);
            }
            break;
        }

        else if(*a_num == '\0'&&*b_num == '\0'){
            push(a_output,*a_num);
            push(b_output,*b_num);
            break;
        }

        else{
            push(a_output,*a_num);
            push(b_output,*b_num);

        }
    }

    stack_push_stack(a,a_output);
    stack_push_stack(b,b_output);
    
    del_stack(b_output);
    del_stack(a_output);
}

//스택을 서로 뒤 바꿈
void stack_swap(struct STACK *a,struct STACK *b){
    STACK *index = malloc(sizeof(STACK));
    index->next = b->next;

    b-> next = a->next;
    a->next = index->next;
    
    free(index);
}