# Parte I — Análisis Comparativo del tipo String en Lenguajes de Programación

Para el siguiente análisis, se compararan los lenguajes *C* y *C++*.

## Strings como parte del Lenguaje

En *C* no existen los *strings* como un tipo en si. Se considera *string* a un array de *chars* terminados con el *character* '\0'. De por si, *char* es un tipo de dato basico del lenguaje *C*.

*C++*, tampco posee un tipo de dato especifico para los *strings*, sino un objeto, *class*, sin embargo, hereda la misma consideracion que *C*: se caracterizan por terminar con el *character* '\0'. Esta *class* se encuentra definida en el *namespace std* de *iostream*, biblioteca *standard input output stream objects* de *C++*.

Como *C++* fue desarrollado ["as an extension of C Programming Language"](https://en.wikipedia.org/wiki/C%2B%2B), podemos decir que sus alfabetos son los mismos, basados en el alfabeto ingles, con agregados de ciertos simbolos para representar operadores.

Retomando la *class string* de *C++*, esta mascara las *memory allocations y deallocations*, invisibles al programador y dinamicas. C, al no contar con un tipo especifico, estas se deben programarse.
Generalmente, en ambos lenguajes, los *strings* son mutables. Estos, pueden declararse inmutables con el *keyword const*; sin embargo, esto puede ser facilmente *casted away*.

En C, es habitual que funciones tomen como parametros *const char* *, como asi tambien devolverlos; se trata de un *First Class Citizen*
Como en C++, es un objeto, no es recomendable pasarlos como parametros para funciones simples, como asi tipo del valor de retorno. Sin embargo, esto es posible, siendo tambien un *fisrt class citizen*.
En general, para evitar *overhead*, se pasa por referencia

## Declarion y Asignacion

En C:

```c
const char * str = "This is a string literal.";
```

En C++

```cpp
std::string my_str;
/* O inicializado con un c-string*/
std::string name("Mark");
/* O con otro std::string */
std::string name2(name);
/* Incluso con un substring */
std::string lip(name, 4);
```
