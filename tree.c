#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

typedef struct ListNode {
    Node *data;
    struct ListNode *next;
} ListNode;

int GreaterThan(int alpha, int beta) {
    return alpha > beta;
}

int GreaterThanEqual(int alpha, int beta) {
    return alpha >= beta;
}

ListNode *AddNode(ListNode *head, ListNode *element, int (*comp)(int, int)) {
    ListNode *temp1, *temp2 = NULL;

    if (!head) {
        return element;
    }
    else if (comp(head->data->count, element->data->count)) {
        element->next = head;
        return element;
    }
    else {
        temp1 = head;
        while (temp1 && !comp(temp1->data->count, element->data->count)) {
            temp2 = temp1;
            temp1 = temp1->next;
        }
        element->next = temp1;
        temp2->next = element;
        return head;
    }
}

ListNode *InitNode(int data, int isLeaf, int count, Node *left, Node *right) {
    ListNode *ret;

    ret = malloc(sizeof(ListNode));
    ret->data = malloc(sizeof(Node));
    ret->data->data = data;
    ret->data->isLeaf = isLeaf;;
    ret->data->count = count;
    ret->data->left = left;
    ret->data->right = right;
    ret->next = NULL;

    return ret;
}

ListNode *FreeHead(ListNode *head) {
    ListNode *ret;

    ret = head->next;
    free(head);

    return ret;
}

Node *CreateTree(int *counts) {
    int idx;
    ListNode *head, *temp;
    Node *ret;

    head = NULL;
    for (idx = 0; idx <= CHAR_MAX; idx++) {
        if (counts[idx]) {
            temp = InitNode(idx, 1, counts[idx], NULL, NULL);
            head = AddNode(head, temp, GreaterThan);
        }
    }

    while(head && head->next) {
        temp = InitNode(0, 0, head->data->count + head->next->data->count,
         head->data, head->next->data);
        head = FreeHead(FreeHead(head));
        head = AddNode(head, temp, GreaterThanEqual);
    }

    ret = head->data;
    head = FreeHead(head);
    
    return ret;
}

void FreeTree(Node *root) {
    if (root->left) {
        FreeTree(root->left);
    }
    if (root->right) {
        FreeTree(root->right);
    }
    free(root);
}