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

    last modified: 01/06/2020
------------------------------------------------------------------------------------ */

#include "String.h"
#include <assert.h>

int main(void){

    char* test = "hello, world!";
    char* test_2 = "";
    char* test_3 = " new world";

    /*Testing if can get length and not empty*/
    assert(getLength(test) == 13lu);
    assert(isEmpty(test_2));

    /* Testing isEqual  */
    assert(!isEqual(test, test_2));
    assert(isEqual(test, test));

    /*Testing power works correctly*/
    test = power(test, 2);
    assert(isEqual(test,"hello, world!hello, world!"));
    puts(test);
    string_destroy(test);

    /*Testing power, with negatives, should print "\n"*/
    test = power(test,-10);
    assert(isEmpty(test));
    puts(test);

    /*Testing append*/

    append(&test, test_3);
    puts(test);
    assert(isEqual(test," new world"));

    string_destroy(test);

    return 0;
}