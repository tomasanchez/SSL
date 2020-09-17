/* ---------------------------------------------------------------------------------

    stack.c

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

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    last modified: 09/14/2020
------------------------------------------------------------------------------------ */

#include "../inc/stack.h"

stack_t *stack_create() {
	stack_t * stack = malloc(sizeof(stack_t));
	t_list * elements = list_create();
	stack->index = 0;
	stack->elements = elements;
	return stack;
}

void stack_clean(stack_t *self) {
	list_clean(self->elements);
}

void stack_clean_and_delete_elements(stack_t *self, void(*element_destroyer)(void*)) {
	list_clean_and_destroy_elements(self->elements, element_destroyer);
}

void stack_delete(stack_t *self) {
	list_destroy(self->elements);
	free(self);
}

void stack_delete_and_delete_elements(stack_t *self, void(*element_destroyer)(void*)) {
	list_destroy_and_destroy_elements(self->elements, element_destroyer);
	free(self);
}

void stack_push(stack_t *self, void *element) {
	self->index++;
	list_add(self->elements, element);
}

void * stack_pop(stack_t *self) {
	return list_remove(self->elements, --self->index);
}


int stack_size(stack_t* self) {
	return self->index;
}

int stack_is_empty(stack_t *self) {
	return self->index < 1;
}