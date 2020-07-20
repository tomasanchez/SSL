/* ---------------------------------------------------------------------------------

    all.h

    Header for State machine based on The C Programming Language 1.5.4 example.

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

    last modified: 07/20/2020
------------------------------------------------------------------------------------ */

# pragma once

#include <stdio.h>

typedef enum SM_type{
    SM_GOTO,
    SM_SWITCH,
    SM_RECURSIVE
}SM_type_t;

/*  Switch test for state machine */
int sm_switch (void);

/* Goto test for state machine */
int sm_goto(void);

/* Recursive test for state machine*/
int sm_recursive(void);

/* Chooses what state machine to execute*/
SM_type_t sm_get_option(){
    int option;

    puts("Choose variant:");
    puts("[0] goto");
    puts("[1] switch");
    puts("[2] Recursive");
    scanf("%d", &option );

    return option;
}