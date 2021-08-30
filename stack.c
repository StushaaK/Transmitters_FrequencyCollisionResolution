#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stacknode *create_stack_node(int data) {
    stacknode *node = (stacknode *) malloc(sizeof(stacknode));
    node->data = data;
    node->next = NULL;
    return node;
}

int is_empty(stacknode *root) {
    return !root;
}

void push(stacknode** root, int data) {
    stacknode *node = create_stack_node(data);
    node->next = *root;
    *root = node;
}

int pop(stacknode **root) {
    stacknode *temp;
    int popped_data;

    if(is_empty(*root)) return RET_ERR;
    temp = *root;
    *root = (*root)->next;
    popped_data = temp->data;
    free(temp);

    return popped_data;
}

int peek(stacknode *root) {
    if(is_empty(root)) return RET_ERR;
    return root->data;
}

int in_stack(stacknode *root, int value) {
    stacknode *node_pointer;
    if(is_empty(root)) return 0;
    node_pointer=root;
    while(node_pointer) {
        if(value==root->data) return 1;
        node_pointer = node_pointer->next;
    }
    return 0;
}

