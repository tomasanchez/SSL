# [07] - Calculadora Infija Automática

## Objetivos

- A partir de la primera version, ahora poder permitir realizar operaciones y uso de parentesis.

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

## Instrucciones

Ejecutar `make compile` y luego `./Calculator.exe`