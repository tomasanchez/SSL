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

    last modified: 09/12/2020
------------------------------------------------------------------------------------ */

#include "scanner.h"

/*Valid operators*/
const char optor_list[] = {'+','-', '*'};

int buffer_clean(char * buffer){

    for (int i = 0; i < buffer_size; i++){
        buffer[i] = '\0';
    }
    
    return 0;
}


inline scanner_t scanner_create(){
    if(VERBOSE)
        puts("[DEBUG] Creating scanner...");
    scanner_t new;
    new.index = buffer_clean(new.ibuffer);
    new.flags.operand = new.flags.optor = new.flags.overwritten = false;
    if(VERBOSE)
        puts("[DEBUG] Scanner created!...");
    return new;
}

inline int scanner_read(scanner_t * this){
    int c;
    if(VERBOSE)
        puts("[DEBUG] Reading from stdin:");
    
    printf(" > ");
    c = getchar();
    // Consuming '\n'
    getchar();
    if(VERBOSE)
        printf("[DEBUG] Has been read: %c / %d\n", c, c);

    
    return scanner_is_valid(this, c);
}

inline token_t scanner_is_valid(scanner_t * this, int c){
    
    if(VERBOSE)
        puts("[DEBUG] Validating character ...");

    if(scanner_is_number(this, c))
        return OPERAND;
    else if (scanner_is_operator(this, c))
        return OPERATOR;
    else if (scanner_is_variable(this, c))
        return OPERANDV;
    else if (c != '\n')
        return EOL;
    else return INVALID;
}

int scanner_check_buffer(scanner_t * this){

    if ( this->index >= (buffer_size - 2)){
        puts("[WARNING] Buffer overflow: buffer will be overwritten");
        this->flags.overwritten = true;
        this->index = 0;
    } else if(this->flags.overwritten){
        puts("[WARNING] Buffer is being overwritten");  
    }
    
    return this->index;
}

bool scanner_is_number(scanner_t * this, int c){

    this->flags.operand = false;

    scanner_check_buffer(this);
        
    if ( (c >= '0') && (c <= '9')){
        if(VERBOSE)
            printf("[DEBUG] %c has validated as a Number\n", c);

        this->flags.operand = true;
        this->ibuffer[this->index++] = c;
    } 

    return this->flags.operand;
}

bool scanner_is_variable(scanner_t * this, int c){

    this->flags.operand = false;

    if( ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) ){
        if(VERBOSE)
            printf("[DEBUG] %c has validated as a Variable\n", c);
        this->flags.operand = true;
        this->ibuffer[this->index++] = c;
    }

    return this->flags.operand;
}

bool scanner_is_operator(scanner_t * this, int c){

    scanner_check_buffer(this);

    this->flags.optor = false;

    for(int i = 0 ; i < operator_size; i++){
        if(optor_list[i] == c){
            if(VERBOSE)
                printf("[DEBUG] %c has validated as a Operator\n", c);
            this->flags.optor = true;
            this->ibuffer[this->index] = c;
        }
    }    
   
    return this->flags.operand;
}

inline int scanner_GetNextToken(char * dest, scanner_t * this){

    /* Explanation Index - 2:
     * 
     * Suppose a new token is detected we will have something like this
     *            0   |   1   |   2    |   ...   |   31  |
     *            7   |   +   |   \0   |   ...   |   \0  |
     *                  The thing is that INDEX = 2,
     *      And we need to get 7, and then +,  so we also need to save the element in INDEX - 1
     */

    char last_token = this->ibuffer[this->index-1];
    strncpy(dest, this->ibuffer, this->index - 2);

    this->index = buffer_clean(this->ibuffer);

    this->ibuffer[this->index++] = last_token;

    return 0;
}