/* ---------------------------------------------------------------------------------

    solver.c

    solver for infix calculator.

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

    last modified: 09/20/2020
------------------------------------------------------------------------------------ */

#include "../inc/solver.h"

extern int tokens_g;

solver_t solver_create(){
    solver_t this;
    this.operand_buffer     = (int *) malloc(sizeof(int));
    this.operand_stack      = stack_create();
    this.operator_buffer    = (char *) malloc(sizeof(char));
    this.operator_stack     = stack_create();
    this.final_result       = 0;
    return this;
}

void solver_delete(solver_t * this){
    //Freeing buffers
    free(this->operand_buffer);
    free(this->operator_buffer);
    // Deleting stacks
    if(!stack_is_empty(this->operand_stack))
        stack_delete_and_delete_elements(this->operand_stack, free);
    else
        stack_delete(this->operand_stack);

    if(!stack_is_empty(this->operator_stack))    
        stack_delete_and_delete_elements(this->operator_stack, free);
    else
        stack_delete(this->operator_stack);
    
}

int solver_GetNextToken(solver_t * this, char * tok, token_t type){

    char token_operator;
    int token_integer;

    switch (type)
    {
    case OPERAND:
        token_integer = atoi(tok);
        this->operand_buffer = &token_integer;
        stack_push(this->operand_stack, this->operand_buffer);
        this->operand_buffer = malloc(sizeof(int));
        break;
    case OPERATOR:
        token_operator = *tok;
        if(token_operator == ')')
            solver_handle_parenthesis(this);
        else{
            this->operator_buffer = &token_operator;
            stack_push(this->operator_stack, this->operator_buffer);
            this->operator_buffer = malloc(sizeof(char));
        }
    default:
        break;
    }

    return 0;
}


int __solve__(solver_t * this, char * optor){
    int * a, *b;
    switch (*optor)
        {
        case '+':
            b = (int *) stack_pop(this->operand_stack);    
            a = (int *) stack_pop(this->operand_stack);
            *this->operand_buffer = *a + *b;
            free(a);
            free(b);
            stack_push(this->operand_stack, this->operand_buffer);
            this->operand_buffer = malloc(sizeof(int));
            break;
        case '*':
            b = (int *) stack_pop(this->operand_stack);    
            a = (int *) stack_pop(this->operand_stack);
            *this->operand_buffer = *a * *b;
            free(a);
            free(b);
            stack_push(this->operand_stack, this->operand_buffer);
            this->operand_buffer = malloc(sizeof(int));
            break;
        case '-':
            b = (int *) stack_pop(this->operand_stack);    
            a = (int *) stack_pop(this->operand_stack);
            *this->operand_buffer = *a + *b;
            free(a);
            free(b);
            stack_push(this->operand_stack, this->operand_buffer);
            this->operand_buffer = malloc(sizeof(int));
            break;
        default:
            break;
        }

    free(optor);
    return 0;
}

int solver_handle_parenthesis(solver_t * this){

    char  * optor; (char *) stack_pop(this->operator_stack);
    
    while(*optor != '('){
        __solve__(this, optor);
        optor = (char *) stack_pop(this->operator_stack);
    }

    // Optor should be '('
    if(optor)
        free(optor);

    return 0;
}

int solver_update(solver_t * this){

    char  * optor;

    while (!stack_is_empty(this->operator_stack))
    {
        optor = (char *) stack_pop(this->operator_stack);

        if(*optor == ')')
            solver_handle_parenthesis(this);
        else
            __solve__(this, optor);
    }
    
    if(optor){
        __solve__(this, optor);
    }

    this->operand_buffer = stack_pop(this->operand_stack);

    this->final_result = *this->operand_buffer;

    return this->final_result;
}

int solver_print(solver_t * this){
    if(tokens_g > 0){
        puts("\n:=-----------------::========::-----------------=:");
        puts(" :: :: :: :: :: :: :: RESULTS :: :: :: :: :: :: :: ");
        puts(":=-----------------::========::-----------------=:\n");
        printf(" :: :: > > %d", this->final_result);
    }
    return puts("\n- :: © 2020 TOMAS SANCHEZ - <tosanchez@est.frba.utn.edu.ar> | :: | All rights reserved :: -");
}