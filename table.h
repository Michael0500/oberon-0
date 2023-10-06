#ifndef OBERON_0_TABLE_H
#define OBERON_0_TABLE_H

#include "scan.h"

/* Категории имен */
typedef enum {
    catConst, catVar, catType, catStProc, catModule, catGuard
} tCat;

/* Типы */
typedef enum {
    typNone, typInt, typBool
} tType;

/* Тип записи таблицы имен */
typedef struct tObjDesc {
    char Name[NAME_LEN+1]; /* ключ поиска */
    tCat Cat; /* Категория */
    tType Typ; /* Тип */
    int Val; /* Значение */
    struct tObjDesc *Prev; /* Указатель на предыдущее имя */
} tObj;

void InitNameTable(); /* Инициализация таблицы */
void Enter(char *Name, tCat Cat, tType Typ, int Val); /* Добавление елемента */
tObj *NewName(char *Name, tCat Cat); /* Занесение нового имени */
tObj *Find(char *Name); /* Поиск имени */
void OpenScope(); /* Открытие области видимости (блока) */
void CloseScope(); /* Закрытие области видимости (блока) */
tObj *FirstVar(); /* Поиск первой переменной */
tObj *NextVar(); /* Поиск следующей переменной */

#endif //OBERON_0_TABLE_H
