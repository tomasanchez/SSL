/* ---------------------------------------------------------------------------------

    parser.c

    Manual Parser for infix calculator.

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

    last modified: 11/12/2020
------------------------------------------------------------------------------------*/

#include "../inc/parser.h"

/*Global Token counter*/
extern int totalTokens_g;

/*Local Parser*/
parser_t oParser;
unsigned int cTokens;
unsigned int rBrackets = 0;
unsigned int lBrackets = 0;

/*Private Functions*/

/*  Private Function :: writes a token to stdout*/
void __print_token__(void *);

/*  Private Function :: wirtes unique token to stdout*/
void __print_one__(void * element);

/*  Private Function :: Validates a token*/
bool __token_is_valid__(token_id_t, token_id_t);

/*  Private Function :: Creates an element for a list*/
ptoken_t * __ptoken_create__(void);

/* Checks if a number is Decimal or an unique variable*/
bool __is_valid_operand__(char *);

/*
===============================================================================================================================
============================================= PARSER ALLOCATIONS  =============================================================
===============================================================================================================================
*/

int parser_create(){
    oParser.token_list = list_create();
    oParser.read_token = __ptoken_create__();
    oParser.previous_token = OPERATOR;
    oParser.valid_expression = true;
    return OK;
}

int parser_delete(){
    free(oParser.read_token);
    /*As no items are removed, elements need to be deleted with the list*/
    list_destroy_and_destroy_elements(oParser.token_list, free);
    return OK;
}


ptoken_t * __ptoken_create__(){
    ptoken_t * new = malloc(sizeof(ptoken_t));
    new->value = '+';
    new->type = OPERATOR;
    new->valid = false;
    return new;
}

/*
===============================================================================================================================
============================================= TOKENS HANDLING =================================================================
===============================================================================================================================
*/



bool parser_GetNextToken(int src, token_id_t parsed_type){

    oParser.read_token->value = src;
    oParser.read_token->type = parsed_type;

    if(parsed_type == LBRACKET)
        ++lBrackets;

    if(parsed_type == RBRACKET)
        ++rBrackets;

    oParser.read_token->valid = __token_is_valid__(parsed_type, oParser.previous_token);

    oParser.valid_expression = oParser.valid_expression && oParser.read_token->valid;

    if(VERBOSE && PARSER && parsed_type == OPERAND)
        printf("[DEBUG] :: [PARSER] %d --> %d :: oScanner ---> oPaser.\n :: -> Is token Valid? %s\n", src, oParser.read_token->value, oParser.read_token->valid? "YES" : "NO");
    
    if(VERBOSE && PARSER && parsed_type != OPERAND)
        printf("[DEBUG] :: [PARSER] %c --> %c :: oScanner ---> oPaser.\n :: -> Is token Valid? %s\n", src, oParser.read_token->value, oParser.read_token->valid? "YES" : "NO");

    /*Count as parsed token*/
    cTokens++;
    
    /*Storing*/
    oParser.previous_token = parsed_type;
    list_add(oParser.token_list, oParser.read_token);
    oParser.read_token = __ptoken_create__();
    
    return oParser.valid_expression;
}

bool __token_is_valid__(token_id_t new, token_id_t previous){

    /*
        Valid Expression:
        EXPRESSION -> ( EXPRESSION ) | OPERATION
        OPERATION -> OPERAND | OPERAND OPERATOR EXPRESSION
    */
    switch (new)
    {
        case VARIABLE:
        case OPERAND:
            return previous == OPERATOR || previous == LBRACKET;
            break;
        case OPERATOR:
            return previous == OPERAND || previous == VARIABLE || previous == RBRACKET ;
        case LBRACKET:
            return previous == OPERATOR;
        case RBRACKET:
            return (previous == OPERAND || previous == VARIABLE) && rBrackets <= lBrackets;
        default:
            return false;
    }
}