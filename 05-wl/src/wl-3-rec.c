/* ---------------------------------------------------------------------------------

    wl-3-rec.c

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

    last modified: 07/20/2020
------------------------------------------------------------------------------------ */

#include "sm-es.h"

/* Iterates the state machine, returning the number of iterations*/ 
static int sm_recursive_loop (stateMachine_t *);

int sm_recursive(void){

    stateMachine_t recursive;

    stateMachine_init(&recursive);

    sm_recursive_loop(&recursive);
    
    return  stateMachine_print(&recursive);
}

static int sm_recursive_loop (stateMachine_t * this_sm){


    if(stateMachine_is_reading(this_sm)){
        
        stateMachine_put(*this_sm);

        if(stateMachine_is_EOL(*this_sm))
            this_sm->current_state = SM_OUT;
        else
            this_sm->current_state = SM_IN;
        
        
    } else
        return 0;
    

    return 1 + sm_recursive_loop(this_sm);
}