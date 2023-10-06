#ifndef OBERON_0_TEXT_H
#define OBERON_0_TEXT_H

#define chSpace ' ' /* Пробел */
#define chTab '\t' /* Табуляция */
#define chEOL '\n' /* Конец строки */
#define chEOT '\0' /* Конец текста */

extern char ResetError;
extern char *Message;
extern int Ch;

void ResetText();
void CloseText();
void NextCh();

#endif //OBERON_0_TEXT_H
