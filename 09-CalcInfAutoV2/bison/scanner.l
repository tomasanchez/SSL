%{
#include "scanner.h"    // For IDs
// Avoiding warning implicit-function-declaration as fileno is no std in C
extern int fileno(FILE *);
%}

/* Stop the error "undefined reference to 'yywrap'" from Flex */
%option noyywrap

%%
[ \t]
[0-9]+         					                { yylval.num = atoi(yytext); return NUMBER; }
[+]                         					{ return ADD; }
[*]                         					{ return MUL; }
[=]                                             { return EQ; }
[(]                                             { return L_BRACKET; }
[)]                                             { return R_BRACKET; }
("let")|("LET")|("Let")                         { return LET; }
[a-zA-Z]+                                       { yylval.index = add_variable(yytext); return VAR;}
[\n]                                            { return EOL; }
.                                               { yyerror();} 
%%


int getNextToken(){
    return yylex();
}

void yyerror(){
    puts("Syntax error.");
    exit(1);
}