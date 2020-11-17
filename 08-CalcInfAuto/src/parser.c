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
parser_t * oParser;
unsigned int cTokens;
unsigned int rBrackets = 0;
unsigned int lBrackets = 0;

/*Private Functions*/

/*  Private Function :: writes a token to stdout*/
static void __print_token__(void *);

/*  Private Function :: wirtes unique token to stdout*/
static void __print_one__(void * element);

/*  Private Function :: Validates a token*/
static bool __token_is_valid__(token_id_t, token_id_t);

/*  Private Function :: Creates an element for a list*/
static ptoken_t * __ptoken_create__(void);

/* Private Function :: Prints all token parsed*/
static int __print_results__();

/* Private Function :: Tells if parse has error*/
static bool __has_error__();

/*
===============================================================================================================================
============================================= PARSER ALLOCATIONS  =============================================================
===============================================================================================================================
*/

int parser_create(){

    oParser = malloc(sizeof(parser_t));

    oParser->token_list = list_create();
    oParser->read_token = __ptoken_create__();
    oParser->previous_token = OPERATOR;
    oParser->valid_expression = true;
    
    return solver_create();;
}

int parser_delete(){
    free(oParser->read_token);
    /*As no items are removed, elements need to be deleted with the list*/
    list_destroy_and_destroy_elements(oParser->token_list, free);

    return solver_delete();
}


static ptoken_t * __ptoken_create__(){
    ptoken_t * new = malloc(sizeof(ptoken_t));
    new->value = '+';
    new->type = OPERATOR;
    new->valid = false;
    return new;
}

inline int parser_parse(){
    return yylex();
}

int parser_update(){

    __print_results__();
    if(! __has_error__()){
        solver_update();
        solver_print();
    }
    
    return OK;
}

/*
===============================================================================================================================
============================================= TOKENS HANDLING =================================================================
===============================================================================================================================
*/


bool parser_GetNextToken(int src, token_id_t parsed_type){

    oParser->read_token->value = src;
    oParser->read_token->type = parsed_type;

    if(parsed_type == LBRACKET)
        ++lBrackets;

    if(parsed_type == RBRACKET)
        ++rBrackets;

    oParser->read_token->valid = __token_is_valid__(parsed_type, oParser->previous_token);

    oParser->valid_expression = oParser->valid_expression && oParser->read_token->valid;

    if(VERBOSE && PARSER && parsed_type == OPERAND)
        printf("[DEBUG] :: [PARSER] %d --> %d :: oScanner ---> oPaser.\n :: -> Is token Valid? %s\n", src, oParser->read_token->value, oParser->read_token->valid? "YES" : "NO");
    
    if(VERBOSE && PARSER && parsed_type != OPERAND)
        printf("[DEBUG] :: [PARSER] %c --> %c :: oScanner ---> oPaser.\n :: -> Is token Valid? %s\n", src, oParser->read_token->value, oParser->read_token->valid? "YES" : "NO");

    /*Count as parsed token*/
    cTokens++;
    
    /*Storing*/
    oParser->previous_token = parsed_type;
    list_add(oParser->token_list, oParser->read_token);
    oParser->read_token = __ptoken_create__();
    
    return oParser->valid_expression;
}

static bool __token_is_valid__(token_id_t new, token_id_t previous){

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
            return previous == OPERATOR || previous == LBRACKET;
        case RBRACKET:
            return (previous == OPERAND || previous == VARIABLE || previous == RBRACKET) && rBrackets <= lBrackets;
        default:
            return false;
    }
}

static inline bool __has_error__(){
    return !oParser->valid_expression;
}

static int __print_results__(){

    oParser->valid_expression = oParser->valid_expression && lBrackets == rBrackets;

    if(VERBOSE && PARSER)
        puts("[DEBUG] Printing results ...\n");

    if( totalTokens_g > 0){
        puts("\n:=-----------------::========::-----------------=:");
        puts(" :: :: :: :: :: :: :: PARSER :: :: :: :: :: :: :: ");
        puts(":=-----------------::========::-----------------=:\n");
        if( totalTokens_g > 1)
            list_iterate(oParser->token_list, __print_token__);
        else
            list_iterate(oParser->token_list, __print_one__);
        printf("\n:== Expression is %s ==:\n", oParser->valid_expression? "VALID" : "INVALID");
    } else
        puts("\n :: No valid character has been entered :: ");
    

    
    return OK;
}

static void __print_one__(void * element){

    ptoken_t * this_token = (ptoken_t *) element;

    if(this_token->type != OPERAND)
        printf(">> PARSED :: Invalid expression :: '%c' ::\n", this_token->value);
    else
        printf(">> PARSED :: [VALID] :: '%d' :: Operand.\n", this_token->value);
}

static void __print_token__(void * element){

    ptoken_t * this_token = (ptoken_t *) element;

    if(this_token->valid){
        if(this_token->type == OPERAND)
            printf(">> PARSED :: [ VALID ] :: '%d'\t:: OPERAND.\n", this_token->value);
        else
            printf(">> PARSED :: [ VALID ] :: '%c'\t:: OPERATOR.\n", this_token->value);
    } else{
        if(this_token->type == OPERAND)
            printf(">> PARSED :: [INVALID] :: '%d'\t:: OPERAND.\n", this_token->value);
        else
            printf(">> PARSED :: [INVALID] :: '%c'\t:: OPERATOR.\n", this_token->value);
    }
}