#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "tree.h"

#define PERMS       0700
#define BUF_SIZE    1024
#define CHAR_SIZE   8

int GetBit() {
    static char value = 0, bitsLeft = 0;
    int readValue, ret;

    if (bitsLeft == 0) {
        if ((readValue = read(0, &value, sizeof(char))) == -1) {
            perror(NULL);
            exit(EXIT_FAILURE);
        }
        if (readValue == 0) {
            fprintf(stderr, "Unexpected EOF\n");
            exit(EXIT_FAILURE);
        }
        bitsLeft = CHAR_SIZE;
    }

    ret = value & 1 << --bitsLeft;

    return ret;
}

void ClearBuffer(char *buf, int size) {
    while (size--) {
        *buf++ = 0;
    }
}

int main(int argc, char *argv[]) {
    int inFd, outFd, numChars, idx, count, bufUsed = 0;
    char cidx, cur, buf[BUF_SIZE];
    int *counts = calloc(CHAR_MAX + 1, sizeof(int));
    Node *root, *temp;

    if (argc >= 2 && strcmp(argv[1], "-")) {
        inFd = open(argv[1], O_RDONLY);
        if (inFd == -1) {
            perror(argv[1]);
            return -1;
        }
        dup2(inFd, 0);
        close(inFd);
    }
    if (argc >= 3) {
        outFd = open(argv[2], O_CREAT|O_TRUNC|O_WRONLY, PERMS);
        dup2(outFd, 1);
        close(outFd);
    }

    read(0, &numChars, sizeof(int));

    idx = numChars;

    while (idx--) {
        read(0, &cidx, sizeof(char));
        read(0, &count, sizeof(int));
        counts[(int)cidx] = count;
    }

    root = CreateTree(counts);

    free(counts);

    count = root->count;

    temp = root;

    ClearBuffer(buf, BUF_SIZE);
    while (count) {
        if (temp->isLeaf) {
            buf[bufUsed++] = temp->data;
            if (bufUsed == BUF_SIZE) {
                write(1, buf, BUF_SIZE * sizeof(char));
                ClearBuffer(buf, BUF_SIZE);
                bufUsed = 0;
            }
            temp = root;
            count--;
        }
        else {
            cur = GetBit();
            if (cur) {
                temp = temp->right;
            }
            else {
                temp = temp->left;
            }
        }
    }
    if (bufUsed) {
        write(1, buf, bufUsed * sizeof(char));
    }
    FreeTree(root);

    return 0;
}