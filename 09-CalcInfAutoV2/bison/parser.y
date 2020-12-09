%{
#include "scanner.h"
#include "parser.tab.h"

/* Flex functions */
extern void yyterminate();

void yyerror(const char *s);

static int yylex();
%}

/* Bison declarations */

/* 
    When using %union specifying multiples data types, a choice must be declared among these 
    types for each terminal or nonterminal symbol that can have a semantic value. 
    Then each time you use $$ or $n, its data type is determined by which symbol it refers to in the rule.
    (http://dinosaur.compilertools.net/bison/bison_6.html)

    Where 
    $$ - In an action, the semantic value of the left-hand side of the rule. See Section 3.4.6[Actions], page 59.
    $n - In an action, the semantic value of then-th symbol of the right-hand side of the rule.See Section 3.4.6 [Actions], page 59.
    (https://www.gnu.org/software/bison/manual/bison.pdf)
*/
%union {
	int index;
	int num;
}

/*  Tokens  */
%token<num> NUMBER
%token<num> L_BRACKET R_BRACKET
%token<num> MUL ADD EQ
%token<num> LET
%token<index> VAR
%token<num> EOL
%type<num>  lines
%type<num>  line
%type<num>  calc
%type<num>  expr
%type<num>  terms
%type<num>  term
%type<num>  factors
%type<num>  factor
%type<num>  assignment


/*Operators Association*/
%left ADD
%left MUL 
%left L_BRACKET R_BRACKET

/*Grammar Rules*/
%%
lines:
        |   lines line

    ;
line:
            EOL                                 { printf("Please enter a calculation:\n"); }
        |   calc EOL                            { printf("  = %d", $1); }
    ;
calc:
            expr
        |   assignment
    ;
expr:
            terms
    ;
terms:
            term
        |   terms ADD term                      { $$ = $1 + $3; }
    ;
term:
            factors
    ;
factors:
            factor
        |   factors MUL factor                  { $$ = $1 * $3; }
    ;
factor:
            NUMBER                              { $$ = $1; }
        |   VAR                                 { $$ = get_variable($1); }
        |   L_BRACKET expr  R_BRACKET           { $$ = $2; }
    ;
assignment:
            LET VAR EQ calc                     { $$ = set_variable($2, $4); }
        ;
%%

static int yylex(){
    return getNextToken();
}