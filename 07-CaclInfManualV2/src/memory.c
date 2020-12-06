/* ---------------------------------------------------------------------------------

    memory.c

    Memory for variable for infix calculator.

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

    last modified: 12/06/2020
------------------------------------------------------------------------------------ */

#include "memory.h"

extern char* strdup(const char* _S);

// Store variable names
char* variable_names[100];

// Flags for if the variables have been set
int variable_set[100];

// Number of variables defined
int variable_counter = 0;

// Store values of the variables
int variable_values[100];

int 
add_variable(char* var_name){
	int x; // Index var
	
	/* Search for the variable and return its index if found */	
	for (x = 0; x<variable_counter; x++) {
		if (strcmp(var_name, variable_names[x]) == 0) {
				return x;
		}
	}

	/* Variable not found yet. */
	/* Define it and add it to the end of the array. */
	variable_counter++;
	variable_names[x] = strdup(var_name);
	return x;
}

int
set_variable(int index, int val){

	variable_values[index] = val;
	variable_set[index] = 1;
	
	return val;
}