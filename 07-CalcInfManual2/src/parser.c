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

#include "../inc/parser.h"

extern int tokens_g;
int tokens_gp = 0;

parser_t parser_create(){
    parser_t new;
    new.token_list = list_create();
    new.read_token = __ptoken_create__();
    new.previous_token = OPERATOR;
    return new;  
}

ptoken_t * __ptoken_create__(){
    ptoken_t * new = malloc(sizeof(ptoken_t));
    new->index = buffer_clean(new->str);
    new->type = OPERATOR;
    new->valid = false;
    return new;
}

void __ptoken_destroy__(void * element){
    free (element);
}

inline void parser_destroy(parser_t * this){
    free(this->read_token);
    list_destroy_and_destroy_elements(this->token_list, __ptoken_destroy__);
}

int parser_GetNextToken(parser_t * this, char * src, token_t parsed_type){

    for (int i = 0; src[i] != '\0'; i++)
    {
        this->read_token->str[i] = src[i];
    }

    if(VERBOSE && PARSER)
        printf("[DEBUG] :: [PARSER] %s --> %s :: tbuffer ---> obuffer.\n", src, this->read_token->str);
    
    tokens_gp++;
    this->read_token->type = parsed_type;
    this->read_token->valid = __token_is_valid__(this->read_token->type, this->previous_token);

    if(parsed_type == OPERAND){
        sprintf(this->read_token->str, "%d", atoi(this->read_token->str));
        if(this->read_token->valid)
            this->read_token->valid = __is_valid_operand__(src);
    }
        
    
    if(VERBOSE && PARSER)
        printf("[DEBUG] :: [PARSER] :: Is token '%s' valid ? :: '%s'.\n", this->read_token->str, this->read_token->valid? "YES" : "NO");
    
    this->previous_token = parsed_type;
    
    list_add(this->token_list, this->read_token);

    this->read_token = __ptoken_create__();
    
    return this->read_token->valid;
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

    if(VERBOSE && PARSER)
        puts("[DEBUG] Printing results ...\n");

    if( tokens_g > 0){
        puts("\n:=-----------------::========::-----------------=:");
        puts(" :: :: :: :: :: :: :: PARSER :: :: :: :: :: :: :: ");
        puts(":=-----------------::========::-----------------=:\n");
        if( tokens_g > 1)
            list_iterate(this->token_list, __print_token__);
        else
            list_iterate(this->token_list, __print_one__);
    } else
        puts("\n :: No valid character has been entered :: ");
    
    return 0;
}

void __print_one__(void * element){

    ptoken_t * this_token = (ptoken_t *) element;

    if(this_token->type != OPERAND)
    printf(">> PARSED :: Invalid expression :: '%s' :: Operator.\n", this_token->str);
    else
    printf(">> PARSED :: [VALID] :: '%s' :: Operand.\n", this_token->str);
}

void __print_token__(void * element){

    ptoken_t * this_token = (ptoken_t *) element;

    if(this_token->valid){
        printf(">> PARSED :: [ VALID ] :: '%s'\t:: %s.\n", this_token->str, this_token->type == OPERAND ? "Operand" : "Operator");
    } else{
        printf(">> PARSED :: [INVALID] :: '%s'\t:: %s.\n", this_token->str, this_token->type == OPERAND ? "Operand" : "Operator");
    }
}

bool __is_valid_operand__(char * this){

    bool integer, id;

    integer = char_is_number(*this);
    id = !integer;

    //Patterng matching
    if( id && this[1] != '\0')
        return false;

    for (int i = 1; this[i] != '\0'; i++){

            // Checking for non-decimal imputs
            if( char_is_number(this[i])){
                if(id)
                    return false;
                id = false;
                integer = !id;
            }

            if(char_is_variable(this[i])){
                if(integer)
                    return false;
                integer = true;
                id = !integer;
            }
    }

    return true;
}