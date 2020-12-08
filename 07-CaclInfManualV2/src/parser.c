/* ---------------------------------------------------------------------------------

    parser.c

    parser for infix calculator.

    MIT License

    Copyright (c) 2020 Tomas Sanchez

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    last modified: 11/17/2020
------------------------------------------------------------------------------------ */

#include "../inc/parser.h"

extern value_t yyval;

/*
===============================================================================================================================
============================================== Parser Design =================================================================
===============================================================================================================================
*/

/*class Parser{---------------------*/

    // Private:

        // Last token
        struct Tokens{
            // Following scheme of bison
            int $$, $1, $2, $3, $4;
        }ls_token;

        //Stores previous token
        value_t yytoken;

        /*Tells if $x has initial value*/
        static bool isInitial(int);    

        /*Sets $X with initial value*/
        static void setInitial(int *);

        // Gets next token from scanner
        static void match(int);

        // Handles error parsing
        static void yyperror();

        // <INPUT>
        static void lines();

        // <LINE>
        static void line();

        // <EXPR>
        static int expr();

        // <TERMS>
        static int terms();

        // <TERM>
        static int term();

        // <FACTORS>
        static int factors();

        // NUMBER || VAR
        static int factor();


/*};--------------------------------*/


/*
===============================================================================================================================
============================================== Exported Functions =============================================================
===============================================================================================================================
*/

int yyparse(){

    // Initial status
    ls_token.$$ = 0;
    ls_token.$1 = ls_token.$2 = ls_token.$3 = ls_token.$4 = -1;

    /*
        <Lines>     ->              |    <Line> <Lines>
        <Line>      ->  EOL         |   <Expr> EOL
        <Expr>      ->  <Terms>
        <Terms>     ->  <Term>      | <Term> ADD <Terms>
        <Term>      ->  <Factors>
        <Factors>   -> <Factor>     | <Factor> MUL <Factors>
        <Factor>    -> NUM          | VAR


        Based on GNU BISON Manual
        (https://www.gnu.org/software/bison/manual/bison.pdf)
    */
   lines();

    return 0;
}

static void yyperror(){
    puts("Syntax error.\nCalculator exited with syntax error during parsing.");
    exit(2);
}

static void match(int tokenID){
    yytoken.num = getNextToken();

    if(yytoken.num == tokenID)
        return;
    else
        yyperror();
}

/*
===============================================================================================================================
============================================== Lexical Transitions =============================================================
===============================================================================================================================
*/

static void lines(){ // <Lines>

        //Read token
        printf("> ");
        yytoken.num = peekNextToken();

        if(yytoken.num == EOF){
            return;
        }
        
        line();

        lines();

}

static void line(){
    /*
        <Line>    ->  EOL     |   <Expr> EOL
    */

    if(yytoken.num == EOL){
        puts("Please, enter an expression");
        match(EOL);
        return;
    }
    
    int $$ = expr();
    
    printf(" = %d\n", $$);

    match(EOL);
    
}

static int expr(){
    /*
        <Expr>    ->  <Terms>
    */
   return terms();
}

static int terms(){
    /*
        <Terms>     ->  <Term>      | <Term> ADD <Terms>
    */

    int $$ = term();

    yytoken.num = peekNextToken();
    if(yytoken.num == ADD){
        match(ADD);
        $$ += terms();
    }

    return $$;

}

static int term(){
    /*
        <Term>      ->  <Factors>
    */
    return factors();
}

static int factors(){
    /*
        <Factors>   -> <Factor>     | <Factor> MUL <Factors>
    */
    int $$ = factor();

    yytoken.num = peekNextToken();
    if(yytoken.num == MUL){
        match(MUL);
        $$ *= factors();
    }
   
    return $$;
}

static int factor(){
    /*
        <Factor>    -> NUMBER | VAR |   ( EXPR )

    */

   int $$;

   yytoken.num = peekNextToken();

    switch (yytoken.num)
    {
    case NUMBER:
        match(NUMBER);
        return yyval.num;

    case VAR:
        match(VAR);
        return -1;
    
    case L_BRACKET:
        match(L_BRACKET);
        $$ = expr();
        match(R_BRACKET);
    case R_BRACKET:
        return $$;
    default:
        yyperror();
        break;
    }
}

/*
===============================================================================================================================
============================================== Internal Methods =============================================================
===============================================================================================================================
*/

static inline bool isInitial(int n){
    return n == -1;
}

static inline void setInitial(int * n){
    int * ptr = n;
    *ptr = -1;
}