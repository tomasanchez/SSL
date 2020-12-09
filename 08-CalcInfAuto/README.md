# [08] - [Calculadora Infija :: Construcción semi-Automática](./Calc.md)

Calculadora Infija con Scanner Automatico basado en [07-CalcInfManual](../07-CalcInfManualV2/README.md).

El  Scanner es generado por Flex, siendo asi una mejora de optimizacion a la version anterior.

## Objetivos

- A partir de la segunda versión, reemplazar el `scanner` por uno auto-generado por `LEX`.

## Temas

- Especificación del nivel Léxico y Sintáctico.
- Implementación del nivel Léxico y Sintáctico.
- Implementación de **Scanner**, usando Lex.
- Implementación de **Parser**.
- Resolucion de expresiones

## Problema

Análisis de expresiones aritméticas infijas simples que incluya:

- Números naturales con representación literal en base 10.
- Identificadores de variables.
- Adición.
- Multiplicación.
- Paréntesis
- Asignación

## Restricciones

- El *scanner* y el *parser* deben estar lógicamente separados.
- El  *parser*  se  comunica  con  el  *scanner*  con  la  operación  *GetNextToken*.
- El *scanner* toma los caracteres de *stdin* con *getchar*.

## Instrucciones

Ejecutar `make compile` y luego `./Calculator.exe`.