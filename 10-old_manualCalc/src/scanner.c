/* ---------------------------------------------------------------------------------

    scanner.c

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

    last modified: 09/14/2020
------------------------------------------------------------------------------------ */

#include "scanner.h"

extern int tokens_g;

/*Valid operators*/
const char optor_list[] = {'+','-', '*'};

int buffer_clean(char * buffer){

    for (int i = 0; i < buffer_size; i++){
        buffer[i] = '\0';
    }
    
    return 0;
}


int scanner_syntax_check(scanner_t * this){

    // Pattern Matching.
    int first_element = *this->ibuffer;

    bool id, operator, integer;

    id          = char_is_variable(first_element);
    operator    = char_is_operator(first_element);
    integer     = char_is_number(first_element);

    // Expression starting with operator
    if( (operator && first_element != '-') || (first_element == '-' && this->ibuffer[1] != '\0') ){
        this->error = INVALID_OPERATOR;
        return 0;
    }
        
    for (int i = 1; this->ibuffer[i] != '\0'; i++){

            // Checking for non-decimal imputs
            if(char_is_number(this->ibuffer[i])){
                
                if(id){
                    this->error = NON_DECIMAL;
                    return 0;
                }

                operator = id = false;
                integer = true;
            }

            // Checking for non-decimal imputs
            if(char_is_variable(this->ibuffer[i])){
                if( id ||integer){
                    this->error = NON_DECIMAL;
                    return 0;
                }
                operator = integer = false;
                id = true;
            }

            // Checking for multiple operators
            if(char_is_operator(this->ibuffer[i])){
                if( operator ){
                    this->error = MULTIPLE_OPERATORS;
                    return 0;
                }

                id = integer = false;
                operator = true;
            }
    }

    return 1;
}


inline scanner_t scanner_create(){
    if(VERBOSE)
        puts("[DEBUG] :: [SCANNER] :: Creating scanner...");
    scanner_t new;
    new.tokens = 0;
    new.index = buffer_clean(new.ibuffer);
    new.flags.fst = new.flags.optor = true;
    new.flags.operand = new.flags.overwritten = false;
    new.error = NONE;
    if(VERBOSE)
        puts("[DEBUG] :: [SCANNER] :: Scanner created!...");
    return new;
}

int scanner_read(scanner_t * this){
    int c;
    if(VERBOSE)
        puts("[DEBUG] :: [SCANNER] :: Reading from stdin:");
    
    printf(" :: > ");
    while(  (c = getchar()) != '\n'){

        if(c == EOF)
            break;
        
        scanner_check_buffer(this);
        if( scanner_valid(this, c) != INVALID )
            this->ibuffer[this->index++] = c;

        if (this->flags.fst)
            this->flags.fst = false;
    }
    this->index = 0;
    if(VERBOSE)
        printf("[DEBUG] :: [SCANNER] :: Read << '%s' >> with <<'%d' tokens >>\n", this->ibuffer, this->tokens);

    return 0;
}

token_t scanner_valid(scanner_t * this, int c){
    
    if(VERBOSE)
        puts("[DEBUG] :: [SCANNER] :: Validating character ...");

    if(char_is_number(c)){
        if(this->flags.optor || this->flags.fst){
            this->tokens++;
            this->flags.optor   = false;
            this->flags.operand = true;
        }    
    return OPERAND;
    }

        
    else if (char_is_operator(c)){
        if(this->flags.operand || this->flags.fst){
            this->tokens++;
            this->flags.optor   = true;
            this->flags.operand = false;
        }
        return OPERATOR;
    }
    else if (char_is_variable(c)){
        if(this->flags.optor || this->flags.fst){
            this->tokens++;
            this->flags.optor = false;
            this->flags.operand = true;
        }
        return OPERANDV;
    }
    
    if(VERBOSE)
        puts("[DEBUG] :: [SCANNER] :: << Invalid character >> :: IGNORING...");

    return INVALID;
}

int scanner_check_buffer(scanner_t * this){

    if ( this->index >= (buffer_size - 2)){
        puts("[WARNING] :: [SACANNER] :: Buffer overflow :: Buffer will be overwritten");
        this->flags.overwritten = true;
        this->index = 0;
    } else if(this->flags.overwritten){
        puts("[WARNING] :: [SCANNER] :: Buffer is being overwritten");  
    }
    
    return this->index;
}

inline bool char_is_number(int c){
        
    if ( (c >= '0') && (c <= '9')){
        if(VERBOSE)
            printf("[DEBUG] :: [SCANNER] :: '%c' is a Number\n", c);
        return true;
    } 

    return false;
}

inline bool char_is_variable(int c){


    if( ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) ){
        if(VERBOSE)
            printf("[DEBUG] :: [SCANERR] :: '%c' is a Variable\n", c);
        return true;
    }

    return false;
}

inline bool char_is_operator(int c){

    for(int i = 0 ; i < operator_size; i++){
        if(optor_list[i] == c){
            if(VERBOSE)
                printf("[DEBUG] :: [SCANNER] :: '%c' is Operator\n", c);
            return true;
        }
    }    
   
    return false;
}

inline int scanner_GetNextToken(char * dest, scanner_t * this){

    if(VERBOSE){
        puts(":: ============================================================================ ::");
        printf("[DEBUG] :: [SCANNER] :: Getting Next Tokens :: ibuffer = '%s'.\n", this->ibuffer);
    }
    /* Understanding indexation:
     * 
     * Suppose a new token is detected we will have something like this
     *            0   |   1   |   2    |   ...   |   31  |
     *            7   |   +   |   \0   |   ...   |   \0  |
     *                  When iterated, will be INDEX = 1,
     *      And we need to get 7, and then +
     */

    int d_index = 0;
    for(int i = this->index;  this->ibuffer[i] != '\0'; d_index++, i++){
        
        dest[d_index] = this->ibuffer[i];
        if(char_is_operator(this->ibuffer[i])){

            if( i != this->index)
                dest[d_index] = '\0';

            break; 
        }
        this->index = i;
    }
    this->index++;

    if(char_is_operator(this->ibuffer[this->index-1])){
        while(char_is_operator(this->ibuffer[this->index])){
            dest[d_index] = this->ibuffer[this->index++];
        }
    }

    if(VERBOSE){
        printf("[DEBUG] :: [SCANNER] :: '%d' ---> '%c' :: index   ---> ibuffer.\n", this->index, this->ibuffer[this->index]);
        printf("[DEBUG] :: [SCANNER] :: '%s' ---> '%s' :: ibuffer ---> tbuffer.\n", this->ibuffer, dest);
    }

    return this->ibuffer[this->index] == '\0' ? false : true;
}

int __put_scanner_header__(){
            puts("\n:=-----------------::========::------------------=:");
            puts(" :: :: :: :: :: :: :: SYNTAXIS :: :: :: :: :: :: :: ");
    return  puts(":=-----------------::========::------------------=:\n");
}

int scanner_print(scanner_t * this){

    switch (this->error)
    {
    case NONE:
        if(tokens_g == 0)
            puts(" :: No syntax error - no valid input to analyze");
        else{
            __put_scanner_header__();
            printf(">> Expression :: '%s' :: Not errors were found\n",this->ibuffer);
        }
        break;
    case MULTIPLE_OPERATORS:
            __put_scanner_header__();
            printf(">> Expression :: '%s' :: ERROR :: Multiple operators concatenated :: Only the last one of them will be parsed\n",this->ibuffer);
        break;
    case INVALID_OPERATOR:
            __put_scanner_header__();
            printf(">> Expression :: '%s' :: ERROR :: Expression can't start with operator '%c' :: First element must be an operand\n",this->ibuffer, *this->ibuffer);
        break;
    default:
            __put_scanner_header__();
            printf(">> Expression :: '%s' :: ERROR :: Non-Decimal number\n",this->ibuffer);
        break;
    }
    return 0;
}