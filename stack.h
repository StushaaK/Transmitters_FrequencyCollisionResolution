#ifndef __STACK__
#define __STACK__

#define RET_OK 1
#define RET_ERR -1

typedef struct thestacknode {
    int data;
    struct thestacknode *next;
} stacknode;

stacknode *create_stack_node(int data);
int is_empty(stacknode *root);
void push(stacknode **root, int data);
int pop(stacknode **root);
int peek(stacknode *root);
int in_stack(stacknode *root, int value);

#endif