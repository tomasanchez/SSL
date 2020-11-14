/* ---------------------------------------------------------------------------------

    solver.c

    solver for infix automatic-scanner calculator.

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

    last modified: 11/13/2020
------------------------------------------------------------------------------------ */

#include "../inc/solver.h"

/*Global Token counter*/
extern int totalTokens_g;

/*Local Solver*/
solver_t * oSolver;

/*Private Functions*/

/*Solves '(expression)' operations stacks*/
int __handle_parenthesis__();

/*Solve math expression a (operator) b, operator in {+,-,*}*/
int __solve__(int a, int b, char operator);

/*Determines precedence of operators*/
int __precedence__(int);

/*Creates a tok with the passed token and its type*/
token_t * __token_create__(int token, token_id_t type);

/*
===============================================================================================================================
============================================= SOLVER ALLOCATIONS  =============================================================
===============================================================================================================================
*/

int solver_create(){
    if(VERBOSE && SOLVER)
        puts("[DEBUG] :: [SOLVER] :: Creating solver...");
    /*Reserving solver size*/
    oSolver = malloc(sizeof(solver_t));    
    /*Creating dynamic elements*/
    oSolver->token = NULL;
    oSolver->output_queue = queue_create();
    oSolver->operator_stack = stack_create();
    oSolver->final_result = 0;

    if(VERBOSE && SOLVER)
        puts("[DEBUG] :: [SOLVER] :: Solver created!");

    return OK;
}

int solver_delete(){


    //Deleting current token
    if(oSolver->token != NULL)
        free(oSolver->token);
    
    // Elements should have been removed, but just in case, we verify this
    if(!queue_is_empty(oSolver->output_queue))
        queue_destroy_and_destroy_elements(oSolver->output_queue, free);
    else
        queue_destroy(oSolver->output_queue);

    /* The same applies to the stack */
    if(!stack_is_empty(oSolver->operator_stack))    
        stack_delete_and_delete_elements(oSolver->operator_stack, free);
    else
        stack_delete(oSolver->operator_stack);

    free(oSolver);

    return OK;
}

/*
===============================================================================================================================
============================================= TOKENS HANDLING =================================================================
===============================================================================================================================
*/

token_t * __token_create__(int token, token_id_t type){
    token_t * new = malloc(sizeof(token_t));
    new->token = token;
    new->type = type;
    return new;
}

int solver_GetNextToken(int tok, token_id_t type){
    /*Tok for operators handling*/
    token_t * previous = NULL;

    if(VERBOSE && SOLVER)
        printf("[DEBUG] :: [SOLVER] :: Evaluating '%d'\n", tok);

    switch (type)
    {
    case OPERAND:
    case VARIABLE:
        /*Being operands, only need to be enqueued, however we ensure they have the correct value, by parsing to int*/
        // NOTE: this method parsed variables to 0.
        oSolver->token = __token_create__(tok, OPERAND);
        if(VERBOSE && SOLVER)
            printf("[DEBUG] :: [SOLVER] :: '%d' -> '%d' :: Parser -> outputQueue\n", tok, oSolver->token->token);
        queue_push(oSolver->output_queue, oSolver->token);
        return OK;
    case RBRACKET:
        /*As ')' is not needed, we do not allocate memory for it. Is not pushed but solved*/
        if(VERBOSE && SOLVER)
            puts("[DEBUG] :: [SOLVER] :: Handling Parenthesis...");
        /*All operators will moved Stack -> output Queue, until the first ')' is found*/
        __handle_parenthesis__();
        return OK;
    case LBRACKET:
        /*No break, as '(' does need to be pushed*/
    case OPERATOR:
        
        /*We create a new tok, just to be pushed*/
        oSolver->token = __token_create__(tok, type);

        /*Pattern matching, '(' should be pushed
          But also, if the stack was empty for any reason, we verify this before popping from it*/
        if(oSolver->token->token == '('|| stack_is_empty(oSolver->operator_stack)){
            stack_push(oSolver->operator_stack, oSolver->token);
            return OK;  
        }

        previous = stack_pop(oSolver->operator_stack);

        /*If previous has higher precende, no changes are needed*/
        if(__precedence__(previous->token) < __precedence__(oSolver->token->token)){

            if(VERBOSE && SOLVER){
                printf("[DEBUG] :: [SOLVER] :: Precendence of '%c' <  Precende of '%c'\n", previous->token, oSolver->token->token);
                printf("[DEBUG] :: [SOLVER] :: Stack::['%c'|'%c']\n", previous->token, oSolver->token->token);
            }
            stack_push(oSolver->operator_stack,previous);
            stack_push(oSolver->operator_stack, oSolver->token);
        }else{
            if(VERBOSE && SOLVER){
                printf("[DEBUG] :: [SOLVER] :: Precendence of '%c' >  Precende of '%c'\n", previous->token, oSolver->token->token);
                printf("[DEBUG] :: [SOLVER] :: Stack ::['%c']\n", oSolver->token->token);
                printf("[DEBUG] :: [SOLVER] :: Queue :: <<'%c'>>\n", previous->token);
            }
            /*Otherwise, we move the  previous to the queue, and stack the new one*/
            stack_push(oSolver->operator_stack, oSolver->token);
            queue_push(oSolver->output_queue, previous);
        }
    default:
        break;
    }
    return OK;
}


/*
===============================================================================================================================
============================================= SOLVING HANDLING =================================================================
===============================================================================================================================
*/

int __precedence__(int op){

    /*Lower number means higher precedence*/
    switch (op) 
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

int __solve__(int a, int b, char optor){

    if(VERBOSE && SOLVER)
            puts("[DEBUG] :: [SOLVER] :: Solving...");

    /*Solves for '+', '-', and '*' */
    switch (optor)
        {
        case '+':
            if(VERBOSE && SOLVER)
                printf("[DEBUG] :: [SOLVER] :: Solving '%d+%d'...\n", a, b);

            return a+b;
            break;
        case '*':
            if(VERBOSE && SOLVER)
                printf("[DEBUG] :: [SOLVER] :: Solving '%d' * '%d'...\n", a, b);
            return a*b;
            break;
        case '-':
            if(VERBOSE && SOLVER)
                printf("[DEBUG] :: [SOLVER] :: Solving '%d' - '%d'...\n", a, b);
            return a-b;
            break;
        default:
            if(VERBOSE && SOLVER)
                printf("[DEBUG] :: [SOLVER] :: '%c' is not an arithmetic operator\n", optor);
            return -1;
            break;
        }

    return 0;
}

int __handle_parenthesis__(){

    /*Pops operator*/
    oSolver->token = (token_t *) stack_pop(oSolver->operator_stack);

    if(VERBOSE && SOLVER)
        printf("[DEBUG] :: [SOLVER] :: [PARENTHESIS_HANDLER] :: First operator is <'%c'>\n", oSolver->token->token );
    /*Until the first LBRACKET is found, all operators will be moved*/
    while(oSolver->token->token != '('){
        /*Moving all operators to output queue*/
        queue_push(oSolver->output_queue, oSolver->token);
        if(VERBOSE && SOLVER)
            printf("[DEBUG] :: [SOLVER] :: [PARENTHESIS_HANDLER] :: Moved <'%c'> :: Stack -> Queue\n", oSolver->token->token);
        oSolver->token = (token_t *) stack_pop(oSolver->operator_stack);
    }

    if(VERBOSE && SOLVER)
        puts("[DEBUG] :: [SOLVER] :: [PARENTHESIS_HANDLER] :: Parenthesis was solved");

    // token should be '(', unused so must be freed
    free(oSolver->token);
    
    oSolver->token = NULL;

    return OK;
}

int solver_update(){

    /*First operand*/
    token_t  * a = NULL;
    /*Second operand*/
    token_t  * b = NULL;

    if(VERBOSE && SOLVER)
        puts("[DEBUG] :: [SOLVER] :: [UPDATE] :: Calculating...");

    /*First, we need to make sure there are no operators remaining in the stack, if there are, they are moved to the output queue*/
    while(!stack_is_empty(oSolver->operator_stack)){
        if(VERBOSE && SOLVER)
            puts("[DEBUG] :: [SOLVER] :: [UPDATE] :: Emptying stack...");
        oSolver->token = (token_t *) stack_pop(oSolver->operator_stack);
        queue_push(oSolver->output_queue, oSolver->token);
    }

    /*Procedeing to solve the output queue*/
    while (!queue_is_empty(oSolver->output_queue))
    {
        oSolver->token = (token_t *) queue_pop(oSolver->output_queue);

        /*As we need operators, operands are pushed to stack*/
        if(oSolver->token->type == OPERAND){
            stack_push(oSolver->operator_stack, oSolver->token);
        }
        else{
            /*Getting and operator, we proceed to solve the expressions a (operator) b*/

            /* As stack is LIFO, b should pop first*/
            if(stack_size(oSolver->operator_stack) >= 2){
                b = (token_t *) stack_pop(oSolver->operator_stack);
                a = (token_t *) stack_pop(oSolver->operator_stack);
            }
            /*Overwritting operator, now is an operand*/
            oSolver->token->token = __solve__(a->token, b->token, oSolver->token->token);
            oSolver->token->type = OPERAND;

            /*Putting result again in the stack*/
            stack_push(oSolver->operator_stack, oSolver->token);

            /*As tokens were consumed, there is no need of them*/
            free(a);
            free(b);
        }        
    }
    if(VERBOSE && SOLVER)
        puts("[DEBUG] :: [SOLVER] :: Everything was solved");

    if(totalTokens_g > 0){
        oSolver->token = stack_pop(oSolver->operator_stack);
        /*Last token should have the final result*/
        oSolver->final_result =    oSolver->token->token;
    }
    return oSolver->final_result;
}

int solver_print(){
    /*This is only for aesthetcis, we cheeck if there were tokens*/
    if(totalTokens_g > 0){
        puts("\n:=-----------------::========::-----------------=:");
        puts(" :: :: :: :: :: :: :: RESULTS :: :: :: :: :: :: :: ");
        puts(":=-----------------::========::-----------------=:\n");
        printf(" :: :: > > %d\n", oSolver->final_result);
    }
    return OK;
}