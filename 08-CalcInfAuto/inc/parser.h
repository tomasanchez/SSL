/* ---------------------------------------------------------------------------------

    parser.h

    Manual Parser for Infix Calculator w/ Automatic Scanner.

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
#include "solver.h"

/*Object Parser*/
typedef struct Parser{
    t_list * token_list;
    ptoken_t * read_token;
    token_id_t previous_token;
    bool valid_expression;
}parser_t;

/*Starts oParser*/
int parser_create();

/*Reads and parses expression*/
int parser_parse();

/*Evaluates expression*/
int parser_update();

/*Deletes oParser freeing memory usage*/
int parser_delete();

/*Parses a new token*/
bool parser_GetNextToken(int , token_id_t);

/*Prints all token parsed*/
int parser_print_results();



/*Tells if parse has error*/
bool parser_has_error();