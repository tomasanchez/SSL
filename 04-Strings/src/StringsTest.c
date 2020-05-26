/* ---------------------------------------------------------------------------------

    StringsTest.c

    Testing strings with assert
    
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
#include <assert.h>

int main(void){

    char* test = "abcdefghijklmnopqrstuvwxyZ";

    /*Testing if can get length and not empty*/
    assert(getLength(test));
    assert(!isEmpty(test));

    /*Testing power works correctly*/
    test = power(test, 10);
    assert(test);
    puts(test);

    puts("Testing Negatives, should return empty string");
    test = power(test,-10);
    assert(test);
    puts(test);

    free(test);
    return 0;
}