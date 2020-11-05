/* ---------------------------------------------------------------------------------

    scanner.c

    State machine based on The C Programming Language 1.5.4 example.

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

    This file is a modify version of "queue.h" 2012 Sistemas Operativos - UTN FRBA.
    In this version queue was updated to match last in first out accounting method
    as queue represent a first in first out method, some functions were deleted and
    others barely touched in order to obtain the last item instead of the first one.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    

    last modified: 09/15/2020
------------------------------------------------------------------------------------ */

#pragma once

#include "list.h"
#include <stdlib.h>


#ifndef STACK_H_
#define STACK_H_

	
	typedef struct Stack{
		t_list* elements;
        int index;
	}stack_t;

    /*Creates a stack pointer to the top*/
	stack_t * stack_create();

    /*Deletes memory usage of stack*/
	void stack_delete(stack_t *);

    /*Deletes memory usage of each element of the stack, needs element destroyer function*/
	void stack_delete_and_delete_elements(stack_t *, void(*element_destroyer)(void *));

    /*Puts an element at the top of the stack*/
	void stack_push(stack_t *, void *element);

	/*Removes first element of stack*/
	void * stack_pop(stack_t *);

	/*Deletes all elements of stack*/
	void stack_clean(stack_t *);

   /*DCleans stack and deletes all elements*/
	void stack_clean_and_delete_elements(stack_t *, void(*element_destroyer)(void*));

	/*Finds number of elements stacked*/
	int stack_size(stack_t *);

    /*Tells if stack is empty or not*/
	int stack_is_empty(stack_t *);

#endif /*stack_H_*/