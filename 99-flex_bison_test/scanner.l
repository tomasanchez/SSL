%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mem.h"
#include "parser.tab.h"
%}

/* Stop the error "undefined reference to 'yywrap'" from Flex */
%option noyywrap

%option noyywrap

%%
[ \t]
[0-9]+         					                { yylval.num = atoi(yytext); return NUMBER; }
[+]                         					{ return ADD; }
[-]                         					{ return SUB; }
[*]                         					{ return MUL; }
[=]												{ return EQUALS; }
[(]											    { return L_BRACKET; }
[)]												{ return R_BRACKET; }
("let")|("LET")									{ return LET; }
[a-zA-Z0-9]+  									{ yylval.index = add_variable(yytext); return VARIABLE;}
[\n|<<EOF>>]                        			{ return EOL; }
. 											    { yyerror("Undefined symbol"); exit(-1); } 
%%
