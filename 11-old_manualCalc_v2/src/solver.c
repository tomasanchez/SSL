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
    /*Creating dynamic elements*/
    this.token = NULL;
    this.output_queue = queue_create();
    this.operator_stack = stack_create();

    if(VERBOSE && SOLVER)
        puts("[DEBUG] :: [SOLVER] :: Solver created!");

    return this;
}

void solver_delete(solver_t * this){
    //Deleting current token
    free(this->token);
    // Elements should have been removed, but just in case, we verify this
    if(!queue_is_empty(this->output_queue))
        queue_destroy_and_destroy_elements(this->output_queue, free);
    else
        queue_destroy(this->output_queue);

    /* The same applies to the stack */
    if(!stack_is_empty(this->operator_stack))    
        stack_delete_and_delete_elements(this->operator_stack, free);
    else
        stack_delete(this->operator_stack);
    
}

int solver_GetNextToken(solver_t * this, char * tok, token_t type){
    /*Tok for operators handling*/
    tok_t * previous = NULL;

    if(VERBOSE && SOLVER)
        printf("[DEBUG] :: [SOLVER] :: Evaluating '%s'\n", tok);

    switch (type)
    {
    case OPERAND:
    case OPERANDV:
        /*Being operands, only need to be enqueued, however we ensure they have the correct value, by parsing to int*/
        // NOTE: this method parsed variables to 0.
        this->token = __tok_create__(atoi(tok), OPERAND);
        if(VERBOSE && SOLVER)
            printf("[DEBUG] :: [SOLVER] :: '%d' -> '%d' :: tBuffer -> outputQueue\n", atoi(tok), this->token->token);
        queue_push(this->output_queue, this->token);
        break;
    case PARENTHESIS:
        /*No break, as '(' does need to be pushed*/
    case OPERATOR:
        /*As ')' is not needed, we do not allocate memory for it*/
        if(*tok == ')'){
            if(VERBOSE && SOLVER)
                puts("[DEBUG] :: [SOLVER] :: Handling Parenthesis...");
            /*All operators will moved Stack -> output Queue, until the first ')' is found*/
            solver_handle_parenthesis(this);
            return 0;
        }
        /*We create a new tok, just to be pushed*/
        this->token = __tok_create__(*tok, type);

        /*Pattern matching, '(' should be pushed*/
        /*But also, if the stack was empty for any reason, we verify this before popping from it*/
        if(this->token->token == '('|| stack_is_empty(this->operator_stack)){
            stack_push(this->operator_stack, this->token);
            return 0;  
        }

        previous = stack_pop(this->operator_stack);

        /*If previous has higher precende, no changes are needed*/
        if(__precedence__(previous->token) < __precedence__(this->token->token)){

            if(VERBOSE && SOLVER){
                printf("[DEBUG] :: [SOLVER] :: Precendence of '%c' <  Precende of '%c'\n", previous->token, this->token->token);
                printf("[DEBUG] :: [SOLVER] :: Stack::['%c'|'%c']\n", previous->token, this->token->token);
            }
            stack_push(this->operator_stack,previous);
            stack_push(this->operator_stack, this->token);
        }else{
            if(VERBOSE && SOLVER){
                printf("[DEBUG] :: [SOLVER] :: Precendence of '%c' >  Precende of '%c'\n", previous->token, this->token->token);
                printf("[DEBUG] :: [SOLVER] :: Stack ::['%c']\n", this->token->token);
                printf("[DEBUG] :: [SOLVER] :: Queue :: <<'%c'>>\n", previous->token);
            }
            /*Otherwise, we move the  previous to the queue, and stack the new one*/
            stack_push(this->operator_stack, this->token);
            queue_push(this->output_queue, previous);
        }
    default:
        break;
    }
    return 0;
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

int solver_handle_parenthesis(solver_t * this){

    /*Pops operator*/
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

    // token should be '(', unused
    free(this->token);
    
    this->token = NULL;

    return 0;
}

int solver_update(solver_t * this){

    /*First operand*/
    tok_t  * a = NULL;
    /*Second operand*/
    tok_t  * b = NULL;

    if(VERBOSE && SOLVER)
        puts("[DEBUG] :: [SOLVER] :: [UPDATE] :: Calculating...");

    /*First, we need to make sure there are no operators remaining in the stack, if there are, they are moved to the output queue*/
    while(!stack_is_empty(this->operator_stack)){
        if(VERBOSE && SOLVER)
            puts("[DEBUG] :: [SOLVER] :: [UPDATE] :: Emptying stack...");
        this->token = (tok_t *) stack_pop(this->operator_stack);
        queue_push(this->output_queue, this->token);
    }

    /*Procedeing to solve the output queue*/
    while (!queue_is_empty(this->output_queue))
    {
        this->token = (tok_t *) queue_pop(this->output_queue);

        /*As we need operators, operands are pushed to stack*/
        if(this->token->type == OPERAND){
            stack_push(this->operator_stack, this->token);
        }
        else{
            /*Getting and operator, we proceed to solve the expressions a (operator) b*/

            /* As stack is LIFO, b should pop first*/
            if(stack_size(this->operator_stack) >= 2){
                b = (tok_t *) stack_pop(this->operator_stack);
                a = (tok_t *) stack_pop(this->operator_stack);
            }
            /*Overwritting operator, now is an operand*/
            this->token->token = __solve__(a->token, b->token, this->token->token);
            this->token->type = OPERAND;

            /*Putting result again in the stack*/
            stack_push(this->operator_stack, this->token);

            /*As tokens were consumed, there is no need of them*/
            free(a);
            free(b);
        }        
    }
    if(VERBOSE && SOLVER)
        puts("[DEBUG] :: [SOLVER] :: Everything was solved");

    if(tokens_g > 0)
        this->token = stack_pop(this->operator_stack);

    /*Last token should have the final result*/
    this->final_result =    this->token->token;

    return this->final_result;
}

int solver_print(solver_t * this){
    /*This is only for aesthetcis, we cheeck if there were tokens*/
    if(tokens_g > 0){
        puts("\n:=-----------------::========::-----------------=:");
        puts(" :: :: :: :: :: :: :: RESULTS :: :: :: :: :: :: :: ");
        puts(":=-----------------::========::-----------------=:\n");
        printf(" :: :: > > %d\n", this->final_result);
    }
    return 0;
}

int __precedence__(char ch){

    /*Lower number means higher precedence*/
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
