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
#include "Calc.h"

/*Global Token Counter*/
int tokens_g;

calculator_t calculator_create(){
    puts(" :: == A Simple Infix Manual Calculator == :: ");
    calculator_t new;
    new.scanner = scanner_create();
    new.parser = parser_create();
    new.tokens = new.index = buffer_clean(new.tbuffer);
    new.flags.fst = new.flags.running = true;
    new.flags.operand = new.flags.optor = false;
    new.token_type = new.previous_token = new.token_parsed = OPERAND;
    tokens_g = 0;
    return new;
}

inline bool calculator_is_running(calculator_t * this){
    if (this->tokens >= this->scanner.tokens)
        this->flags.running = false;

    return this->flags.running;
}

inline int calculator_new_token(calculator_t * this){
    return (this->token_type != this->previous_token) && !this->flags.fst;
}

int calculator_GetNextToken(calculator_t * this){

    scanner_GetNextToken(this->tbuffer, &this->scanner);
    tokens_g = ++this->tokens;
    
    this->token_type        =                           calculator_validate_token(this);
    this->previous_token    = this->token_parsed    =   this->token_type;

    parser_GetNextToken(&this->parser, this->tbuffer, this->token_parsed);

    this->index = buffer_clean(this->tbuffer);

    return 0;
}

int calculator_update(calculator_t * this){

    calculator_read(this);

    while( calculator_is_running(this)){
        calculator_GetNextToken(this);
    }

    return 0;
}

inline int calculator_read(calculator_t * this){
    return scanner_read(&(this->scanner));;
}

token_t calculator_validate_token(calculator_t * this){
 return char_is_operator(*this->tbuffer) ? OPERATOR : OPERAND;
}

inline int calculator_print_results(calculator_t * this){
    scanner_syntax_check(&this->scanner);
    scanner_print(&this->scanner);
    return parser_print_results(&this->parser);
}

int calculator_destroy(calculator_t * this){
    parser_destroy(&this->parser);
    return 0;
}