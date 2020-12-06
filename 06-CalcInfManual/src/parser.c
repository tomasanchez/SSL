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


/*
===============================================================================================================================
============================================== Parser Design =================================================================
===============================================================================================================================
*/

/*class Parser{---------------------*/

    // Private:

        // Last token
        int currentToken;

        //Stores previous token
        value_t yytoken;

        // Gets next token from scanner
        static void match(int);

        // Handles error parsing
        static void yyperror();

        // <INPUT>
        static void lines();

        // <LINE>
        static void line();

        // <EXPR>
        static void expr();

        // <TERMS>
        static void terms();

        // <TERM>
        static void term();

        // <FACTORS>
        static void factors();

        // NUMBER || VAR
        static void factor();


/*};--------------------------------*/


/*
===============================================================================================================================
============================================== Exported Functions =============================================================
===============================================================================================================================
*/

int yyparse(){

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
    /*
        <Lines>   ->        |   <Input> <Line>
    
        getNextToken()
        if (EOF)
            exit();
        else
            line();
    
    */
        //Read token
        printf("> ");
        yytoken.num = peekNextToken();

        puts("IN LINES");
        if(yytoken.num == EOF){
            puts("EXIT LINES");
            return;
        }
        
        line(); lines();

        puts("EXIT LINES");
}

static void line(){
    /*
        <Line>    ->  EOL     |   <Expr> EOL
    */

   puts("IN LINE");

    if(yytoken.num == EOL){
        return;
    }
    
    expr(); match(EOL);
    
    puts("EXIT LINE");
}

static void expr(){
    /*
        <Expr>    ->  <Terms>
    */
   puts("IN EXPR");
   terms();
   puts("EXIT EXPR");
}

static void terms(){
    /*
        <Terms>     ->  <Term>      | <Term> ADD <Terms>
    */
    puts("IN TERMS");

    term();
    yytoken.num = peekNextToken();
    if(yytoken.num == ADD){
        match(ADD);
        puts("::MATCHED ADD::");
        terms();
    }

    puts("EXIT TERMS");
    return;

}

static void term(){
    /*
        <Term>      ->  <Factors>
    */
    puts("IN TERM");
    factors();
    puts("EXIT TERM");
}

static void factors(){
    /*
        <Factors>   -> <Factor>     | <Factor> MUL <Factors>
    */
    puts("IN FACTORS");
    factor();
    yytoken.num = peekNextToken();
    if(yytoken.num == MUL){
        match(MUL);
        puts("::MATCHED MUL::");
        factors();
    }
    puts("EXIT FACTORS");
   
   //TODO LONG JUMPS

}

static void factor(){
    /*
        <Factor>    -> NUMBER | VAR |   ( EXPR )

    */
   puts("IN FACTOR");
   yytoken.num = peekNextToken();

    switch (yytoken.num)
    {
    case NUMBER:
        match(NUMBER);
        puts("::MATCHED NUMBER::");
        return;

    case VAR:
        match(VAR);
        puts("::MATCHED VAR::");
        return;
    
    default:
        yyperror();
        break;
    }

   puts("EXIT FACTOR");
}