/* ---------------------------------------------------------------------------------

    converter.h

    converts an infix expression to a reverse polish expression.

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
------------------------------------------------------------------------------------*/

#pragma once

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

typedef struct Stack{
    int top; 
    unsigned int capacity; 
    int* array; 
}Stack_t;

/*Creates a new stack with indicated size*/ 
Stack_t * Stack_create(int size);

/*Tells if stack is empty or not*/
int Stack_is_empty(Stack_t *);

/*Peeks top value*/
char Stack_peek(Stack_t *);

/*Pops next value*/
char Stack_pop(Stack_t *);

/*Push this operator*/
void Stack_push(Stack_t *, char operator);

/*Private function for telling if operand*/
int __is_operand__(int);

/*Private function to obtain operator precendence*/
int __precedence__(int);