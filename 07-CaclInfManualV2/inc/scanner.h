/* ---------------------------------------------------------------------------------

    scanner.h

    scanner for infix calculator.

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

#pragma once

#include "memory.h"

#define VERBOSE_SCANNER 1

/*Token IDs*/
typedef enum Token{

    EPSILON,
    //\n
    EOL,
    //[0-9]+
    NUMBER,
    //[a-zA-Z]
    VAR,
    //[ + ]
    ADD,
    //[ * ]
    MUL,
    //[ ( ]
    L_BRACKET,
    //[ ) ]
    R_BRACKET,
    //[ . ]
    UNDEFINED
}token_t;

/*Token value*/
typedef union Value{
    /*Number*/
    int num;

    /*TODO: Index of Variable*/
    int index;
}value_t;

/*Exporting...*/

/*Reads from stdin*/
int getNextToken();

/*Peeks token from stdin*/
int peekNextToken();

/*Ungets token*/
int ungetPreviousToken(int);
