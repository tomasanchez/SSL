/* ---------------------------------------------------------------------------------

    Strings.c

    Own string library

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

    last modified: 06/01/2020
------------------------------------------------------------------------------------ */

#include "String.h"

inline char * string_create(){
    char * new_str = malloc(sizeof(char));
    *new_str = '\0';
    return new_str;
}

inline void string_destroy(char * str){
    free(str);
}

size_t getLength(const char* str){
    return *str == '\0' ? 0lu : getLength(str+1) + 1lu;
}

inline bool isEmpty(const char* str){
    return *str == '\0';
}

char* power (char* src, int n){

    //pattern matching
    if(n<=0)
        return "";

    char* dest = NULL;
    dest = string_create();
    
    for (int i = 0; i < n; i++)
        append(&dest, src);

    return dest;
}

void append (char** dest, char* src){
    
    size_t dest_length = getLength(*dest);
    size_t src_length = getLength(src);

    *dest = realloc(*dest, dest_length + src_length + 1);
    char * aux = NULL;
    aux = *dest;

    //Avoiding jumps on uninitialized values
    for(size_t i = dest_length; i<= src_length; i++)
        aux[i] = '\0';


    for (size_t i = 0; i <= src_length ; i++){
        aux[dest_length + i] = src[i];
    }
}

bool isEqual(const char* this_str,const char* that_str){

    size_t this_str_len =   getLength(this_str);

    //pattern matching
    if (    this_str_len != getLength (that_str))
        return false;

    //check for every c : str
    for (size_t i = 0; i < this_str_len; i++ ){

        if (this_str[i] != that_str[i])
            return false;
    }

    return true;    
}