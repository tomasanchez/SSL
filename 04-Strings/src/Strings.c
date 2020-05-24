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

    last modified: 05/23/2020
------------------------------------------------------------------------------------ */

#include "String.h"

size_t getLength(const char* str){
    return *str != 0 ? getLength(str+1) + 1 : 0;
}

bool isEmpty(const char* str){
    return getLength(str) == 0 ? true : false;
}

char* power (char* src, int n){

    //pattern matching
    if(n<=0)
    return "";

    char* dest = malloc((getLength(src)+1)*n);

    for (int i = 0; i < n; i++){
        append(dest, src);
    }

    return dest;
}

void append (char* dest, char* src){

    int destend = getLength(dest);
    int srcend = getLength(src);

    for (int i = 0; i < srcend ; i++){
        dest[destend+i] = src[i];
    }
}
