/* ---------------------------------------------------------------------------------

    parser.h

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

    last modified: 09/12/2020
------------------------------------------------------------------------------------ */
#pragma once
#include "all.h"

typedef struct Parser{
    t_list * token_list;
    ptoken_t * read_token;
    token_t previous_token;
}parser_t;

/*Creates a new usable parser*/
parser_t parser_create();

/*Adds token to the list*/
int parser_GetNextToken(parser_t *, char *, token_t);

/*Writes parsed tokens to stdout, telling if valid or not*/
int parser_print_results(parser_t *);

/*Frees memory usage*/
void parser_destroy(parser_t *);

/*  Private Function :: writes a token to stdout*/
void __print_token__(void *);
/*  Private Function :: wirtes unique token to stdout*/
void __print_one__(void * element);

/*  Private Function :: Validates a token*/
bool __token_is_valid__(token_t, token_t);

/* Checks if a number is Decimal or an unique variable*/
bool __is_valid_operand__(char *);
