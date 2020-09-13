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
    scanner_t scanner;
    parser_t parser;
    cflags_t flags;
    token_t token_type, previous_token, token_parsed;
    char tbuffer[buffer_size];
    int index, tokens;
} calculator_t;

/*Starts a calculator ready to run*/
calculator_t calculator_create();

/*Checks if calculator is active*/
bool calculator_is_running(calculator_t *);

/*Updates lvalues of calculator*/
int calculator_update(calculator_t *);

/*Loads a new character into the calculator*/
int calculator_read(calculator_t *);

/*Checks if a new token has been detected*/
int calculator_new_token(calculator_t *);

/*Allow communication between parser and scanner*/
int calculator_GetNextToken(calculator_t *);

/*Writes resultos to stdout*/
int calculator_print_results(calculator_t *);

/*Closes program*/
int calculator_destroy(calculator_t *);