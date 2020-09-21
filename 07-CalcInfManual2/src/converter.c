/* ---------------------------------------------------------------------------------

    converter.c

    converts an infix strression to a reverse polish strression.

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

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, strRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    last modified: 09/20/2020
------------------------------------------------------------------------------------ */

#include "../inc/converter.h"

Stack_t * Stack_create(int size){ 
    Stack_t * this = (Stack_t*) malloc(sizeof(Stack_t)); 
  
    if (!this)  
        return NULL;
  
    this->top = -1; 
    this->capacity = size;
  
    this->array = (int*) malloc(this->capacity * sizeof(int)); 
  
    return this; 
}

inline int Stack_is_empty(Stack_t * this){ 
    return this->top == -1 ; 
}

inline char Stack_peek(Stack_t * this) { 
    return this->array[this->top]; 
}

inline char Stack_pop(Stack_t * this){ 
    return !Stack_is_empty(this)? this->array[this->top--] : ';' ; 
} 

inline void Stack_push(Stack_t * this, char op){ 
    this->array[++this->top] = op; 
} 
  
inline int __is_operand__(int c) { 
    return (c >= '0' && c <= '9'); 
} 
  
int __precedence__(char ch){ 
    switch (ch) 
    { 
    case '+': 
    case '-': 
        return 1; 
  
    case '*': 
    case '/': 
        return 2; 
  
    case '^': 
        return 3; 
    } 
    return -1; 
}

int infixToPostfix(char* str) 
{ 
    int i, k; 

    /*Size = strlen*/  
    Stack_t * stack = createStack(strlen(str));

    if(!stack)
        return -1;
  
    for (i = 0, k = -1; str[i]; ++i) 
    { 
        // If the scanned character is an operand, add it to output. 
        if (__is_operand__(str[i])) 
            str[++k] = str[i];
        
        else if (str[i] == '(') 
            Stack_push(stack, str[i]); 
          
        /*')' forces popping until '(' is found*/
        else if (str[i] == ')') 
        { 
            while (!Stack_is_rmpty(stack) && Stack_peek(stack) != '(') 
                str[++k] = Stack_pop(stack); 
            if (!Stack_is_empty(stack) && Stack_peek(stack) != '(') 
                return -1;              
            else
                Stack_pop(stack); 
        } 
        else // Case operator:
        { 
            while (!Stack_isEmpty(stack) && Stack_Prec(str[i]) <= __precedence__(peek(stack))) 
                str[++k] = Stack_pop(stack); 
            push(stack, str[i]); 
        } 
  
    } 
  
    // pop all the operators from the stack 
    while (!isEmpty(stack)) 
        str[++k] = pop(stack ); 
  
    str[++k] = '\0';
}