#include <stdio.h>


#define true 1
#define false 0

typedef struct NODE{
    char* data;
    struct NODE* link;
}node;

typedef struct LIST{
    int count;
    struct NODE* body;
}list;

void LIST_Init(list* head) {
    head->count = 0;
    head->head = NULL;
}

int LIST_Add(list* head, char* data) {
    node* temp = head->body;

    while (1) {
        // 헤더가 비었을 때
        if (temp == NULL) {
            temp = (node*)malloc(sizeof(node));
            temp->data = data;
            temp->link = NULL;
            head->body = temp;
            break;
        }

        // 헤더(현재 노드)가 마지막 일때
        else if (temp->link == NULL) {
            temp->link = (node*)malloc(sizeof(node));
            temp->link->data = data;
            temp->link->link = NULL;
            break;
        }

        // 다음 노드가 존재할 때
        else {
            temp = temp->link;
        }
    }
    head->count++;
    return true;
}

void LIST_Show(list head) {
    node* temp = head.body;
    int i = 0;

    printf("--- total count : %d\n", head.count);
    while (temp!=NULL) {
        printf("%d - %s\n", i,temp->data);
        i++; temp = temp->link;
    }
}

int LIST_Release(list* head) {
    if (head->count == 0 /*head->body ==NULL*/ ) return true;
    node* ptr = head->body;
    node* next = ptr->link;

    while (1) {
        free(ptr);

        if (next == NULL) break;

        ptr = next;
        next = ptr->link;
    }
    head->count = 0;
    head->body = NULL;
    return true;
}

int LIST_Insert(list* head, char* data, int index) {
    
    if (index > head->count) return false;

    node* ptr = head->body;
    node* pre = NULL;
    for (int i = 0; i < index; i++) {
        pre = ptr;
        ptr = ptr->link;
    }

    if (pre == NULL) {
        pre = (node*)malloc(sizeof(node));
        pre->data = data;
        pre->link = ptr;
        head->body = pre;
    }
    else {
        pre->link = (node*)malloc(sizeof(node));
        pre->link->data = data;
        pre->link->link = ptr;
    }

    head->count++;
    return true;
}

int LIST_Delete(list* head, int index) {

    if (index > head->count) return false;

    node* ptr = head->body;
    node* pre = NULL;
    for (int i = 0; i < index; i++) {
        pre = ptr;
        ptr = ptr->link;
    }

    if (pre == NULL) {
        free(ptr);
        head->body = NULL;
    }
    else {
        pre->link = ptr->link;
        free(ptr);
    }

    head->count++;
    return true;
}

void main() {
    list datalist;
    LIST_Init(&datalist);

    LIST_Add(&datalist, "one");
    LIST_Add(&datalist, "two");
    LIST_Add(&datalist, "three");
    LIST_Add(&datalist, "four");
    
    LIST_Insert(&datalist, "six", 4);
    LIST_Delete(&datalist, 1);

    LIST_Show(datalist);

    LIST_Release(&datalist);

}