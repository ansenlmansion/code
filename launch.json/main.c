//项目名称：简单的通讯录管理程序
//项目功能：实现对通讯录的增删改查功能，包括添加联系人、删除联系人、修改联系人信息和查询联系人信息。
//项目作者：王雨萱
//项目日期：2026年10月26日

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// 定义联系人结构体
typedef struct {
    char name[50]; // 姓名
    char phone[12]; // 电话号码
    struct Birthday {
        int year;
        int month;
        int day;
    } birthday;
    int age; // 年龄
} Contact; 

/*函数功能：计算联系人年龄
  输入参数：const Contact* contact（联系人信息指针）、int* age（年龄指针）
  返回值：成功返回true，失败返回false,bool类型
*/
static bool calculateAge(const Contact* contact, int* age) {
    time_t now = time(NULL);
    struct tm* currentDate = localtime(&now);
    if (currentDate == NULL) {
        fprintf(stderr, "无法获取当前日期\n");
        return false;
    }

    *age = currentDate->tm_year + 1900 - contact->birthday.year;
    if (currentDate->tm_mon + 1 < contact->birthday.month ||
        (currentDate->tm_mon + 1 == contact->birthday.month &&
         currentDate->tm_mday < contact->birthday.day)) {
        --*age;
    }
    return true;
}

//定义通讯录节点结构体
typedef struct Node {
    Contact data;
    struct Node* next;
} Node;

/*函数功能：初始化一个空的通讯录链表
  输入参数：无
  返回值：Node*类型，指向空链表头节点的指针
*/
Node* initContactList() {
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) 
        fprintf(stderr, "内存分配失败\n");
    else
        head->next = NULL;
    return head;
}
//13
/*函数功能：查找指定联系人的前驱节点
  输入参数：Node* head（通讯录链表头节点指针）、char* name（指定联系人姓名）
  返回值：成功返回前驱节点指针，失败返回空指针
*/
Node* findPredecessor(Node* head, const char* name) {
    if (head == NULL || name == NULL) {
        return NULL;
    }
    Node* current = head;
    while (current->next != NULL) {
        if (strcmp(current->next->data.name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; // 未找到指定联系人
}
//1
/*函数功能：采用头插法向通讯录链表中添加联系人信息
  输入参数：Node* head（通讯录链表头节点指针）、Contact data（要添加的联系人信息）
  返回值：成功返回true，失败返回false,bool类型
*/
bool addContact(Node* head, Contact data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "内存分配失败\n");
        return false;
    }
    node->data = data;
    node->next = head->next;
    head->next = node;
    return true;
}
//2
/*函数功能：采用尾插法向通讯录链表中添加联系人信息
  输入参数：Node* head（通讯录链表头节点指针）、Contact data（要添加的联系人信息）
  返回值：成功返回true，失败返回false,bool类型
*/
bool addContactAtTail(Node* head, Contact data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "内存分配失败\n");
        return false;
    }
    node->data = data;
    node->next = NULL;
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return true;
}
//3
/*函数功能：删除通讯录链表中的指定联系人信息
  输入参数：Node* head（通讯录链表头节点指针）、char* name（要删除的联系人姓名）
  返回值：成功返回true，失败返回false,bool类型
*/
bool deleteContact(Node* head, const char* name) {
    if (head == NULL || name == NULL) {
        return false;
    }
    Node* current = head;
    while (current->next != NULL) {
        if (strcmp(current->next->data.name, name) == 0) {
            Node* temp = current->next;
            current->next = temp->next;
            free(temp);
            return true;
        }
        current = current->next;
    }
    return false; // 未找到联系人
}
//4
/*函数功能：删除通讯录链表中的指定联系人后面联系人的信息
  输入参数：Node* head（通讯录链表头节点指针）、char* name（要删除的联系人姓名）
  返回值：成功返回true，失败返回false,bool类型
*/
bool deleteContactAfter(Node* head, const char* name) {
    Node* predecessor = findPredecessor(head, name);
    if (predecessor == NULL || predecessor->next == NULL ||
        predecessor->next->next == NULL) {
        return false; // 未找到指定联系人或其后无节点
    }
    Node* target = predecessor->next->next;
    predecessor->next->next = target->next;
    free(target);
    return true;
}

// 删除指定联系人前面的联系人
bool deleteContactBefore(Node* head, const char* name) {
    Node* predecessor = findPredecessor(head, name);
    if (predecessor == NULL || predecessor == head) {
        return false; // 未找到指定联系人或其前无联系人
    }

    Node* beforePredecessor = head;
    while (beforePredecessor->next != NULL &&
           beforePredecessor->next != predecessor) {
        beforePredecessor = beforePredecessor->next;
    }
    if (beforePredecessor->next != predecessor) {
        return false;
    }

    beforePredecessor->next = predecessor->next;
    Node* temp = predecessor;
    free(temp);
    return true;
}
//6
/*函数功能：修改通讯录链表中的联系人信息
  输入参数：Node* head（通讯录链表头节点指针）、char*   name（要修改的联系人姓名）、Contact newData（新的联系人信息）
  返回值：成功返回true，失败返回false,bool类型
*/
bool modifyContact(Node* head, char* name, Contact newData) {
    Node* current = head->next;
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            current->data = newData;
            return true;
        }
        current = current->next;
    }
    return false; // 未找到联系人
}
//7
/*函数功能：查询通讯录链表中的联系人信息（姓名）
  输入参数：Node* head（通讯录链表头节点指针）、char name[]（要查询的联系人姓名）          
  返回值：成功返回地址，失败返回空指针,void*类型
*/
Contact* searchContact(Node* head, const char* name) {
    Node* current = head->next;
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            return &current->data;
        }
        current = current->next;
    }
    return NULL; // 未找到联系人
}
//8
/*函数功能：查询通讯录链表中的联系人信息（电话号码）
  输入参数：Node* head（通讯录链表头节点指针）、char phone[]（要查询的联系人电话号码）          
  返回值：成功返回地址，失败返回空指针,void*类型
*/
Contact* searchContactByPhone(Node* head, const char* phone) {
    Node* current = head->next;
    while (current != NULL) {
        if (strcmp(current->data.phone, phone) == 0) {
            return &current->data;
        }
        current = current->next;
    }
    return NULL; // 未找到联系人
}
//9
/*函数功能：输出单个人的联系人信息 
  输入参数：Contact contact（联系人信息）
  返回值：成功返回true，失败返回false,bool类型
*/
bool printContact(Contact contact) {
    printf("姓名: %s\n", contact.name);
    printf("电话号码: %s\n", contact.phone);
    printf("出生日期: %d-%d-%d\n", contact.birthday.year, contact.birthday.month, contact.birthday.day);
    printf("年龄: %d\n", contact.age);
    return true;
}
//10
/*函数功能：输出所有人的联系人信息
  输入参数：Node* head（通讯录链表头节点指针）
  返回值：成功返回true，失败返回false,bool类型
*/
bool printAllContacts(Node* head) {
    Node* current = head->next;
    while (current != NULL) {
        printContact(current->data);
        current = current->next;
    }
    return true;
}
//11
/*函数功能：在指定联系人后面插入新的联系人信息
  输入参数：Node* head（通讯录链表头节点指针）、char* name（指定联系人姓名）、Contact newData（新的联系人信息）
  返回值：成功返回true，失败返回false,bool类型
*/
bool insertContactAfter(Node* head, char* name, Contact newData) {
    Node* current = head->next;// 从第一个节点开始查找指定联系人
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            Node* node = (Node*)malloc(sizeof(Node));// 创建新的联系人节点
            if (node == NULL) {
                fprintf(stderr, "内存分配失败\n");
                return false;
            }
            node->data = newData;// 将新的联系人信息赋值给新节点
            node->next = current->next;// 将新节点的next指针指向当前节点的下一个节点
            current->next = node;// 将当前节点的next指针指向新节点，实现插入操作
            return true;
        }
        current = current->next;// 继续查找下一个节点
    }
    return false; // 未找到指定联系人
}
//12
/*函数功能：在指定联系人前面插入新的联系人信息
  输入参数：Node* head（通讯录链表头节点指针）、char* name（指定联系人姓名）
  返回值：成功返回前驱节点指针，失败返回空指针
*/
Node* insertContactBefore(Node* head, char* name, Contact newData) {
    Node* pred = findPredecessor(head, name);
    if (pred == NULL) {
        return NULL; // 未找到指定联系人
    }
    Node* node = (Node*)malloc(sizeof(Node));// 创建新的联系人节点
    if (node == NULL) {
        fprintf(stderr, "内存分配失败\n");
        return NULL;
    }
    node->data = newData;// 将新的联系人信息赋值给新节点
    node->next = pred->next;// 将新节点的next指针指向前驱节点的下一个节点
    pred->next = node;// 将前驱节点的next指针指向新节点，实现插入操作
    return pred;
}
void manageContacts(Node* head) {
    int choice;
    Contact contact;
    Contact* found;
    while (1) {
        printf("\n请选择操作:\n");
        printf("1. 添加联系人\n");
        printf("2. 删除联系人\n");
        printf("3. 修改联系人信息\n");
        printf("4. 查询联系人信息（姓名）\n");
        printf("5. 查询联系人信息（电话号码）\n");
        printf("6. 输出单人联系人的信息\n");
        printf("7. 输出所有联系人的信息\n");
        printf("8. 在指定联系人后面插入新的联系人信息\n");
        printf("9. 在指定联系人前面插入新的联系人信息\n");
        printf("10. 删除指定联系人后面联系人的信息\n");
        printf("11. 删除指定联系人前面联系人的信息\n");
        printf("12. 查找指定联系人的前驱节点\n");
        printf("13. 退出\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                // 添加联系人
                printf("请输入联系人姓名: ");
                scanf("%49s", contact.name);
                printf("请输入联系人电话号码: ");
                scanf("%11s", contact.phone);
                printf("请输入联系人出生年份: ");
                scanf("%d", &contact.birthday.year);
                printf("请输入联系人出生月份: ");
                scanf("%d", &contact.birthday.month);
                printf("请输入联系人出生日期: ");
                scanf("%d", &contact.birthday.day);
                if (!calculateAge(&contact, &contact.age)) {
                    break;
                }
                addContact(head, contact);
                break;
            case 2:
                // 删除联系人
                printf("请输入要删除的联系人姓名: ");
                scanf("%49s", contact.name);
                deleteContact(head, contact.name);
                break;
            case 3:
                // 修改联系人信息
                printf("请输入要修改的联系人姓名: ");
                scanf("%49s", contact.name);
                printf("请输入新的联系人电话号码: ");
                scanf("%11s", contact.phone);
                printf("请输入新的联系人出生年份: ");
                scanf("%d", &contact.birthday.year);
                printf("请输入新的联系人出生月份: ");
                scanf("%d", &contact.birthday.month);
                printf("请输入新的联系人出生日期: ");
                scanf("%d", &contact.birthday.day);
                if (!calculateAge(&contact, &contact.age)) {
                    break;
                }
                modifyContact(head, contact.name, contact);
                break;
            case 4:
                // 查询联系人信息（姓名）
                printf("请输入要查询的联系人姓名: ");
                scanf("%49s", contact.name);
                found = searchContact(head, contact.name);
                if (found != NULL) {
                    contact = *found;
                    printf("找到联系人信息:\n");
                    printf("姓名: %s\n", contact.name);
                    printf("电话号码: %s\n", contact.phone);
                    printf("出生日期: %d-%d-%d\n", contact.birthday.year, contact.birthday.month, contact.birthday.day);
                    printf("年龄: %d\n", contact.age);
                } else {
                    printf("未找到该联系人。\n");
                }
                break;
            case 5:
                //查询联系人信息（电话号码）
                printf("请输入要查询的联系人电话号码: ");
                scanf("%11s", contact.phone);
                found = searchContactByPhone(head, contact.phone);
                if (found != NULL) {
                    contact = *found;
                    printf("找到联系人信息:\n");
                    printf("姓名: %s\n", contact.name);
                    printf("电话号码: %s\n", contact.phone);
                    printf("出生日期: %d-%d-%d\n", contact.birthday.year, contact.birthday.month, contact.birthday.day);
                    printf("年龄: %d\n", contact.age);
                } else {
                    printf("未找到该联系人。\n");
                }
                break;
            case 6:
                //输出单人联系人的信息
                printf("请输入要输出的联系人姓名: ");
                scanf("%49s", contact.name);
                found = searchContact(head, contact.name);
                if (found != NULL) {
                    contact = *found;
                    printf("联系人信息:\n");
                    printf("姓名: %s\n", contact.name);
                    printf("电话号码: %s\n", contact.phone);
                    printf("出生日期: %d-%d-%d\n", contact.birthday.year, contact.birthday.month, contact.birthday.day);
                    printf("年龄: %d\n", contact.age);
                } else {
                    printf("未找到该联系人。\n");
                }
                break;
            case 7:
                //输出所有联系人的信息
                printf("所有联系人信息:\n");
                printAllContacts(head);
                break;
            case 8:
                //在指定联系人后面插入新的联系人信息
                {
                char targetName[sizeof(contact.name)];
                printf("请输入要插入到其后的联系人姓名: ");
                scanf("%49s", targetName);
                printf("请输入新的联系人姓名: ");
                scanf("%49s", contact.name);
                printf("请输入新的联系人电话号码: ");
                scanf("%11s", contact.phone);
                printf("请输入新的联系人出生年份: ");
                scanf("%d", &contact.birthday.year);
                printf("请输入新的联系人出生月份: ");
                scanf("%d", &contact.birthday.month);
                printf("请输入新的联系人出生日期: ");
                scanf("%d", &contact.birthday.day);
                if (!calculateAge(&contact, &contact.age)) {
                    break;
                }
                if (!insertContactAfter(head, targetName, contact)) {
                    printf("未找到指定联系人，插入失败。\n");
                }
                break;
                }
            case 9:
                // 在指定联系人前面插入新的联系人信息
                {
                char targetName[sizeof(contact.name)];
                printf("请输入要插入到其前的联系人姓名: ");
                scanf("%49s", targetName);
                printf("请输入新的联系人姓名: ");
                scanf("%49s", contact.name);
                printf("请输入新的联系人电话号码: ");
                scanf("%11s", contact.phone);
                printf("请输入新的联系人出生年份: ");
                scanf("%d", &contact.birthday.year);
                printf("请输入新的联系人出生月份: ");
                scanf("%d", &contact.birthday.month);
                printf("请输入新的联系人出生日期: ");
                scanf("%d", &contact.birthday.day);
                if (!calculateAge(&contact, &contact.age)) {
                    break;
                }
                if (insertContactBefore(head, targetName, contact) == NULL) {
                    printf("未找到指定联系人或内存分配失败，插入失败。\n");
                }
                break;
                }
            case 10:
                // 删除指定联系人后面联系人的信息
                printf("请输入要删除的联系人姓名: ");
                scanf("%49s", contact.name);
                if (!deleteContactAfter(head, contact.name)) {
                    printf("删除失败或未找到指定联系人。\n");
                }
                break;
            case 11:
                // 删除指定联系人前面联系人的信息
                printf("请输入要删除的联系人姓名: ");
                scanf("%49s", contact.name);
                if (!deleteContactBefore(head, contact.name)) {
                    printf("删除失败或未找到指定联系人。\n");
                }
                break;
            case 12:
                // 查找指定联系人的前驱节点
                printf("请输入要查找的联系人姓名: ");
                scanf("%49s", contact.name);
                Node* pred = findPredecessor(head, contact.name);
                if (pred != NULL) {
                    if (pred == head) {
                        printf("该联系人是第一个联系人，没有前驱联系人。\n");
                    } else {
                        printf("前驱联系人姓名: %s\n", pred->data.name);
                    }
                } else {
                    printf("未找到指定联系人。\n");
                }
                break;
            case 13:
                // 退出
                return;
            default:
                printf("无效的选择，请重新输入。\n");
                break;
        }
    }
}


int main() {
    Node* contactList = initContactList();
    if (contactList == NULL) {
        return EXIT_FAILURE;
    }
    manageContacts(contactList);
    while (contactList->next != NULL) {
        Node* temp = contactList->next;
        contactList->next = temp->next;
        free(temp);
    }
    free(contactList);
    return 0;
}