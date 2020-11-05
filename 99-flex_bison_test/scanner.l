%{
/* Reconoce números enteros y palabras alfabéticas; además,
cuenta las ocurrencias de ambos */
#include <stdio.h>
int nros, pals;
void getToken();
%}

%option noyywrap

%%
[0-9]+ { puts(yytext); nros++;}
[a-zA-Z]+ { pals++; }
[+*-]+    { puts(yytext);}
.|\n
%%

int main(void) {
yylex();
printf("Se reconocieron:\n");
printf("%d Numeros y\n", nros);
printf("%d Palabras.\n\n", pals);
return 0;
}