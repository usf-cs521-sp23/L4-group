#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <ctype.h>
#include "words.h"

#define MAX_WORD   500

int validChar(char *word) {
    for (int i = 0; i < strlen(word) - 1; i++) {
        if (isalpha(word[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

char* toLower(char* s) {
    for(char *p=s; *p; p++) {
        *p=tolower(*p);
    }
    return s;
}

int getWord(char *randword) {
    /* Open words file */
    FILE *fp = fopen("/usr/share/dict/words", "r");

    if (fp == NULL) {
        perror("Unable to locate word list");
        exit(EXIT_FAILURE);
    }

    /* Count words in file */
    char word[MAX_WORD];
    long wc = 0;
    while (fgets(word, sizeof word, fp) != NULL) {
        ++wc;
    }

    /* Store random words in array */
    while(strlen(randword) == 0) {
        rewind(fp);
        int sel = rand() % wc + 1;
        for (int j = 0; j < sel; j++) {
            if (fgets(word, sizeof word, fp) == NULL) {
                perror("Error in fgets()");
            }
        }

        if (strlen(word) == 6 && validChar(word) == 0) {
            strcpy(randword, word);
            toLower(randword);
            break;
        }
    }

    if (fclose(fp) != 0) {
        perror("Unable to close file");
    }

    return 0;
}