# [06] - Calculadora Infija: Construccion manual

## Objetivos

- Experimentar  el  diseño  de  la  especificación  de  lenguajes  a  nivel  léxico  ysintáctico.
- Experimentar  la  implementación  manual  del  nivel  léxico  y  sintáctico  delenguajes.

## Temas

- Especificación del nivel Léxico y Sintáctico.
- Implementación del nivel Léxico y Sintáctico.
- Implementación de **Scanner**.
- Implementación de **Parser**.

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

## TODO

1. Diseñar el nivel léxico del lenguaje. [-]
2. Diseñar el nivel sintáctico del lenguaje. [-]
3. Implementar el scanner. [X]
4. Implementar el parser.[X]
5. Probar. [x]
