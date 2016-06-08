#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "tree.h"
#include "CodeTable.h"

#define PERMS       0700
#define CHAR_SIZE   8

void BitPack(char bit, int last) {
    static char buf = 0, bitsLeft = CHAR_SIZE;

    buf |= (1 & bit) << --bitsLeft;
    if (!bitsLeft || last) {
        write(1, &buf, sizeof(char));
        buf = 0;
        bitsLeft = CHAR_SIZE;
    }
}

int main(int argc, char *argv[]) {
    int numChars = 0, *counts, idx, inFd, outFd, total;
    Node *root;
    unsigned char cidx;
    char *temp;
    TableEntry *codes;
    TableEntry entry;

    counts = calloc(CHAR_MAX + 1, sizeof(int));

    if (argc == 1) {
        fprintf(stderr, "usage: %s infile [outfile]\n", *argv);
        return -1;
    }

    inFd = open(argv[1], O_RDONLY);
    if (inFd == -1) {
        perror(argv[1]);
        return -1;
    }
    dup2(inFd, 0);
    close(inFd);

    if (argc == 3) {
        outFd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, PERMS);
        if (inFd == -1) {
            perror(argv[1]);
            return -1;
        }
        dup2(outFd, 1);
        close(outFd);
    }

    while (read(0, &cidx, sizeof(char))) {
        if (!counts[(int)cidx]) {
            numChars++;
        }
        counts[(int)cidx]++;
    }
    idx = 0;

    write(1, &numChars, sizeof(int));

    for (idx = 0; idx <= CHAR_MAX; idx++) {
        cidx = idx;
        if (counts[idx]) {
            write(1, &cidx, sizeof(char));
            write(1, counts + idx, sizeof(int));
        }
    }

    root = CreateTree(counts);
    total = root->count;

    codes = MakeTable(root);

    FreeTree(root);

    idx = 0;
    lseek(0, 0, SEEK_SET);
    while (read(0, &cidx, sizeof(char))) {
        entry = codes[(unsigned int)cidx];
        idx++;
        for (temp = entry.value; *temp; temp++) {
            BitPack(*temp - '0', idx == total && !*(temp + 1));
        }
    }

    FreeTable(codes);

    return 0;
}