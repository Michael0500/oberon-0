#include <stdio.h>
#include <string.h>

#include "text.h"
#include "ovm.h"
#include "gen.h"
#include "location.h"
#include "pars.h"
#include "scan.h"
#include "error.h"

void Init() {
    ResetText();
    if (ResetError) {
        Error(Message);
    }
    InitScan();
    InitGen();
}

void Done() {
    CloseText();
}

int main(int argc, char *argv[]) {
    puts("Компилятор языка O!\n");
    if (argc < 1)
        Path = NULL;
    else
        Path = argv[1];

    Init();
    Compile();
    Run();
    Done();

    return 0;
}
