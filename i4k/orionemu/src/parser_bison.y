/* parser */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_ast.h"

extern int yylex();
 void yyerror(const char* s) { printf("ERROR: %s\n", s); }

 /* all ast's */
struct astlist program;
%}

%union {
  struct ast *a;
  struct opcode *op;
  int reg;
  int n;
}

/* tokens */
%token <n> NUMBER
%token <reg> TAX TBX TCX TDX TSP TBP TSI TDI TIP
%token <reg> TEAX TEBX TECX TEDX TESP TEBP TESI TEDI TEIP
%token EOL TPUSH TPOP

%type <a> program stmts asm_directive
%type <op> opcode_mnemonic 
%type <n> reg

%%

program: stmts {
  DEBUG_AST($1);
  add_astlist(&program, $1);
  printf("stmts #> ");
  free_ast($1);
}
| program stmts {
  DEBUG_AST($2);
  add_astlist(&program, $2);
  printf("stmts 2 #> ");
  free_ast($2);
}
| program error EOL { yyerrok; printf("#> "); }
;

stmts: opcode_mnemonic {
        $$ = init_ast($1, NULL, NULL);  
}
| asm_directive {
        $$ = init_ast(NULL, NULL, "directive");
}
;

opcode_mnemonic: TPUSH reg EOL {
  printf("pushing %d register on the stack.\n#> ", $2);
  $$ = init_opcode(PUSH_REG, $2, 0, 0, 0);
}
| TPUSH NUMBER EOL {
  printf("pushing %d on the stack\n#>", $2);
  $$ = init_opcode(PUSH_NUMBER, 0, 0, 0, $2);
}
| TPOP reg EOL {
  printf("popping top of the stack into register %d\n", $2);
  $$ = init_opcode(POP, $2, 0, 0, 0);
}
;

/* tests */
asm_directive: TPUSH NUMBER NUMBER EOL { printf("directive called\n"); }
;

reg: TAX { $$ = AX; }
| TBX { $$ = BX; }
| TCX { $$ = CX; }
| TDX { $$ = DX; }
| TSP { $$ = SP; }
| TBP { $$ = BP; }
| TDI { $$ = DI; }
| TIP { $$ = IP; }
| TEAX  { $$ = EAX; }
| TEBX { $$ = EBX; }
| TECX { $$ = ECX; }
| TEDX { $$ = EDX; }
| TESP { $$ = ESP; }
| TEBP { $$ = EBP; }
| TEDI { $$ = EDI; }
| TEIP { $$ = EIP; }
;

%%
