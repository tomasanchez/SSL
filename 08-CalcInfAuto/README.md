# [08] - Calculadora Infija :: Construccion Automatica 

## Objetivos

- A partir de la segunda version manual, implementar un Scanner con Flex/Lex.

## Temas

- Especificación del nivel Léxico y Sintáctico.
- Implementación del nivel Léxico y Sintáctico.
- Implementación de **Scanner**.
- Implementación de **Parser**.
- Resolucion de expresiones

## Problema

Análisis de expresiones aritméticas infijas simples que incluya:

- Números naturales con representación literal en base 10.
- Identificadores de variables.
- Adición.
- Multiplicación.

## Restricciones

- El *scanner* y el *parser* deben estar lógicamente separados.
- El  *parser*  se  comunica  con  el  *scanner*  con  la  operación  *GetNextToken*.
- El *scanner* toma los caracteres de *stdin* con *getchar*.