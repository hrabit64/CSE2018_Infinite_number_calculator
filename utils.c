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


// check exception. if normal, return 0. but it has error, return -1
int check_exception(struct STACK *target){
    // error
    int left_bracket_counter = 0;
    int right_bracket_counter = 0;
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
                    push(postfix_stack,' ');   
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
                    push(postfix_stack,' ');
                }
            }
        }       
    }

    // 모든 피 연산자를 출력했다면, oper stack에 남은 요소 모두 출력
    while (1)
    {
        *num = pop(oper_stack);
        if(*num == '\0') break;
        push(postfix_stack,*num);
        push(postfix_stack,' ');
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

