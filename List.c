//
//  List.c
//  FileEncrypter
//

#include "List.h"

/* Public Functions */

List* list_init() {
    List *list = NULL;
    list = malloc(sizeof(List));
    if(list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void list_Push(List *list, void *data) {
    Node *node = NULL;
    node = malloc(sizeof(Node));
    if(node == NULL) {
        return;
    }
    node->data = data;
    if(list->size < 1) {
        list->head = node;
    }
    else {
        list->tail->next = node;
    }
    node->next = NULL;
    list->tail = node;
    list->size++;
}

void list_Insert(List *list, void *data) {
    Node *node = NULL;
    node = malloc(sizeof(Node));
    if(node == NULL) {
        return;
    }
    node->data = data;
    if(list->size < 1) {
        list->tail = node;
        node->next = NULL;
    }
    else {
        node->next = list->head;
    }
    list->head = node;
    list->size++;
}

Node* list_At(List *list, int index) {
    if(list->size <= index) {
        return NULL;
    }
    if(list->size < 1) {
        return NULL;
    }
    Node *cursor = NULL;
    cursor = list->head;
    for(int i=0; i<=index; i++) {
        if(i == index) {
            return cursor;
        }
        cursor = cursor->next;
    }
    return NULL;
}

void list_Copy(List *dst, List *src) {
    if(src->size < 1) {
        return;
    }
    Node *node = NULL;
    node = src->head;
    do {
        list_Push(dst, node->data);
    } while((node = node->next));
}

void list_destroy(List *list) {
    Node *node = NULL;
    node = list->head;
    while(node) {
        Node *next = NULL;
        next = node->next;
        node->next = NULL;
        free(node);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
    free(list);
}

