//
// Created by Lenovo on 15.11.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list {
    int key;
    float value;
    struct list* next;
}LIST;

LIST* CreateList() {
    LIST* cur;
    cur = (LIST*)malloc(sizeof(LIST));
    cur->key = 0;
    cur->value = 0;
    cur->next = NULL;
    return cur;
}


bool IsEmpty(LIST* list) {
    return !list->next;
}

void Push(LIST* list, int key, float value) {
    LIST* cur;
    cur = (LIST*)malloc(sizeof(LIST));
    cur->key = key;
    cur->value = value;
    cur->next = list->next;
    list->next = cur;
}


void PrintList(LIST* list) {
    LIST* cur = list->next;
    while (cur) {
        printf("key: %d   value: %f\n", cur->key, cur->value);
        cur = cur->next;
    }
    puts("");

}

void Pop(LIST* list) {
    if (!IsEmpty(list)) {
        LIST* del = list->next;
        list->next = list->next->next;
        free(del);
    }
}

void DelitingListElements(LIST* list) {
    while (!IsEmpty(list)) {
        Pop(list);
    }
}

int LengthList(LIST* list) {
    int count = 0;
    LIST* ptr = list->next;
    while (ptr) {
        ptr = ptr->next;
        count++;
    }
    return count;

}
LIST* LastElement(LIST* list) {
    LIST* ptr = list;
    while (ptr->next)
        ptr = ptr->next;

    return ptr;

}

void PopByKey(LIST* list, int key) {
    LIST* ptr = list;

    while (ptr->next) {
        if (ptr->next->key == key){
            LIST* del;
            del= ptr->next;
            ptr->next = del->next;
            free(del);
            return;

        }
        ptr = ptr->next;
    }
}

int IssueValueByKey(LIST* list, int key, float* value) {
    LIST* ptr = list->next;
    while (ptr) {
        if (ptr->key == key) {
            *value = ptr->value;
            return 1;
        }
        ptr = ptr->next;
    }
    return 0;
}
void Append(LIST* list, int key, float value) {
    LIST* cur;
    cur = (LIST*)malloc(sizeof(LIST));
    cur->key = key;
    cur->value = value;
    cur->next = NULL;
    LIST* last= LastElement(list);
    last->next = cur;

}

int main(void){
    LIST* list = CreateList();

    Push(list, 0,24);
    Push(list, 1, 13);
    Push(list, 2, 7);
    Push(list, 3, 99);

    printf("lenght = %d\n", LengthList(list));
    PrintList(list);


    Pop(list);

    printf("lenght = %d\n", LengthList(list));
    PrintList(list);


    Push(list,4,88);

    printf("lenght = %d\n", LengthList(list));
    PrintList(list);


    Append(list,5,70);
    Append(list,6,100);

    printf("lenght = %d\n", LengthList(list));
    PrintList(list);

    PopByKey(list,1);

    printf("lenght = %d\n", LengthList(list));
    PrintList(list);


    float valueElement;

    if (IssueValueByKey(list, 6, &valueElement) == 1)
        printf("%f\n",valueElement);
    else
        puts("There is no element with this key");


    DelitingListElements(list);
    printf("lenght = %d\n", LengthList(list));
    PrintList(list);








    free(list);
    return 0;
}

