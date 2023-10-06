#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "scan.h"
#include "text.h"
#include "error.h"
#include "location.h"

#define KWNUM 34
tLex Lex; /* Текущая лексема */
tName Name; /* Строковое значкение имени */
int Num; /* Значение числовых литералов */

typedef char tKeyWord[9];  /* Длина слова PRODCEDURE */
static int nkw = 0;

static struct {
    tKeyWord Word;
    tLex Lex;
} KWTABLE[KWNUM];

static void EnterKW(tKeyWord Name, tLex Lex) {
    strcpy(KWTABLE[nkw].Word, Name);
    KWTABLE[nkw].Lex = Lex;
    nkw++;
}

static tLex TestKW() {
    int i;
    for (i = nkw - 1; i >= 0; i--) {
        if (strcmp(KWTABLE[i].Word, Name) == 0) {
            return KWTABLE[i].Lex;
        }
    }

    return lexName;
}

static void Ident() {
    int i = 0;
    do {
        if (i < NAME_LEN) {
            Name[i] = Ch;
            i++;
        } else {
            Error("Слишком длинное имя");
        }
        NextCh();
    } while (isalnum(Ch));
    Name[i] = '\0';
    Lex = TestKW(); /* Проверка на ключевое слово */
}

static void Number() {
    int d;

    Lex = lexNum;
    Num = 0;
    do {
        d = Ch - '0';
        if ((INT_MAX - d) / 10 >= Num) {
            Num = 10 * Num + d;
        } else {
            Error("Слишком большое число");
        }
        NextCh();
    } while (isdigit(Ch));
}

static void Comment() {
    int Level = 1;
    NextCh();
    do {
        if (Ch == '*') {
            NextCh();
            if (Ch == ')') {
                Level--;
                NextCh();
            }
        } else if (Ch == '(') {
            NextCh();
            if (Ch == '*') {
                Level++;
                NextCh();
            }
        } else { /* if <> chEOT */
            NextCh();
        }
    } while (Level && Ch != chEOT);

    if (Level) {
        LexPos = Pos;
        Error("Незавершенный комментарий");
    }
}

void NextLex() {
    while (Ch == chSpace || Ch == chTab || Ch == chEOL) {
        NextCh();
    }
    LexPos = Pos;
    if (isalpha(Ch)) {
        Ident();
    } else if (isdigit(Ch)) {
        Number();
    } else {
        switch (Ch) {
            case ';':
                NextCh();
                Lex = lexSemi;
                break;
            case ':':
                NextCh();
                if (Ch == '=') {
                    NextCh();
                    Lex = lexAss;
                    break;
                }
                Lex = lexColon;
                break;
            case '.':
                NextCh();
                Lex = lexDot;
                break;
            case ',':
                NextCh();
                Lex = lexComma;
                break;
            case '=':
                NextCh();
                Lex = lexEQ;
                break;
            case '#':
                NextCh();
                Lex = lexNE;
                break;
            case '<':
                NextCh();
                if (Ch == '=') {
                    NextCh();
                    Lex = lexLE;
                    break;
                }
                Lex = lexLT;
                break;
            case '>':
                NextCh();
                if (Ch == '=') {
                    NextCh();
                    Lex = lexGE;
                    break;
                }
                Lex = lexGT;
                break;
            case '(':
                NextCh();
                if (Ch == '*') {
                    Comment();
                    NextLex();
                } else {
                    Lex = lexLPar;
                }
                break;
            case ')':
                NextCh();
                Lex = lexRPar;
                break;
            case '+':
                NextCh();
                Lex = lexPlus;
                break;
            case '-':
                NextCh();
                Lex = lexMinus;
                break;
            case '*':
                NextCh();
                Lex = lexMult;
                break;
            case chEOT:
                Lex = lexEOT;
                break;
            default:
                Error("Недопустимый символ");
        }
    }
}

void InitScan() {
    EnterKW("ARRAY", lexNone);
    EnterKW("BY", lexNone);
    EnterKW("BEGIN", lexBEGIN);
    EnterKW("CASE", lexNone);
    EnterKW("CONST", lexCONST);
    EnterKW("DIV", lexDIV);
    EnterKW("DO", lexDO);
    EnterKW("ELSE", lexELSE);
    EnterKW("ELSIF", lexELSIF);
    EnterKW("END", lexEND);
    EnterKW("EXIT", lexNone);
    EnterKW("FOR", lexNone);
    EnterKW("IF", lexIF);
    EnterKW("IMPORT", lexIMPORT);
    EnterKW("IS", lexNone);
    EnterKW("IN", lexNone);
    EnterKW("LOOP", lexNone);
    EnterKW("MOD", lexMOD);
    EnterKW("MODULE", lexMODULE);
    EnterKW("NIL", lexNone);
    EnterKW("OF", lexNone);
    EnterKW("OR", lexNone);
    EnterKW("POINTER", lexNone);
    EnterKW("PROCEDURE", lexNone);
    EnterKW("RECORD", lexNone);
    EnterKW("REPEAT", lexNone);
    EnterKW("RETURN", lexNone);
    EnterKW("THEN", lexTHEN);
    EnterKW("TO", lexNone);
    EnterKW("TYPE", lexNone);
    EnterKW("UNTIL", lexNone);
    EnterKW("VAR", lexVAR);
    EnterKW("WHILE", lexWHILE);
    EnterKW("WITH", lexNone);

    NextLex();
}