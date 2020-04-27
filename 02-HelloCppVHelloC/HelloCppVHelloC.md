# 02 - Hello Cpp vs Hello C

## Hello in C++

Utilizare el siguiente codigo para la comparacion:

```c++
#include <iostream>

int main (int argc, char* argv[]){

    std::cout << "Hello,  World!" << std::endl;

    return 0;
}
```

## Hello in C

En C, equivalente podriamos tener:

```c
#include <stdio.h>

int main (int argc, char* argv []){

    puts("Hello,  World!");

    return 0;
}
```

## Hello in Haskell

Si bien *Haskell* trabaja con otro paradigma, funcional, a diferencia de *C* y *C++* que lo hacen con el paradigma estructurado:

```haskell

main = putStrLn "Hello, World!"

```

## Tabla de comparacion

|                                                  Sintaxis                                                 	|                                        Semantica                                        	|                                  Lexico                                  	| Lenguaje 	|
|:---------------------------------------------------------------------------------------------------------:	|:---------------------------------------------------------------------------------------:	|:----------------------------------------------------------------------------:	|:--------:	|
|                                        Utiliza biblioteca *stdio.h*, operador subfija                                       	|                                    Llamada a funcion a la cual se pasa un argumento para **escribir** al *string* y agregar una *newline* en *stdout*.                                      	|         No posee token '::' definido        	|     C    	|
|                 Utiliza biblioteca *iostream*, operaciones infijas, utilizacion el operador *:: (scope qualifier)*               	|      Realiza una operacion *<< (overload de bitwise)*  y llama a una funcion *endl* del *namespace std* para **insertar** al *string* en el *ostream* y **realizar** un *flush* del mismo    	|   Posee token '::', hereda la mayoria de sus tokens de C 	|    C++   	|
|  Los parametros se especifican solo un espacio en blanco. No se incluyen librerias. Unica sentencia. Operaciones subfijas 	|   Se declara una igualdad donde "se le asigna" otro nombre a una funcion ya determinada para **escribir** en el *standard output device* 	|                                    Posee token '::', *(no utilizado en este ejemplo)*, no utiliza '{}' *(en este ejemplo}*, no posee operador '<<', Existe 'Int' equivalente a 'int'	|  Haskell 	|
