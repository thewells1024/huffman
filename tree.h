#pragma once
#define CHAR_MAX    255

typedef struct Node {
    unsigned char data;
    int isLeaf;
    int count;
    struct Node *right, *left;
} Node;

Node *CreateTree(int *);
void FreeTree(Node *);