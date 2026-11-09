#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int DataType;
struct Node {
    int top;
    int maxsize;
    DataType* elements;
};
typedef struct Node* Stack;
//初始化一个空的顺序栈
Stack initStack(int maxsize){
    //申请头结点空间
    Stack s = (Stack)malloc(sizeof(struct Node));
    if (s == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    s->top = -1;//栈顶指针初始化为-1，表示栈为空,top指向栈顶元素的下标
    s->maxsize = maxsize;//设置栈的最大容量
    s->elements = (DataType*)malloc(maxsize * sizeof(DataType)); //为栈分配存储空间
    if (s->elements == NULL) { 
        printf("内存分配失败\n");
        exit(1);
    }
    return s;
}
//判断顺序栈是否为空
int isEmpty(Stack s) {
    return s->top == -1; //栈顶指针为-1表示栈为空
}
//判断顺序栈是否已满
int isFull(Stack s){
    return s->top == s->maxsize - 1; //栈顶指针等于最大容量减1表示栈已满
}
//入栈操作
int push(Stack s, DataType value) {
    if (isFull(s)) {
        printf("栈已满，无法入栈。\n");
        return 0;
    }
    s->elements[s->top+1]= value;
    s->top++;
    return 1;
}
//出栈操作
int pop(Stack s, DataType* value) {
    if (isEmpty(s)) {
        printf("栈为空，无法出栈。\n");
        return 0;
    }
    *value = s->elements[s->top];
    s->top--;
    return 1;
}
//获取栈顶元素
int getTop(Stack s, DataType* value){
    if (isEmpty(s)) {
        printf("栈为空，无法获取栈顶元素。\n");
        return 0;
    }
    *value = s->elements[s->top];
    return 1;
}
//进制转化
int ten_base(int number, int base){ 
    
    Stack s = initStack(MAXSIZE); //初始化栈
    while (number > 0) {
        if (isFull(s)) {
            printf("栈已满，无法继续入栈。\n");
            return 0;
        }
        push(s, number % base); //将余数入栈
        number /= base; //更新number为商
    }
    printf("转换后的结果为: ");
    while (!isEmpty(s)) {
        int value;
        pop(s, &value); //从栈中弹出并打印每一位
        printf("%d", value);
    }
    printf("\n");
}

int main() {
    int number, base;
    printf("请输入一个十进制整数: ");
    scanf("%d", &number);
    printf("请输入目标进制(2-9): ");
    scanf("%d", &base);
    
    if (base < 2 || base > 9) {
        printf("无效的进制，请输入2到9之间的整数。\n");
        return 1;
    }
    
    ten_base(number, base);
    
    return 0;
}