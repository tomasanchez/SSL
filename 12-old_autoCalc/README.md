# 08 - CalcInfAuto

Calculadora Infija con Scanner Automatico basado en [07-CalcInfManual](../07-CalcInfManual2/REAMDE.md).

El  Scanner es generado por Flex, siendo asi una mejora de optimizacion a la version anterior.

## Changelog

- Calculator
  - Ya no es una estructura, solo mascara funciones de interfaz
  - Optimizacion de codigo: Se simplificaron todas sus funciones

- Parser
  - No dependede de la calculadora: object parser = **oParser**
  - Mejor distincion de tokens
  - Mejora de lectura: estetica de codigo
  - Optimizacion de codigo: no existe mas buffer, no mas multiples chequeos de tipo de token

- Solver
  - No depende de la calculadora: object solver = **oSolver**
  - Mejora de lectura: estetica de codigo
  - Optimizacion de codigo: no existe mas buffer

- Scanner
  - Implementacion con Flex
  - Mejor definicion de tokens
