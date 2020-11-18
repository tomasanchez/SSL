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
        int lastToken;

        // Gets next token from scanner
        static void match(int);

        // <INPUT>
        static void input();

        // <LINE>
        static void line();

        // <EXPR>
        static void expr();

        // <MUL>
        static void mul();

        // <ADD>
        static void add();


/*};--------------------------------*/


/*
===============================================================================================================================
============================================== Exported Functions =============================================================
===============================================================================================================================
*/

int yyparse(){

    /*
        <Input>   ->   EOF     |   <Input> <Line>
        <Line>    ->  EOL     |   <Expr> EOL
        <Expr>    ->  NUMBER  |   VAR     |   <Expr> MUL <Expr>   |   <Expr> ADD <Expr> 

        Inspired on GNU BISON Manual
        (https://www.gnu.org/software/bison/manual/bison.pdf)
    */
   input();

    return 0;
}

static void match(int tokenID){

    if( tokenID == getNextToken()){

        switch (tokenID)
        {
            case EOF:
                exit(0);
                break;
    
            default:
                puts("SI");
                break;
        }

    } else{
        puts("Parse error");
        exit(1);
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
   
   if( (lastToken = getNextToken()) == EOF)
        match(EOF);
    else
        line();
}

static void line(){
    /*
        <Line>    ->  EOL     |   <Expr> EOL
    */

   match(EOL);

   expr();
   match(EOL);

}

static void expr(){

    match(NUMBER);

    match(VAR);
}