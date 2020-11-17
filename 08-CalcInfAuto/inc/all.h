/* ---------------------------------------------------------------------------------

    all.h

    Infix Automatic Calculator header

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

    last modified: 11/12/2020
------------------------------------------------------------------------------------ */

#pragma once

#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "queue.h"

/* Verbose stdout */
#define VERBOSE 0
#define SCANNER 0
#define PARSER  0
#define SOLVER  0

/*Error handling*/
#define OK 0
#define ERROR -1


/*Defines size of scanner number buffer*/
#define  buffer_size 32

/*Lexical ID*/
typedef enum TokenIDs{
    OPERAND,
    VARIABLE,
    OPERATOR,
    LBRACKET,
    RBRACKET
}token_id_t;

/*Parsed tokens data struct*/
typedef struct pToken{
    bool valid;
    token_id_t type;
    unsigned int value;
}ptoken_t;

/*Calls Flex Scanner*/
int yylex();