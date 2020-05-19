# Parte I — Análisis Comparativo del tipo String en Lenguajes de Programación

Para el siguiente análisis, se compararan los lenguajes *C* y *C++*.

## Strings como parte del Lenguaje

En *C* no existen los *strings* como un tipo en si. Se considera *string* a un array de *chars* terminados con el *character* '\0'. De por si, *char* es un tipo de dato basico del lenguaje *C*.

*C++*, a diferencia, posee un tipo de dato especifico para los *strings*, que es una *class*, sin embargo, hereda la misma consideracion que *C*: se caracterizan por terminar con el *character* '\0'. Esta *class* se encuentra definida en el *namespace std* de *iostream*, biblioteca *standard input output stream objects* de *C++*.

Como *C++* fue desarrollado como una ["as an extension of C Programming Language"](https://en.wikipedia.org/wiki/C%2B%2B), podemos decir que sus alfabetos son los mismos, basados en el alfabeto ingles, con agregados de ciertos simbolos para representar operadores.

Retomando la *class string* de *C++*, esta mascara las *memory allocations y deallocations*, invisibles al programador y dinamicas. C, al no contar con un tipo especifico, estas se deben programarse.
Generalmente, en ambos lenguajes, los *strings* son mutables. Estos, pueden declararse inmutables con el *keyword const*; sin embargo, esto puede ser facilmente *casted away*.

En C, es habitual que funciones tomen como parametros *const char* *,
