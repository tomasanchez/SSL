%{
#include "scanner.h"    // For ID
// Avoiding warning implicit-function-declaration as fileno is no std in C
int fileno(FILE *);
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
.                                               { yyerror(*yytext);} 
%%

int getNextToken(){
    return yylex();
}

void yyerror(int c){
    printf("Flex Error: Undefined Symbol '%c'\nCalculator exited with error in scanner.\n", c);
    exit(1);
}