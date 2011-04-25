%{
#include "parser_bison.h"
%}

%%

"push" { return TPUSH; }
"pop"  { return TPOP; }
"ax"   { return TAX; }
"bx"   { return TBX; }
"cx"   { return TCX; }
"dx"   { return TDX; }
"sp"   { return TSP; }
"bp"   { return TBP; }
"si"   { return TSI; }
"di"   { return TDI; }
"ip"   { return TIP; }
"eax"  { return TEAX; }
"ebx"  { return TEBX; }
"ecx"  { return TECX; }
"edx"  { return TEDX; }
"esp"  { return TESP; }
"ebp"  { return TEBP; }
"esi"  { return TESI; }
"edi"  { return TEDI; }
"eip"  { return TEIP; }
[0-9]+ { yylval.n = atoi(yytext); return NUMBER; }
\n     { return EOL; }
[ \t]  { /* ignore empty space */ }
.      { printf("unknown character '%c'\n", *yytext); }

%%

