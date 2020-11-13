%{
/*C - Code*/
#include "scanner.h"
int totalTokens_g;
bool allOK = true;
%}

%option noyywrap

%%
[0-9]+          { scanner_GetNextToken(atoi(yytext), OPERAND); totalTokens_g++;}
[a-zA-Z]+       { scanner_GetNextToken(*yytext, VARIABLE); totalTokens_g++;}
[+*-]+          { scanner_GetNextToken(*yytext, OPERATOR); totalTokens_g++;}
[(]             { scanner_GetNextToken(*yytext, LBRACKET);}
[\n|<<EOF>>]    { return 0;}
.               { puts("Undefined Symbol: Exiting..."); exit(-1);}
%%
