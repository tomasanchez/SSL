/* ---------------------------------------------------------------------------------

    scanner.c

    scanner for infix calculator.

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

    last modified: 11/17/2020
------------------------------------------------------------------------------------ */

#include "../inc/scanner.h"

// Max amount of characters, based on YYLMAX
#define BUFFER_SIZE 8192

/*
===============================================================================================================================
============================================== Scanner Design =================================================================
===============================================================================================================================
*/

/*class Scanner{--------------------------*/

    //Public:

        // Token Value
        value_t yyval;

        void yyerror(int);


    // Private:

        // Character buffer
        char yytext[BUFFER_SIZE] = "";

        /*Tells if character is number*/
        static bool isNumber(int);

        /*Tells if character is a letter*/
        static bool isLetter(int);

        /*Tells if id corresponds to let*/
        static bool isLet(char *);

        /*Stores tokens*/
        static int pushToken();

/*};----------------------------------*/


/*
===============================================================================================================================
============================================== Exported Functions =============================================================
===============================================================================================================================
*/

int getNextToken(){

    int c, i = 0;

    //Clear buffers
    memset(yytext, 0, BUFFER_SIZE);
    yyval.index = 0;
    yyval.num = 0;

    /*Until End Of File*/
    while((c=getchar()) != EOF){
        switch (c)
        {
            case ' ':
            case '\t':
                continue;
            case '+':
                return ADD;
            case '*':
                return MUL;
            case '=':
                return  EQ;
            case '(':
                return L_BRACKET;
            case ')':
                return R_BRACKET;
            case '\n':
                return EOL;
            default:
                   
                    /* Inside Number */
                    while (isNumber(c))
                    {
                        yytext[i++] = c;

                        c = getchar();

                        if(! isNumber(c)){
                            ungetc(c, stdin);
                            pushToken();
                            return NUMBER;
                        }
                    }
                    
                    /*Inside variable name*/
                    while(isLetter(c)){
                        yytext[i++] = c;

                        c = getchar();

                        if(! isLetter(c)){
                            ungetc(c, stdin);

                            if(isLet(yytext))
                                return LET;
                            else
                            {
                                yyval.index = add_variable(yytext);
                                return VAR;
                            }
                        }

                    }

                    yyerror(c);
        }
    }

    yyval.num = EOF;
    return EOF;
}

int peekNextToken(){
    int c = 0, i = 0;
    int size = i;

    char buffer[BUFFER_SIZE];

    memset(buffer, 0, BUFFER_SIZE);

    while((c = getchar()) != EOF){
        //Reads from stdin
        switch (c)
        {
        case ' ':   //Eats spaces
        case '\t':
                continue;
            break;
        case '+':
            ungetc('+', stdin);
            return ADD;
        case '*':
            ungetc('*', stdin);
            return MUL;
        case '=':
            ungetc('=', stdin);
            return EQ;
        case '(':
            ungetc('(', stdin);
            return L_BRACKET;
        case ')':
            ungetc(')', stdin);
            return R_BRACKET;    
        case '\n':
            ungetc('\n', stdin);
            return EOL;
        case EOF:
            ungetc(EOF, stdin);
            return EOF;
        default:
                /* Inside Number */
                while (isNumber(c))
                    {
                        
                        buffer[i++] = c;

                        c = getchar();

                        if(! isNumber(c)){
                            size = i;

                            ungetc(c, stdin);

                            for( --i ; 0 <= i; i--){
                                ungetc(buffer[i], stdin);
                            }
                            
                            return NUMBER;
                        }
                    }

                    /*Inside Identifier*/
                    while(isLetter(c)){

                        buffer[i++] = c;

                        c = getchar();

                        if(! isLetter(c)){
                            size = i;

                            ungetc(c, stdin);

                            for( --i ; 0 <= i; i--){
                                ungetc(buffer[i], stdin);
                            }
                            if (isLet(buffer))
                                return LET;
                            else
                            {
                                //yyval.index = add_variable(buffer);
                                //printf("PEEK INDEX is %d\n", yyval.index);
                                return VAR;
                            }
                        }
                    }

                    yyerror(c);
            break;
        }
    }
    return EOF;
}

void yyerror(int c){
    printf("Syntax Error: Undefined Symbol '%c'\nCalculator exited with syntax error.\n", c);
    exit(1);
}

/*
===============================================================================================================================
============================================== Private Functions =============================================================
===============================================================================================================================
*/

static int pushToken(){
    yyval.num = atoi(yytext);

    memset(yytext, 0, BUFFER_SIZE);
    return 0;
}

/*
===============================================================================================================================
============================================== Control Functions =============================================================
===============================================================================================================================
*/

static inline bool isNumber(int c){
    return c >= '0' && c <='9';
}

static inline bool isLetter(int c){
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

static inline bool isSpace(int c){
    return c == '\t' || c == ' ';
}

static bool isLet(char * str){

    // Being "L E T \0" needs space for 4 chars
    char strUpper[4] = "";

    for(int i = 0; i < 4; i++){
        strUpper[i] = toupper(str[i]);
    }

    return strcmp("LET", strUpper) == 0;
}