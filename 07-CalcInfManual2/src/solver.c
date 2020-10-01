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

tok_t * __tok_create__(int token, token_t type){
    tok_t * this = malloc(sizeof(tok_t));
    this->token = token;
    this->type = type;
    return this;
}

solver_t solver_create(){
    if(VERBOSE && SOLVER)
        puts("[DEBUG] :: [SOLVER] :: Creating solver...");
    solver_t this;
    this.token = NULL;
    this.output_queue = queue_create();
    this.operator_stack = stack_create();

    if(VERBOSE && SOLVER)
        puts("[DEBUG] :: [SOLVER] :: Solver created!");

    return this;
}

void solver_delete(solver_t * this){
    //Freeing buffers
    // Deleting stacks
    if(!queue_is_empty(this->output_queue))
        queue_destroy_and_destroy_elements(this->output_queue, free);
    else
        queue_destroy(this->output_queue);

    if(!stack_is_empty(this->operator_stack))    
        stack_delete_and_delete_elements(this->operator_stack, free);
    else
        stack_delete(this->operator_stack);
    
}

int solver_GetNextToken(solver_t * this, char * tok, token_t type){
    tok_t * previous = NULL;
    if(VERBOSE && SOLVER)
        printf("[DEBUG] :: [SOLVER] :: Evaluating '%s'\n", tok);

    switch (type)
    {
    case OPERAND:
        this->token = __tok_create__(atoi(tok), OPERAND);
        if(VERBOSE && SOLVER)
            printf("[DEBUG] :: [SOLVER] :: '%d' -> '%d' :: tBuffer -> outputQueue\n", atoi(tok), this->token->token);
        queue_push(this->output_queue, this->token);
        break;
    case PARENTHESIS:
    case OPERATOR:
        this->token = __tok_create__(*tok, type);

        /*Parenthesis treatment*/
        if(*tok == ')'){
            if(VERBOSE && SOLVER)
                puts("[DEBUG] :: [SOLVER] :: Handling Parenthesis...");
                /* Stack -> output Queue*/
            solver_handle_parenthesis(this);
            return 0;
        }

        previous = stack_pop(this->operator_stack);
        
        if(__precedence__(previous->token) < __precedence__(this->token->token)){

            if(VERBOSE && SOLVER)
                printf("[DEBUG] :: [SOLVER] :: Precendence of '%c' <  Precende of '%c'\n", previous->token, this->token->token);

            stack_push(this->operator_stack,previous);
            stack_push(this->operator_stack, this->token);
        }else{
            if(VERBOSE && SOLVER)
                printf("[DEBUG] :: [SOLVER] :: Precendence of '%c' >  Precende of '%c'\n", previous->token, this->token->token);
            
            stack_push(this->operator_stack,previous);
            queue_push(this->output_queue, this->token);
        }
    default:
        break;
    }

    return 0;
}


int __solve__(int a, int b, char optor){

    if(VERBOSE && SOLVER)
            puts("[DEBUG] :: [SOLVER] :: Solving...");
    
    switch (optor)
        {
        case '+':
            if(VERBOSE && SOLVER)
                printf("[DEBUG] :: [SOLVER] :: Solving '%d+%d'...\n", a, b);

            return a+b;
            break;
        case '*':
            if(VERBOSE && SOLVER)
                printf("[DEBUG] :: [SOLVER] :: Solving '%d' * '%d'...\n", *a, *b);
            return a*b;
            break;
        case '-':
            if(VERBOSE && SOLVER)
                printf("[DEBUG] :: [SOLVER] :: Solving '%d' - '%d'...\n", *a, *b);
            return a-b;
            break;
        default:
            if(VERBOSE && SOLVER)
                printf("[DEBUG] :: [SOLVER] :: '%c' is not an arithmetic operator\n", *optor);
            return -1;
            break;
        }

    return 0;
}

int solver_handle_parenthesis(solver_t * this){

    this->token = (tok_t *) stack_pop(this->operator_stack);

    if(VERBOSE && SOLVER)
        printf("[DEBUG] :: [SOLVER] :: [PARENTHESIS_HANDLER] :: First operator is <'%c'>\n", this->token->token );
    
    while(this->token->token != '('){
        /*Moving all operators to output queue*/
        queue_push(this->output_queue, this->token);
        if(VERBOSE && SOLVER)
            printf("[DEBUG] :: [SOLVER] :: [PARENTHESIS_HANDLER] :: Moved <'%c'> :: Stack -> Queue\n", this->token->token);
        this->token = (tok_t *) stack_pop(this->operator_stack);
    }

    if(VERBOSE && SOLVER)
        puts("[DEBUG] :: [SOLVER] :: [PARENTHESIS_HANDLER] :: Parenthesis was solved");

    // Optor should be '('
    if(this->token)
        free(this->token);
    
    this->token = NULL;

    return 0;
}

int solver_update(solver_t * this){

    tok_t operator;

    while(!stack_is_empty(this->operator_stack)){
        this->token = (tok_t *) stack_pop(this->operator_stack);
        queue_push(this->output_queue, this->token);
    }


    while (!queue_is_empty(this->output_queue))
    {
        this->token = queue_pop(this->output_queue);

        if(this->token->type == OPERAND){
        }

        if(*optor == ')')
            solver_handle_parenthesis(this);
        else
            __solve__(this, optor);
    }
    if(VERBOSE && SOLVER)
        puts("[DEBUG] :: [SOLVER] :: Everything was solved");

    //if(optor){
     //   __solve__(this, optor);
    //}
    if(tokens_g > 0)
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
