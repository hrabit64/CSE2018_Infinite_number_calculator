#include "cal.h"

void run(){
    STACK *input_top = malloc(sizeof(STACK));
    input_top ->next = NULL;

    STACK *test = malloc(sizeof(STACK));
    test -> next = NULL;

    get_input(input_top);
    //공백제거
    if(check_NULL_exception(input_top) == 1){
        printf("입력값이 비어있습니다.\n");
        exit(0);
    }
    *input_top = clear_null(input_top);
    stack_print(input_top);
    *input_top = formula_edit(input_top);
  
    //스택 출력
    printf("---------------\n");
    printf("input\n");
    printf("---------------\n");
    stack_print(input_top);
    printf("\n\n\n");
    // 예외처리
    if(check_exception(input_top) == 1) exit(0);
    else{
        //후위 연산자 변환
        printf("---------------\n");
        printf("postfix\n");
        printf("---------------\n");
        *input_top = convert_postfix(input_top);
        //스택 뒤집기
        *input_top = reserve_stack(input_top);
        stack_print(input_top);
        printf("\n\n\n");
        

        *input_top = calculate(input_top);
        *input_top = clear_null(input_top);
        if(head(input_top) == '$'){
            del_head(input_top);
            push(input_top,'-');
        }
        printf("---------------\n");
        printf("calculate fin!\n");
        printf("---------------\n");
        stack_print(input_top);
    }
    
    del_stack(input_top);
}

int main(){

    run();
    return 0;

}