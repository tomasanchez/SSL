/* ---------------------------------------------------------------------------------

    wl-1-enum-switch.c

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

    last modified: 07/10/2020
------------------------------------------------------------------------------------ */

#include "sm-es.h"

int sm_switch(void)
{

    stateMachine_t state_machine;

    assert(!stateMachine_init(&state_machine));

    while(stateMachine_is_reading(&state_machine)){

        ++state_machine.nc;

        switch (state_machine.c)
        {
        case '\n':
            ++state_machine.nl;
            state_machine.current_state=SM_OUT;
            break;

        case ' ':
        case '\t':
            state_machine.current_state = SM_OUT;
            break;

        default:
            state_machine.current_state == SM_OUT? state_machine.current_state = SM_IN, ++state_machine.nw: 0;
            break;
        }
    }

    stateMachine_print(&state_machine);

    return 0;
}