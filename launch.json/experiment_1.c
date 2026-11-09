#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct{
	int data[MAXSIZE];
	int length;
}SeqList;

void InitList(SeqList*L){
	L->length=0;
} 

void CreateList(SeqList*L){
	int n,i;
	printf("请问要创建几个数字：");
	scanf("%d",&n);
	if(n<0||n>MAXSIZE){
		printf("个数不对\n");
		return;
	}
	for(i=0;i<n;i++){
		printf("输入第%d个元素:",i+1);
		scanf("%d",&L->data[i]);
	}
	L->length=n;
}

int isEmpty(SeqList*L){
	if(L->length==0){
		return 1;
	}
	else{
		return 0;
	}
}

int GetLength(SeqList*L){
	return L->length;
}

int PrintList(SeqList*L){
	int i;
	for(i=0;i<L->length;i++){
		printf("%d ",L->data[i]);
	}
	printf("\n");
	return 1; //补齐return
}

int GetElem(SeqList*L,int position,int*val){
	if(position < 1 || position > L->length) { 
        return 0;
    }
    *val = L->data[position - 1]; 
    return 1;
}

int SeqSearch(SeqList*L,int value){
	int i;
	for(i=0;i<L->length;i++){
		if(L->data[i]==value){
			return i+1; 
		}
	}
	return 0;
}

int BinarySearch(SeqList*L,int value){
	int low=0, high = L->length - 1; 
    while(low <= high) {
        int mid = (low + high) / 2;
        if(L->data[mid] == value) {
            return mid + 1; 
        } else if(L->data[mid] < value) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return 0;
}

int ListInsert(SeqList *L, int position, int x) {
    if(L->length >= MAXSIZE) {
        printf("顺序表已满，无法插入！\n");
        return 0;
    }
    if(position < 1 || position > L->length + 1) {
        printf("插入位置非法！\n");
        return 0;
    }
    for(int i = L->length; i >= position; i--) {
        L->data[i] = L->data[i-1];
    }
    L->data[position - 1] = x;
    L->length++;
    return 1;
}

int ListDeletePos(SeqList *L, int position) {
    if(isEmpty(L)) { 
        printf("顺序表为空！\n");
        return 0;
    }
    if(position < 1 || position > L->length) {
        printf("删除位置非法！\n");
        return 0;
    }
    int idx = position - 1;
    for(int i = idx; i < L->length - 1; i++) {
        L->data[i] = L->data[i+1];
    }
    L->length--;
    return 1;
}

void ListDeleteValue(SeqList *L, int value) {
    int j = 0; 
    for(int i = 0; i < L->length; i++) {
        if(L->data[i] != value) {
            L->data[j++] = L->data[i];
        }
    }
    L->length = j;
}

int main(int argc, char** argv) {
	SeqList L;
    InitList(&L);
    int op,n,pos,x,val,res;
    while(1) {
        printf("\n=====顺序表菜单=====\n");
        printf("1 创建顺序表\n");
        printf("2 判断是否为空\n");
        printf("3 获取长度\n");
        printf("4 输出顺序表\n");
        printf("5 获取指定位置元素\n");
        printf("6 顺序查找\n");
        printf("7 二分查找\n");
        printf("8 在指定位置前插入元素\n");
        printf("9 删除指定位置元素\n");
        printf("10 删除所有值为value的元素\n");
        printf("0 退出\n");
        printf("请输入操作：");
        scanf("%d",&op);
        switch(op) {
            case 1:
                CreateList(&L);
                break;
            case 2:
                if(isEmpty(&L)) printf("顺序表为空\n");
                else printf("顺序表非空\n");
                break;
            case 3:
                printf("顺序表长度=%d\n",GetLength(&L));
                break;
            case 4:
                printf("顺序表内容：");
                PrintList(&L);
                break;
            case 5:
                printf("输入位置position：");
                scanf("%d",&pos);
                if(GetElem(&L,pos,&val)) printf("该位置元素=%d\n",val);
                else printf("位置无效\n");
                break;
            case 6:
                printf("输入要查找的值value：");
                scanf("%d",&val);
                res = SeqSearch(&L,val);
                if(res) printf("顺序查找成功，位置：%d\n",res);
                else printf("未找到\n");
                break;
            case 7:
                printf("输入要二分查找的值value：");
                scanf("%d",&val);
                res = BinarySearch(&L,val);
                if(res) printf("二分查找成功，位置：%d\n",res);
                else printf("未找到（注意二分查找要求表升序）\n");
                break;
            case 8:
                printf("输入插入位置position和元素x：");
                scanf("%d%d",&pos,&x);
                if(ListInsert(&L,pos,x)) printf("插入成功\n");
                break;
            case 9:
                printf("输入要删除的位置position：");
                scanf("%d",&pos);
                if(ListDeletePos(&L,pos)) printf("删除成功\n");
                break;
            case 10:
                printf("输入要删除的值value：");
                scanf("%d",&val);
                ListDeleteValue(&L,val);
                printf("已删除所有值为%d的元素\n",val);
                break;
            case 0:
                printf("程序退出\n");
                exit(0);
            default:
                printf("输入错误，请重新选择！");
        }
    }
	return 0;
}
