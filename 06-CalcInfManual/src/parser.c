/* ---------------------------------------------------------------------------------

    parser.c

    parser for infix calculator.

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
------------------------------------------------------------------------------------*/

#include "parser.h"

const char token_Name[2][10] = {"Operator", "Operand"};

parser_t parser_crate(){
    parser_t new;

    new.token_list = list_create();
    new.previous_token = OPERATOR;
    return new;  
}

void parser_destroy(parser_t * this){
    list_destroy(this->token_list);
}

int parser_GetNextToken(parser_t * this, char * src, token_t parsed_type){

    ptoken_t token;
    token.index = buffer_clean(token.str);
    strcpy(token.str, src);
    token.type = parsed_type;

    if(token.type == this->previous_token)
        token.valid = false;
    else
        token.valid = true;

    this->previous_token = parsed_type;
    
    list_add(this->token_list, &token);
    
    return token.valid;
}

int parser_print_results(parser_t * this){

    if(VERBOSE)
        puts("[DEBUG] Printing results ...\n");

    puts("--------------------------------------------------");
    puts("----------------------PARSER----------------------");
    puts("--------------------------------------------------");
    list_iterate(this->token_list, __print_token__);
    
    return 0;
}

void __print_token__(void * element){

    ptoken_t * this_token = (ptoken_t *) element;

    if(this_token->valid){
        printf("[TOKEN]\t-\t[OK]\t-\t%s\t::\t%s.\n", this_token->str, token_Name[this_token->type]);
    } else{
        printf("[TOKEN]\t-\t[INVALID]\t-\t%s\t::\t%s.\n", this_token->str, token_Name[this_token->type]);
    }
}