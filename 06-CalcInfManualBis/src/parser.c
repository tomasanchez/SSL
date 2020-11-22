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

        // Gets next token from scanner
        static void match(int);

        // Handles error parsing
        static void yyperror();

        // <INPUT>
        static void input();

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
        <Input>     ->              |   <Input> <Line>
        <Line>      ->  EOL         |   <Expr> EOL
        <Expr>      ->  <Terms>
        <Terms>     ->  <Term>      | <Term> ADD <Terms>
        <Term>      ->  <Factors>
        <Factors>   -> <Factor>     | <Factor> MUL <Factors>
        <Factor>    -> NUM          | VAR


        Based on GNU BISON Manual
        (https://www.gnu.org/software/bison/manual/bison.pdf)
    */
   input();

    return 0;
}

static void yyperror(){
    puts("Parse error.");
    puts("Calculator exited with parse error.");
    exit(2);
}

static inline void match(int tokenID){
    puts("Entered match");
    currentToken == getNextToken();
    
    switch (tokenID)
    {
    case NUMBER:
    case VAR:
            if(currentToken == tokenID)
                return;
            else
                yyperror;
        break;
    case ADD:
    case MUL:
            if(currentToken == tokenID)
                return;
            else if(currentToken == EOL)
                return;
        break;
    default:
            yyperror();
        break;
    }
}

/*
===============================================================================================================================
============================================== Lexical Transitions =============================================================
===============================================================================================================================
*/

static void input(){
    /*
        <Input>   ->   EOF     |   <Input> <Line>
    */
        line();
}

static void line(){
    /*
        <Line>    ->  EOL     |   <Expr> EOL
    */
        expr(); match(EOL);
}

static void expr(){
    /*
        <Expr>    ->  <Terms>
    */
   terms();
}

static void terms(){
    /*
        <Terms>     ->  <Term>      | <Term> ADD <Terms>
    */
   
    term();

    //TODO LONG JUMPS
    match(ADD); terms();

}

static void term(){
    /*
        <Term>      ->  <Factors>
    */

    factors();
}

static void factors(){
    /*
        <Factors>   -> <Factor>     | <Factor> MUL <Factors>
    */
   factor();
   
   //TODO LONG JUMPS

}

static void factor(){
    /*
        <Factor>    -> NUMBER | VAR
    */
   match(NUMBER);
}