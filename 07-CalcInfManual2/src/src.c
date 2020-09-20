/* ---------------------------------------------------------------------------------

    src.c

    Infix manual calculator test

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

#include "../inc/Calc.h"

int main(void){

    /*stack_t * this = stack_create();

    int * number;
    

    for(int i=0; i< 10; i++){
        number = malloc(sizeof(int));
        *number = i;
        stack_push(this, number);
    }

    while(!stack_is_empty(this)){
        int * n = stack_pop(this);
        printf(" >>%d<<\n",  *n);
        free(n);
    }

    stack_delete_and_delete_elements(this, free);*/


    calculator_t this_calculator = calculator_create();

    calculator_read(&this_calculator);

    calculator_update(&this_calculator);

    return calculator_delete(&this_calculator);
}