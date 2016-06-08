#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#include "tree.h"
#include "CodeTable.h"

int main(int argc, char *argv[]) {
    double probability, avg = 0, entropy = 0;
    int numChars, idx, count, inFd;
    int *counts = calloc(CHAR_MAX + 1, sizeof(int));
    unsigned char cidx;
    Node *root;
    TableEntry *table;
    
    if (argc >= 2 && strcmp(argv[1], "-")) {
        inFd = open(argv[1], O_RDONLY);
        if (inFd == -1) {
            perror(argv[1]);
            return -1;
        }
        dup2(inFd, 0);
        close(inFd);
    }

    read(0, &numChars, sizeof(int));

    idx = numChars;

    while (idx--) {
        read(0, &cidx, sizeof(char));
        read(0, &count, sizeof(int));
        counts[(int)cidx] = count;
    }

    root = CreateTree(counts);

    table = MakeTable(root);

    count = root->count;

    for (idx = 0; idx <= CHAR_MAX; idx++) {
        probability = (double)counts[idx] / count;
        if (probability) {
            entropy -= probability * log2(probability);
            avg += probability * table[idx].numBits;
        }
    }

    printf("entropy of the data is: %f\n", entropy);

    printf("average code length of the data is: %f\n", avg);

    printf("the efficiency of the encoding is: %f\n", entropy / avg);

    return 0;
}