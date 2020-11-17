%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.tab.h"

/* Used for variable stores. Defined in mem.h */
extern int variable_values[100];
extern int variable_set[100];

/* Flex functions */
extern int yylex(void);
extern void yyterminate();
void yyerror(const char *s);
extern FILE* yyin;
%}

/* Bison declarations */

/* 
If you have used %union to specify a variety of data types, then you must declare a choice among these 
types for each terminal or nonterminal symbol that can have a semantic value. 
Then each time you use $$ or $n, its data type is determined by which symbol it refers to in the rule. 
(http://dinosaur.compilertools.net/bison/bison_6.html)
*/
%union {
	int index;
	int num;
}

%token<num> NUMBER
%token<num> L_BRACKET R_BRACKET
%token<num> MUL ADD SUB EQUALS
%token<num> LET
%token<index> VARIABLE
%type<num> assignment
%token<num> EOL
%type<num> input
%type<num> line
%type<num> calc
%type<num> expr

/*Operators precedence*/
%left SUB 
%left ADD
%left MUL 
%left L_BRACKET R_BRACKET

/*Grammar Rules*/
%%
input: 		
		|	input line
	;
line: 
			EOL 						 	{ printf("Please enter a calculation:\n"); }
		| 	calc EOL  						{ printf(":: = %d\n",$1); }
    ;
calc:
			expr
		|	assignment
	;

expr:
			SUB expr						{ $$ = -$2; }
    	| 	NUMBER            				{ $$ = $1; }
		| 	VARIABLE						{ $$ = variable_values[$1]; }
		| 	expr MUL expr     				{ $$ = $1 * $3; }
		| 	L_BRACKET expr R_BRACKET 		{ $$ = $2; }
		| 	expr ADD expr     				{ $$ = $1 + $3; }
		| 	expr SUB expr   				{ $$ = $1 - $3; }
    ;

assignment: 
		LET VARIABLE EQUALS calc 			{ $$ = set_variable($2, $4); }
		;

%%

/* Entry point */
int main(int argc, char **argv)
{
	char* c;
	printf("Command line or File? (Enter C or F): ");
	// Command line
	printf("Ok, command line it is!\n");
		
	yyin = stdin;
	yyparse();
}

/* Display error messages */
void yyerror(const char *s)
{
	printf("ERROR: %s\n", s);
}