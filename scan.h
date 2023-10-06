#ifndef OBERON_0_SCAN_H
#define OBERON_0_SCAN_H

#define NAME_LEN 31 /* Наибольшая длина имени */
typedef char tName[NAME_LEN+1];

typedef enum {
    lexNone, lexName, lexNum,
    lexMODULE, lexIMPORT, lexBEGIN, lexEND,
    lexCONST, lexVAR, lexWHILE, lexDO,
    lexIF, lexTHEN, lexELSIF, lexELSE,
    lexMult, lexDIV, lexMOD, lexPlus, lexMinus,
    lexEQ, lexNE, lexLT, lexLE, lexGT, lexGE,
    lexDot, lexComma, lexColon, lexSemi, lexAss,
    lexLPar, lexRPar,
    lexEOT
} tLex;

extern tLex Lex; /* Текущая лексема */
extern char Name[]; /* Строковое значение имени */
extern int Num; /* Значение числовых литералов */
extern int LexPos; /* Позиция начала лексемы */

void InitScan();
void NextLex();

#endif //OBERON_0_SCAN_H
