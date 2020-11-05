/* ---------------------------------------------------------------------------------

    Calc.c

    Infix Automatic Calculator

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

    last modified: 11/05/2020
------------------------------------------------------------------------------------ */
#include "../inc/Calc.h"

/*Global Token Counter*/
extern int tokens_g;

calculator_t calculator_create(){
    puts(" :: == A Simple Infix Manual Calculator == :: ");
    calculator_t new;
    /*Creating all objects that make a calculator*/
    new.scanner = scanner_create();
    new.parser = parser_create();
    new.solver = solver_create();
    /*Initializing char buffer[]*/
    tokens_g = new.tokens = new.index = buffer_clean(new.tbuffer);
    new.flags.fst = new.flags.running = true;
    new.token_type = new.previous_token = OPERAND;
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

    /*Gets scanned token*/
    scanner_GetNextToken(this->tbuffer, &this->scanner);
    tokens_g = ++this->tokens;
    
    /*Gets token type*/
    this->token_type        =                           calculator_validate_token(this);
    solver_GetNextToken(&this->solver, this->tbuffer, this->token_type);
    this->previous_token    =   this->token_type;

    parser_GetNextToken(&this->parser, this->tbuffer, this->token_type);

    /*Empties buffer*/
    this->index = buffer_clean(this->tbuffer);

    return 0;
}

int calculator_update(calculator_t * this){
    this->tokens = tokens_g;
    /*If there is any syntax error, nothing else should work*/
    if(scanner_syntax_check(&this->scanner)){

        while( calculator_is_running(this)){
        calculator_GetNextToken(this);
        }
        solver_update(&this->solver);
    }
    calculator_print_results(this);
    return 0;
}

inline int calculator_read(calculator_t * this){
    return scanner_read(&(this->scanner));
}

token_t calculator_validate_token(calculator_t * this){
 return char_is_operator(*this->tbuffer) ? OPERATOR : char_is_parenthesis(*this->tbuffer)? PARENTHESIS : OPERAND;
}

inline int calculator_print_results(calculator_t * this){
    scanner_print(&this->scanner);

    if(scanner_syntax_check(&this->scanner)){
        parser_print_results(&this->parser);
        solver_print(&this->solver);
    }

    return puts("\n- :: © 2020 TOMAS SANCHEZ - <tosanchez@est.frba.utn.edu.ar> | :: | All rights reserved :: -");
}

int calculator_delete(calculator_t * this){
    solver_delete(&this->solver);
    parser_destroy(&this->parser);
    return 0;
}