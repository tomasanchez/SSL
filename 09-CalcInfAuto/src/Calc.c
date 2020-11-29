/* ---------------------------------------------------------------------------------

    Calc.c

    Infix With Automatic Scanner Calculator

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

    last modified: 11/09/2020
------------------------------------------------------------------------------------ */

#include "../inc/Calc.h"

int calculator_create(){

    parser_create();
    solver_create();

    return puts(" :: == A Simple Infix Calculator With Flex-Generated Scanner == :: ");
}

int calculator_read(){
    printf("  : > ");
    return  yylex();
}

int calculator_update(){
    parser_print_results();
    if(! parser_has_error()){
        solver_update();
        solver_print();
    }
    return OK;
}

int calculator_delete(){
    parser_delete();
    solver_delete();
    return puts("\n- :: © 2020 TOMAS SANCHEZ - <tosanchez@est.frba.utn.edu.ar> | :: | All rights reserved :: -");
}