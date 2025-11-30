//
// Created by Lenovo on 26.11.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DLLIST{
    int key;
    float value;
    struct DLLIST *next;
    struct DLLIST *prev;
}DLLIST;

typedef struct {
    DLLIST *front;
    DLLIST *rear;

}QUEUE;

QUEUE* CreateQueue(void) {
    QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));
    q -> front = q -> rear = NULL;
    return q;
}

DLLIST* CreateElement(int key, float value) {
    DLLIST* n = (DLLIST*)malloc(sizeof(DLLIST));
    n -> key = key;
    n -> value = value;
    n -> next = n -> prev = NULL;
    return n;

}

bool IsEmptyQueue(QUEUE* q) {
    return (q -> front == NULL);
}


void InsFront(QUEUE* q, int key, float value) {
    DLLIST* n = CreateElement(key, value);
    n -> next = q -> front;
    if (!IsEmptyQueue(q))
        q -> front -> prev = n;
    q -> front = n;
    if (q -> rear == NULL)
        q -> rear = n;
}

void InsRear(QUEUE* q, int key, float value) {
    DLLIST* n = CreateElement(key, value);
    n -> prev = q -> rear;
    if (!IsEmptyQueue(q))
        q -> rear -> next = n;
    q -> rear = n;
    if (IsEmptyQueue(q))
        q -> front = n;
}


void DelFront(QUEUE* q) {
    if (IsEmptyQueue(q))
        return;
    DLLIST* del = q -> front;
    q -> front = q -> front -> next;
    if (!IsEmptyQueue(q))
        q -> front -> prev = NULL;
    else
        q -> rear = NULL;
    free(del);
}

void DelRear(QUEUE* q) {
    if (IsEmptyQueue(q))
        return;
    DLLIST* del = q -> rear;
    q -> rear = q -> rear -> prev;
    if (q -> rear != NULL)
        q -> rear -> next = NULL;
    else
        q -> front = NULL;
    free(del);
}

void DelByKey(QUEUE* q, int key, int dir) { //dir: 0 - front, 1 - rear)
    if (IsEmptyQueue(q))
        return;
    DLLIST* cur;

    if (dir == 0)
        cur = q -> front;
    else
        cur = q -> rear;

    while (cur) {
        if (cur -> key == key) {

            if (cur == q -> front)
                q -> front = cur -> next;

            if (cur == q -> rear)
                q -> rear = cur -> prev;

            if (cur -> prev)
                cur -> prev -> next = cur -> next;

            if (cur -> next)
                cur -> next -> prev = cur -> prev;
            free(cur);
            return;
        }
        if (dir == 0)
            cur = cur -> next;
        else
            cur = cur -> prev;
    }
}

void DelByPointer(QUEUE* q, DLLIST* ptr) {
    if (ptr && !IsEmptyQueue(q)) {
        if (ptr == q -> front)
            q -> front = ptr -> next;

        if (ptr == q -> rear)
            q -> rear = ptr -> prev;

        if (ptr -> prev)
            ptr -> prev -> next = ptr -> next;

        if (ptr -> next)
            ptr -> next -> prev = ptr -> prev;
        free(ptr);
    }
}

void MakeNull(QUEUE* q) {
    while(!IsEmptyQueue(q))
            DelFront(q);
    }

void Print(QUEUE* q) {
    if (IsEmptyQueue(q))
        return;
    DLLIST* cur = q -> front;
    while (cur) {
        printf("%d %f", cur -> key, cur -> value);
        puts("");
        cur = cur -> next;
    }
}

/* Двусвязные списки
 * 1) создать пустую очередь  create queue
 * 2) создать функцию с проверкой очереди на пустоту
 * 3) ins_front
 *    ins_rear
 *    del_front
 *    del_rear
 * 4) удаление по ключу с указанием направления
 * 5) удаление элемента по ссылке
 * 6) make_null сделать очередь пустой
 */

int main(void) {
    QUEUE* q = CreateQueue();

    InsRear(q,0,5);
    InsRear(q,1,5);
    InsRear(q,2,5);
    InsRear(q,3,5);
    InsRear(q,4,5);
    Print(q);
    puts("");

    DelByKey(q,3, 1);
    Print(q);
    puts("");

    DelByPointer(q,q -> rear  );
    Print(q);
    free(q);
}
