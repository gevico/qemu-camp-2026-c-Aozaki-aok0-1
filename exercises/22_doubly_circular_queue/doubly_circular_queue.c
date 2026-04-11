#include "doubly_circular_queue.h"

#include <stdlib.h>

// 头尾哨兵
static struct node tailsentinel;
static struct node headsentinel = {0, NULL, &tailsentinel};
static struct node tailsentinel = {0, &headsentinel, NULL};

static link head = &headsentinel;
static link tail = &tailsentinel;

link make_node(int data) {
    // TODO: 在这里添加你的代码
    link p = (link)malloc(sizeof(struct node));
    if (p == NULL) {
        return NULL;
    }
    p->data = data;
    p->prev = NULL;
    p->next = NULL;
    return p;
}

void free_node(link p) {
    // TODO: 在这里添加你的代码
    free(p);
}

link search(int key) {
    // TODO: 在这里添加你的代码
    for (link p = head->next; p != tail; p = p->next) {
        if (p->data == key) {
            return p;
        }
    }
    return NULL;
}

void insert(link p) {
    // TODO: 在这里添加你的代码
    if (p == NULL) {
        return;
    }
    p->next = head->next;
    p->prev = head;
    head->next->prev = p;
    head->next = p;
}

void delete(link p) {
    // TODO: 在这里添加你的代码
    if (p == NULL || p == head || p == tail) {
        return;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    p->prev = NULL;
    p->next = NULL;
}

void traverse(void (*visit)(link)) {
    // TODO: 在这里添加你的代码
    if (visit == NULL) {
        return;
    }
    for (link p = head->next; p != tail; p = p->next) {
        visit(p);
    }
}

void destroy(void) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    while (p != tail) {
        link next = p->next;
        free_node(p);
        p = next;
    }
    head->next = tail;
    tail->prev = head;
}
