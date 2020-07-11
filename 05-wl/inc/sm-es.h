/* ---------------------------------------------------------------------------------

    sm-es.h

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

    last modified: 07/10/2020
------------------------------------------------------------------------------------ */

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*Machine status: OUT, or IN*/
typedef enum state {
    SM_OUT,
    SM_IN
} state_t;

/* State Machine */
typedef struct machine{
    state_t current_state;

    // Char buffer
    int c;
    // number of lines
    int nl;
    // number of characters
    int nc;
    // number of words
    int nw;

} stateMachine_t;

/* Creates a new state machine */
int stateMachine_init(stateMachine_t * this_sm){
    this_sm->c = this_sm->nc = this_sm->nl = this_sm->nw = 0;
    this_sm->current_state = SM_OUT;
    return this_sm->c && this_sm->nc && this_sm->nl && this_sm->nw && (int)this_sm->current_state;
}

/* Verifies if characters are being read*/
int stateMachine_is_reading(stateMachine_t * this_sm){
    return (this_sm->c = getchar()) != EOF;
}

/* Outputs to stdout counter results*/
int stateMachine_print(const stateMachine_t * this_sm){
    printf("No. of lines: %d\nNo. of words: %d\nNo. of characters: %d\n", this_sm->nl, this_sm->nw, this_sm->nc);
    return puts("© 2020 TOMAS SANCHEZ - <tosanchez@est.frba.utn.edu.ar | All rights reserved");
}
