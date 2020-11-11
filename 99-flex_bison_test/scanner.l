%{
/*C - Code*/
#include <stdio.h>
int totalTokens_g;
%}

%option noyywrap

%%
[0-9]+      { puts(yytext); totalTokens_g++;}
[a-zA-Z]+   { totalTokens_g++;}
[+*-]+      { puts(yytext); totalTokens_g++;}
.|\n        {return 0;}
%%

int main(){
    puts("Hello World!");
    yylex();
}