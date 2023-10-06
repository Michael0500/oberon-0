#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"
#include "location.h"

#define TABSIZE 3
#define TRUE 1
#define FALSE 0

char ResetError = TRUE;
char* Message = "Файл не открыт";
int Ch = chEOT;

static FILE *f;

void ResetText() {
    if (NULL == Path) {
        puts("Формат вызова:\n  O <входной_файл>");
        exit(1);
    } else if ((f = fopen(Path, "r")) == NULL) {
        ResetError = TRUE;
        Message = "Файл не найден";
    } else {
        ResetError = FALSE;
        Message = "Ok";
        Pos = 0;
        Line = 1;
        NextCh();
    }
}

void CloseText() {
    fclose(f);
}

void NextCh() {
    if ((Ch = getc(f)) == EOF) {
        Ch = chEOT;
    } else if (Ch == '\n') {
        puts("");
        Line++;
        Pos = 0;
        Ch = chEOL;
    } else if (Ch == '\r') {
        NextCh();
    } else if (Ch != '\t') {
        putchar(Ch);
        Pos++;
    } else {
        do {
            putchar(' ');
        } while (++Pos % TABSIZE);
    }
}