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

const char token_Name[2][9] = {"Operator", "Operand"};
parser_t parser_create(){
    parser_t new;
    new.read_token.index = buffer_clean(new.read_token.str);
    new.token_list = list_create();
    new.read_token.type = OPERAND;
    new.read_token.valid = false;
    new.previous_token = OPERATOR;
    return new;  
}

void parser_destroy(parser_t * this){
    list_destroy(this->token_list);
}

int parser_GetNextToken(parser_t * this, char * src, token_t parsed_type){

    for (int i = 0; src[i] < '\0'; i++)
    {
        this->read_token.str[i] = src[i];
    }

    if(VERBOSE)
        printf("[DEBUG][PARSER] %s :: Moved from tbuffer to obuffer as %s\n", src, this->read_token.str);
    
    this->read_token.type = parsed_type;
    this->read_token.valid = __token_is_valid__(this->read_token.type, this->previous_token);
    if(VERBOSE)
        printf("[DEBUG] Is token '%s' valid ? %s\n", this->read_token.str, this->read_token.valid? "true" : "false");
    
    this->previous_token = parsed_type;
    
    list_add(this->token_list, &this->read_token);
    
    return this->read_token.valid;
}

bool __token_is_valid__(token_t new, token_t previous){
    switch (new)
    {
    case OPERAND:
        return (previous == OPERAND || previous == OPERATOR) ? true : false;
        break;
    case OPERANDV:
        return previous == OPERATOR ? true : false;
    case OPERATOR:
        return (previous == OPERAND || previous == OPERANDV) ? true : false;
    
    default:
        return false;
    }
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
        printf("[TOKEN]\t-\t[OK]\t-\t%s\t::\t%s.\n", this_token->str, this_token->type == OPERAND ? "Operand" : "Operator");
    } else{
        printf("[TOKEN]\t-\t[INVALID]\t-\t%s\t::\t%s.\n", this_token->str, this_token->type == OPERAND ? "Operand" : "Operator");
    }
}