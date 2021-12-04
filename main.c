#include "utils.h"
#include <stdio.h>

int main(){

    STACK *input_top = malloc(sizeof(STACK));
    input_top ->next = NULL;

    STACK *test = malloc(sizeof(STACK));
    test -> next = NULL;

    get_input(input_top);
    //공백제거
    *input_top = clear_null(input_top);
    //스택 출력
    stack_print(input_top);
    // 예외처리
    
    //후위 연산자 변환
    *input_top = convert_postfix(input_top);
    //스택 뒤집기
    *input_top = reserve_stack(input_top);
    stack_print(input_top);

    return 0;

}