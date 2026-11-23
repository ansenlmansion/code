#ifndef LINKSTACK_H
#define LINKSTACK_H

#include <stdlib.h>

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} LinkStack;

LinkStack* initLinkStack();
int isEmpty(LinkStack* stack);
int push(LinkStack* stack, int data);
int pop(LinkStack* stack, int* data);
int peek(LinkStack* stack, int* data);

#endif // LINKSTACK_H
