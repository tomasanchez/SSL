%{
/*C - Code*/
#include "scanner.h"
int totalTokens_g;
void getToken();
%}

%option noyywrap

%%
[0-9]+      { puts(yytext); totalTokens_g++;}
[a-zA-Z]+   { totalTokens_g++;}
[+*-]+      { puts(yytext); totalTokens_g++;}
.|\n        {return 0;}
%%

int scanner_GetNextToken(char *){

}

void scanner_sendNumber(){

}
