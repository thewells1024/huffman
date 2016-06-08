#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CodeTable.h"

void getPaths(Node *root, char *path, int length, TableEntry *table) {
    char *lTemp, *rTemp;
    TableEntry *temp;

    if (root->isLeaf) {
        temp = table + (unsigned int)root->data;
        temp->value = path;
        temp->numBits = length;
        temp->isValid = 1;
    }
    else {
        lTemp = calloc(CHAR_MAX, sizeof(char));
        strcpy(lTemp, path);
        *(lTemp + length) = '0';
        getPaths(root->left, lTemp, length + 1, table);
        rTemp = calloc(CHAR_MAX, sizeof(char));
        strcpy(rTemp, path);
        *(rTemp + length) = '1';
        getPaths(root->right, rTemp, length + 1, table);
        free(path);
    }
}

TableEntry *MakeTable(Node *root) {
    TableEntry *table = calloc(CHAR_MAX + 1, sizeof(TableEntry));

    getPaths(root, calloc(CHAR_MAX, sizeof(char)), 0, table);

    return table;
}

void FreeTable(TableEntry *table) {
    int idx;

    for (idx = 0; idx <= CHAR_MAX; idx++) {
        free(table[idx].value);
    }
    free(table);
}