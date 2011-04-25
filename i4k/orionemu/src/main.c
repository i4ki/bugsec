/*
  OrionEmu - Main file
  --------------------------------

  Author: Tiago Natel de Moura <tiago4orion@gmail.com>

  Copyright 2011 by Tiago Natel de Moura. All Rights Reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "types.h"
#include "parser_ast.h"
#include "parser_bison.h"

#define VERSION "0.1"
#define LICENSE "Apache License 2.0"
#define PROMPT "80386#> "

#define true 1
#define false 0

int yywrap() { return 1; }
extern int yyparse();
extern struct astlist program;

void banner()
{
        printf("OrionEmu - " VERSION " - " LICENSE "\n");
        printf("Emulator of 80386 microprocessor.\n");
        printf("Type help() for ...\n");
        printf("Press CTRL+D for exit.\n");
}

void banner_hlp()
{
        printf("=== OrionEmu MANUAL ===\n");
}

void clear_wnd()
{
        if(write(1,"\E[H\E[2J",7) || system("clear"));
                
}

void help(char* hlp)
{
        if (strstr(hlp, "registers") ||
            strstr(hlp, "regs") ||
            strstr(hlp, "reg"))
        {
                clear_wnd();
                banner_hlp();
                printf("\nPrint information about registers.\n");
                printf("Use registers() or regs() for information about all registers.\n");
                printf("Use register(reg) or reg(reg) for information about the register `reg`.\n\tExample: reg(eax)\n\n");
        }
}

extern int yydebug;
yydebug = 0;

void leave()
{
  fprintf(stdout, "saindo ...\n");
  free_astlist(&program);
}

int main(int argc, char** argv)
{
        banner();
        printf(PROMPT);

        atexit(leave);
        
        yyparse();
        
        return 0;
}
