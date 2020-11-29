/* ---------------------------------------------------------------------------------

    Calc.h

    Infix Manual Calculator header

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

    last modified: 09/10/2020
------------------------------------------------------------------------------------ */

#pragma once
#include "scanner.h"
#include "parser.h"

typedef struct Flags{
    bool fst,optor, operand, running;
} cflags_t;

typedef struct Calculator{
    
    parser_t parser; 
        scanner_t scanner;
    cflags_t flags;
        token_t token_type, previous_token, token_parsed;
    char tbuffer[buffer_size];
    int index, tokens;
} calculator_t;

/*Public*/

/*Starts a calculator ready to run*/
calculator_t calculator_create();

/*Updates lvalues of calculator*/
int calculator_update(calculator_t *);

/*Scans characters into the calculator until '\n' is pushed*/
int calculator_read(calculator_t *);

/*Closes program*/
int calculator_delete(calculator_t *);
