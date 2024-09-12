#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

typedef struct ListNode {
    void *data;
    struct ListNode *npx;
} ListNode;

typedef struct List {
    ListNode *head;
    size_t len;
} List;

#define LIST_XOR(x, y) ((ListNode *)((uintptr_t)(x) ^ (uintptr_t)(y)))

List *list_init(void *data);
void list_clean(List *ctx);

int list_insert_head(List *ctx, void *data);
int list_insert_tail(List *ctx, void *data);

int list_delete_head(List *ctx);
int list_delete_tail(List *ctx);

void list_print(List *ctx, FILE *stream);

#endif // LIST_H