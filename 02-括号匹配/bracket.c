#include <stdio.h>
#include "linkstack.h"
#include <string.h>
//括号匹配函数
int isMatchingBrackets(const char* expression) {
    LinkStack* stack = initLinkStack();
    if (stack == NULL) {
        return -1; // 内存分配失败
    }

    for (int i = 0; i < strlen(expression); i++) {
        char ch = expression[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            push(stack, ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            int topChar;
            if (pop(stack, &topChar) != 0) {
                free(stack);
                return 0; // 栈为空，括号不匹配
            }
            if ((ch == ')' && topChar != '(') ||
                (ch == '}' && topChar != '{') ||
                (ch == ']' && topChar != '[')) {
                free(stack);
                return 0; // 括号不匹配
            }
        }
    }

    int result = isEmpty(stack);
    free(stack);
    return result; // 如果栈为空，则括号匹配，否则不匹配
}
int main() {
    char expression[100];
    printf("请输入括号表达式：");
    scanf("%s", expression);

    int result = isMatchingBrackets(expression);
    if (result == 1) {
        printf("括号匹配\n");
    } else if (result == 0) {
        printf("括号不匹配\n");
    } else {
        printf("内存分配失败\n");
    }
    system("pause");
    return 0;
}
