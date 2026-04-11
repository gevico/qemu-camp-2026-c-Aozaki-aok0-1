#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    if (n <= 0) {
        return NULL;
    }

    Node* head = (Node*)malloc(sizeof(Node));
    if (!head) {
        return NULL;
    }
    head->id = 1;
    head->next = head;

    Node* tail = head;
    for (int i = 2; i <= n; ++i) {
        Node* p = (Node*)malloc(sizeof(Node));
        if (!p) {
            free_list(head);
            return NULL;
        }
        p->id = i;
        p->next = head;
        tail->next = p;
        tail = p;
    }

    return head;
}

void free_list(Node* head) {
    if (!head) {
        return;
    }

    Node* p = head->next;
    while (p != head) {
        Node* next = p->next;
        free(p);
        p = next;
    }
    free(head);
}
