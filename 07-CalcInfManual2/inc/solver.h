/* ---------------------------------------------------------------------------------

    solver.h

    solver for infix calculator.

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

    last modified: 09/20/2020
------------------------------------------------------------------------------------ */

#pragma once

#include "scanner.h"

typedef struct Tok{
    int token;
    token_t type;
}tok_t;

typedef struct Solver{
    tok_t * token;
    t_queue * output_queue;
    stack_t * operator_stack;
    int final_result;
}solver_t;

/*Creates a solver*/
solver_t solver_create();

/*Frees memory usage form solver*/
void solver_delete(solver_t *);

/*Solves '(expression)' operations stacks*/
int solver_handle_parenthesis(solver_t *);

/*Stores next token*/
int solver_GetNextToken(solver_t *, char *, token_t);

/*Solves expression*/
int solver_update(solver_t *);

/*Print results*/
int solver_print(solver_t *);

/*Solve math expression a (operator) b, operator in {+,-,*}*/
int __solve__(int a, int b, char operator);

/*Determines precedence of operators*/
int __precedence__(char);

/*Creates a tok with the passed token and its type*/
tok_t * __tok_create__(int token, token_t type);
