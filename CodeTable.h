#include "tree.h"

typedef struct TableEntry {
    char *value;
    int numBits;
    int isValid;
} TableEntry;

TableEntry *MakeTable(Node *);
void FreeTable(TableEntry *);