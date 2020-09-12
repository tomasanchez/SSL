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

    last modified: 09/11/2020
------------------------------------------------------------------------------------ */

#include "inc/scanner.h"

scanner_t scanner_create(){
    scanner_t new;
    new.index = 0;
    new.ibuffer[buffer_size] = '\0';
    new.flags.operand = new.flags.optor = new.flags.overwritten = false;
    return new;
}



int scanner_read(scanner_t * this){
    int c = getchar();
    return scanner_is_valid(this, c);
}

inline token_t scanner_is_valid(scanner_t * this, int c){

    if(scanner_is_number(this, c))
        return OPERAND;
    else if (scanner_is_operator(this, c))
        return OPERATOR;
    else
        return INVALID;
}

inline int scanner_check_buffer(scanner_t * this){

    if ( this->index > (buffer_size - 1)){
        puts("[WARNING] Buffer overflow: buffer will be overwritten");
        this->flags.overwritten = true;
        this->index = 0;
    } else if(this->flags.overwritten){
        puts("[WARNING] Buffer is being overwritten");  
    }
    
    return this->index;
}

inline bool scanner_is_number(scanner_t * this, int c){

    this->flags.operand = false;

    scanner_check_buffer(this);
        
    if ( (c >= 0) && (c <= 9)){

        this->flags.operand = true;
        snprintf(this->ibuffer, 1,"%d", c);
        this->index++;

    } else if((c >= 'a') && (c <= 'z') || (c >= 'A') && (c <= 'Z')){
        this->flags.operand = true;
        this->ibuffer[this->index++] = c;
    }

    return this->flags.operand;
}

inline bool scanner_is_operator(scanner_t * this, int c){

    scanner_check_buffer(this);

    this->flags.optor = false;

    for(int i = 0 ; i < operator_size; i++){
        if(optor_list[i] == c){
            this->flags.optor = true;
            this->ibuffer[this->index] = c;
        }
    }    
   
    return this->flags.operand;
}
