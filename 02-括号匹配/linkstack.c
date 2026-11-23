#include <stdlib.h>
#include <stdio.h>
#include "linkstack.h"
//初始化
LinkStack* initLinkStack() {
    LinkStack* stack = (LinkStack*)malloc(sizeof(LinkStack));
    if (stack == NULL) {
        return NULL; // 内存分配失败
    }
    stack->top = NULL;
    return stack;
}
//判断是否为空
int isEmpty(LinkStack* stack) {
    return stack->top == NULL;
}
//入栈
int push(LinkStack* stack, int data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        return -1; // 内存分配失败
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
    return 0; // 入栈成功
}
//出栈
int pop(LinkStack* stack, int* data) {
    if (isEmpty(stack)) {
        return -1; // 栈为空，无法出栈
    }
    StackNode* temp = stack->top;
    *data = temp->data;
    stack->top = temp->next;
    free(temp);
    return 0; // 出栈成功
}
//获取栈顶元素
int peek(LinkStack* stack, int* data) {
    if (isEmpty(stack)) {
        return -1; // 栈为空，无法获取栈顶元素
    }
    *data = stack->top->data;
    return 0; // 获取栈顶元素成功
}