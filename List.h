//
//  List.h
//  FileEncrypter
//

#ifndef List_h
#define List_h

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node_ {
    void            *data;
    struct _Node_   *next;
} Node;

typedef struct _List_ {
    int     size;
    Node    *head;
    Node    *tail;
} List;

/* Public Function Definitions */

List*   list_init(void);
Node*   list_At(List *list, int index);
void    list_Copy(List *dst, List *src);
void    list_Insert(List *list, void *data);
void    list_Push(List *list, void *data);
void    list_destroy(List *list);

#endif /* List_h */

