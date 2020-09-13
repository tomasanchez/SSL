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

    last modified: 09/10/2020
------------------------------------------------------------------------------------ */

#pragma once
#include "parser.h"

typedef struct Sflags{
    bool fst, optor, operand, overwritten;
} sflags_t;

typedef struct Scanner {
    char ibuffer[buffer_size];
    int index, tokens;
    sflags_t flags;
} scanner_t;

/* Creates a scanner */
scanner_t scanner_create();

/*Scans a character from*/
token_t scanner_read(scanner_t *);

/*Checks if is a valid scan*/
int scanner_is_valid(scanner_t *, int);

/*Investigates if buffer is being overwritten*/
int scanner_check_buffer(scanner_t *);

/*Checks if is a valid number Number = [0..9]*/
bool scanner_is_number(int);

/*Checks if is a valid operator, from the operator list*/
bool scanner_is_operator(int);

/*Checks if scanner is a Variable = [a..z,A..Z]*/
bool scanner_is_variable(int);

/*Loads new token from scanner buffer*/
int scanner_GetNextToken(char *, scanner_t *);
