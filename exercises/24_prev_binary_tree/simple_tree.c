#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    // TODO: 在这里添加你的代码
    if (q == NULL || tree_node == NULL) {
        return;
    }

    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    if (node == NULL) {
        return;
    }
    node->tree_node = tree_node;
    node->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = node;
        return;
    }

    q->rear->next = node;
    q->rear = node;
}

TreeNode* dequeue(Queue *q) {
    // TODO: 在这里添加你的代码
    if (q == NULL || q->front == NULL) {
        return NULL;
    }

    QueueNode *node = q->front;
    TreeNode *ret = node->tree_node;
    q->front = node->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(node);
    return ret;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    // TODO: 在这里添加你的代码
    if (level_order == NULL || size <= 0 || level_order[0] == INT_MIN) {
        return NULL;
    }

    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    if (root == NULL) {
        return NULL;
    }
    root->val = level_order[0];
    root->left = NULL;
    root->right = NULL;

    Queue *q = create_queue();
    if (q == NULL) {
        free(root);
        return NULL;
    }
    enqueue(q, root);

    int i = 1;
    while (i < size && !is_empty(q)) {
        TreeNode *parent = dequeue(q);
        if (parent == NULL) {
            continue;
        }

        if (i < size && level_order[i] != INT_MIN) {
            TreeNode *left = (TreeNode*)malloc(sizeof(TreeNode));
            if (left == NULL) {
                free_queue(q);
                free_tree(root);
                return NULL;
            }
            left->val = level_order[i];
            left->left = NULL;
            left->right = NULL;
            parent->left = left;
            enqueue(q, left);
        }
        i++;

        if (i < size && level_order[i] != INT_MIN) {
            TreeNode *right = (TreeNode*)malloc(sizeof(TreeNode));
            if (right == NULL) {
                free_queue(q);
                free_tree(root);
                return NULL;
            }
            right->val = level_order[i];
            right->left = NULL;
            right->right = NULL;
            parent->right = right;
            enqueue(q, right);
        }
        i++;
    }

    free_queue(q);
    return root;
}

void preorder_traversal(TreeNode *root) {
    // TODO: 在这里添加你的代码
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void preorder_traversal_iterative(TreeNode *root) {
    // TODO: 在这里添加你的代码
    if (root == NULL) {
        return;
    }

    typedef struct StackNode {
        TreeNode *tree_node;
        struct StackNode *next;
    } StackNode;

    StackNode *stack = NULL;
    StackNode *top = (StackNode*)malloc(sizeof(StackNode));
    if (top == NULL) {
        return;
    }
    top->tree_node = root;
    top->next = NULL;
    stack = top;

    while (stack != NULL) {
        StackNode *cur_top = stack;
        stack = stack->next;

        TreeNode *node = cur_top->tree_node;
        free(cur_top);
        printf("%d ", node->val);

        if (node->right != NULL) {
            StackNode *r = (StackNode*)malloc(sizeof(StackNode));
            if (r == NULL) {
                while (stack != NULL) {
                    StackNode *tmp = stack;
                    stack = stack->next;
                    free(tmp);
                }
                return;
            }
            r->tree_node = node->right;
            r->next = stack;
            stack = r;
        }

        if (node->left != NULL) {
            StackNode *l = (StackNode*)malloc(sizeof(StackNode));
            if (l == NULL) {
                while (stack != NULL) {
                    StackNode *tmp = stack;
                    stack = stack->next;
                    free(tmp);
                }
                return;
            }
            l->tree_node = node->left;
            l->next = stack;
            stack = l;
        }
    }
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
