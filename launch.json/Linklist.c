#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType;
struct Node{          //链表结构体定义
    DataType data;    //数据域
    struct Node* next;  //指针域
};

/*函数功能:初始化一个带头节点的单链表
  函数形参:无
  返回值:返回单链表的头指针，Node*类型
*/
struct Node* InitList(){
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));//申请空间的大小为Node结构体的大小
    // Node*head = new Node;
    if(head){                      //判断是否申请成功
        head->next = NULL;   
        return head;     //将头节点的指针域置为空
    }
    return NULL;  //申请失败返回空指针
}

/*函数功能:采用头插法创建一个带头节点的单链表
  函数形参:一个单链表的头指针，Node*类型
  返回值:插入成功返回1/true，插入失败返回0/false，int/bool类型
*/
bool CreateList_head(struct Node* head){
    // 头插法创建链表的实现
    int data;
    // 输入数据
    struct Node*p= (struct Node*)malloc(sizeof(struct Node)); // 创建新节点
    if(p){//申请成功
        p->data = data; // 将数据存入新节点
        p->next = head->next; // 新节点的指针域指向原来的第一个节点
        head->next = p; // 头节点的指针域指向新节点
        return true; // 插入成功
    }else{
        return false; // 插入失败
    }
}

/*函数功能：打印单链表节点的数据
函数形参：一个单链表的头指针Node*head
函数返回值：无，void类型
*/
void PrintList(struct Node* head){
    struct Node* p = head->next; // 定义一个指针p指向头节点的下一个节点
    int count = 0;
    while(p){ 
        count++;// 当p不为空时，循环打印节点数据
        printf("%d ", p->data); // 打印当前节点的数据
        p = p->next; // 指针p指向下一个节点
    }
    //printf("共打印输出%d个节点的数据", count); // 打印输出节点总数
    printf("\n共打印输出%d个节点的数据\n", count); // 打印换行符
}

/*函数功能:采用尾插法创建一个带头节点的单链表
  函数形参:一个单链表的头指针，Node*类型
  返回值:插入成功返回1/true，插入失败返回0/false，int/bool类型
*/
bool CreateList_tail(struct Node* head){
    // 尾插法创建链表的实现
    int data;
    scanf("%d", &data); // 输入数据
    struct Node*p= (struct Node*)malloc(sizeof(struct Node)); // 创建新节点
    if(p){//申请成功
        p->data = data; // 将数据存入新节点
        p->next = NULL; // 新节点的指针域置为空
        struct Node* q = head; // 定义一个指针q指向头节点
        while(q->next){ // 找到链表的最后一个节点
            q = q->next;
        }
        q->next = p; // 最后一个节点的指针域指向新节点
        return true; // 插入成功
    }else{
        return false; // 插入失败
    }
}

/*函数功能:判断单链表是否为空
  函数形参:一个单链表的头指针，Node*类型
  返回值:链表为空返回1/true，否则返回0/false，int/bool类型
*/
bool IsEmpty(struct Node* head){
    return head->next == NULL;
}

/*函数功能:计算链表的长度
  函数形参:一个单链表的头指针，Node*类型
  返回值:返回链表的长度，int类型
*/
int GetLength(struct Node* head){
    int length = 0;
    struct Node* p = head->next;
    while(p){
        length++;
        p = p->next;
    }
    return length;
}

/*函数功能:输出链表的所有元素
  函数形参:无
  返回值:0
*/
int main(){
    struct Node* head = InitList();//调用初始化函数，返回头指针
    int num;
    while(1){
        scanf("%d", &num);
        if(num == -1) break;
        CreateList_head(head, num);
    }   
    PrintList(head);//调用打印链表函数

    while(1){
        scanf("%d", &num);
        if(num == -1) break;
        CreateList_tail(head, num);
    }//调用尾插法创建链表函数
    PrintList(head);//调用打印链表函数  

    printf("链表长度为: %d\n", GetLength(head));
    if(IsEmpty(head)){
        printf("链表为空\n");
    }else{
        printf("链表非空\n");
    }
    return 0;
}