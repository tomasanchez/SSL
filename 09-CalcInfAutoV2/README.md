# [08] - [Calculadora Infija :: Construcción Automática](./Calc.md)

Calculadora Infija con Scanner Automatico basado en [09-CalcInfAuto](../07-CalcInfAuto/README.md).

El  Scanner es generado por Flex.
El  Parser  es generado por Bison.

## Objetivos

- Reutilizar    el      `scanner`   auto-generado por `LEX`.
- Además implementar un `parser`    auto-generado por `YACC`

## Temas

- Especificación del nivel Léxico y Sintáctico.
- Implementación del nivel Léxico y Sintáctico.
- Implementación de **Scanner**, usando `Lex`.
- Implementación de **Parser**, usando `Yacc`.
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

## Instrucciones

Ejecutar `make compile` y luego `./Calculator.exe`.