#include <stdio.h>
#include <stdlib.h>

typedef int Datatype;

typedef struct Node {
    Datatype data;
    struct Node* next;
} Node;

typedef struct LinkQueue {
    Node* front;
    Node* rear;
} LinkQueue;

LinkQueue* initLinkQueue(void)
{
    LinkQueue* queue = (LinkQueue*)malloc(sizeof(LinkQueue));
    if (queue == NULL) {
        return NULL;
    }

    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isEmpty(const LinkQueue* queue)
{
    return queue == NULL || queue->front == NULL;
}

int enqueue(LinkQueue* queue, Datatype value)
{
    if (queue == NULL) {
        return -1;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return -1;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
    } else {
        queue->rear->next = newNode;
    }
    queue->rear = newNode;
    return 0;
}

int dequeue(LinkQueue* queue, Datatype* value)
{
    if (queue == NULL || value == NULL || isEmpty(queue)) {
        return -1;
    }

    Node* node = queue->front;
    *value = node->data;
    queue->front = node->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(node);
    return 0;
}

int getFront(const LinkQueue* queue, Datatype* value)
{
    if (queue == NULL || value == NULL || isEmpty(queue)) {
        return -1;
    }

    *value = queue->front->data;
    return 0;
}

void destroyLinkQueue(LinkQueue* queue)
{
    if (queue == NULL) {
        return;
    }

    Node* node = queue->front;
    while (node != NULL) {
        Node* next = node->next;
        free(node);
        node = next;
    }
    free(queue);
}

int main(void)
{
    LinkQueue* queue = initLinkQueue();
    if (queue == NULL) {
        fprintf(stderr, "队列初始化失败。\n");
        return 1;
    }

    Datatype value;
    printf("队列为空：%s\n", isEmpty(queue) ? "是" : "否");

    if (enqueue(queue, 10) != 0 || enqueue(queue, 20) != 0 ||
        enqueue(queue, 30) != 0) {
        fprintf(stderr, "入队失败。\n");
        destroyLinkQueue(queue);
        return 1;
    }

    if (getFront(queue, &value) == 0) {
        printf("队首元素：%d\n", value);
    }

    while (dequeue(queue, &value) == 0) {
        printf("出队元素：%d\n", value);
    }
    printf("队列为空：%s\n", isEmpty(queue) ? "是" : "否");

    destroyLinkQueue(queue);
    return 0;
}