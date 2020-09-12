/* ---------------------------------------------------------------------------------

    Calc.c

    Infix Manual Calculator

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

    last modified: 09/12/2020
------------------------------------------------------------------------------------ */

#include "../inc/Calc.h"

calculator_t calculator_create(){
    calculator_t new;
    new.scanner = scanner_create();
    new.index = buffer_clean(new.tbuffer);
    new.flags.running = true;
    new.flags.operand = new.flags.optor = false;
    new.token_type = new.previous_token = new.token_parsed =OPERAND;
    return new;
}

inline bool calculator_is_running(const calculator_t * this){
    return this->flags.running;
}

inline int calculator_new_token(calculator_t * this){
    return this->token_type != this->previous_token;
}

int calculator_GetNextToken(calculator_t * this){

    scanner_GetNextToken(this->tbuffer, &this->scanner);
    
    this->token_parsed = this->previous_token;

    parser_GetNextToken(&this->parser, this->tbuffer, this->token_parsed);

    return 0;
}

int calculator_parse(calculator_t * this){

}

int calculator_update(calculator_t * this){

    calculator_read(this);

    if(calculator_new_token(this) || !calculator_is_running(this)){
        calculator_GetNextToken(this);
    }

    return 0;
}

int calculator_read(calculator_t * this){

    token_t scanned_token = scanner_read(&(this->scanner));

    if ( scanned_token != INVALID ){
        this->previous_token = this->token_type;
        this->token_type = scanned_token;
        return 1;
    } else {
        puts("[NOTE] Invalid character - Aborting...");
        this->flags.running = false;
        return 0;
    }
}