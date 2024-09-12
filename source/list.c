#include <stdlib.h>
#include <stdio.h>

#include "list.h"

static ListNode *list_create_node(void *data) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->npx = NULL;
    return node;
}

List *list_init(void *data) {
    List *ctx = (List *)malloc(sizeof(List));
    if (ctx == NULL) {
        return NULL;
    }
    ctx->head = list_create_node(data);
    ctx->head->npx = LIST_XOR(NULL, NULL);
    ctx->len = 1;
    return ctx;
}

void list_clean(List *ctx) {
    if (ctx == NULL) {
        return;
    }

    ListNode *cur = ctx->head;
    ListNode *next = NULL;
    ListNode *prev = NULL;
    uintptr_t tmp;

    while (cur != NULL) {
        next = LIST_XOR(prev, cur->npx);
        tmp = (uintptr_t)cur;
        free(cur);
        prev = (ListNode *)tmp;
        cur = next;
    }
    free(ctx);

    return;
}

int list_insert_head(List *ctx, void *data) {
    ListNode *node = list_create_node(data);
    if (node == NULL) {
        return -1;
    }

    if (ctx->head != NULL) {
        node->npx = LIST_XOR(NULL, ctx->head);
        ctx->head->npx = LIST_XOR(node, LIST_XOR(ctx->head->npx, NULL));
    }
    else {
        node->npx = LIST_XOR(NULL, NULL);
    }
    ctx->head = node;
    ctx->len++;

    return 0;
}

int list_insert_tail(List *ctx, void *data) {
    ListNode *node = list_create_node(data);
    if (node == NULL) {
        return -1;
    }

    if (ctx->head == NULL) {
        ctx->head = node;
        node->npx = LIST_XOR(NULL, NULL);
        ctx->len++;
        return 0;
    }

    ListNode *cur = ctx->head;
    ListNode *next = NULL;
    ListNode *prev = NULL;

    
    while (cur != NULL) {
        next = LIST_XOR(prev, cur->npx);
        if (next == NULL) {
            break;
        }
        prev = cur;
        cur = next;
    }
     
    node->npx = LIST_XOR(NULL, cur);
    cur->npx = LIST_XOR(LIST_XOR(cur->npx, NULL), node);

    ctx->len++;

    return 0;
}

int list_delete_head(List *ctx) {
    if (ctx == NULL || ctx->head == NULL) {
        return -1;
    }

    ListNode *node = ctx->head;
    ListNode *next = LIST_XOR(node->npx, NULL);

    if (next != NULL) {
        next->npx = LIST_XOR(LIST_XOR(next->npx, node), NULL);
        ctx->head = next;
    }
    else {
        ctx->head = NULL;
    }
    free(node);
    ctx->len--; 

    return 0;
}

int list_delete_tail(List *ctx) {
    if (ctx == NULL || ctx->head == NULL) {
        return -1;
    }

    ListNode *cur = ctx->head;
    ListNode *next = NULL;
    ListNode *prev = NULL;

    while (cur != NULL) {
        next = LIST_XOR(prev, cur->npx);
        if (next == NULL) {
            break;
        }
        prev = cur;
        cur = next;
    }

    if (cur == ctx->head) {
        ctx->head = NULL;
    }
    else {
        if (prev != NULL) {
            prev->npx = LIST_XOR(LIST_XOR(prev->npx, cur), NULL);
        }
    }

    free(cur);
    ctx->len--;

    return 0;
}

void list_print(List *ctx, FILE *stream) {
    if (ctx == NULL || ctx->head == NULL) {
        return;
    }

    ListNode *cur = ctx->head;
    ListNode *next = NULL;
    ListNode *prev = NULL;

    while (cur != NULL) {
        fprintf(stream, "%p - ", cur->data);
        next = LIST_XOR(prev, cur->npx);
        prev = cur;
        cur = next;
    }
    fprintf(stream, "\nSize: %zu\n", ctx->len);

    return;
}