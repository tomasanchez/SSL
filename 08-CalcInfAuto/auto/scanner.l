%{
/*C - Code*/
#include "scanner.h"
int totalTokens_g;
%}

%option noyywrap

%%
[0-9]+      { scanner_GetNextToken(yytext, OPERAND); totalTokens_g++;}
[a-zA-Z]+   { scanner_GetNextToken(yytext, OPERAND); totalTokens_g++;}
[+*-]+      { scanner_GetNextToken(yytext, OPERATOR); totalTokens_g++;}
\n          { return 0;}
.           { puts("Syntax Error, closing ..."); exit(-1);}
%%
