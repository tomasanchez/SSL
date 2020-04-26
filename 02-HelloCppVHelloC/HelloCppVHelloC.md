# 02 - Hello Cpp vs Hello

## Hello in C++

Utilizare el siguiente codigo para la comparacion:

```c++
#include <iostream>

int main (int argc, char* argv[]){

    std::cout << "Hello,  World!" << endl;

    return 0;
}
```

## Hello in C

En C, equivalente podriamos tener:

```c
#include <stdio.h>

int main (int argc, char* argv []){

    puts("Hello,  World!")

    return 0
}
```

## Hello in Haskell

Si bien *Haskell* trabaja con otro paradigma, funcional, a diferencia de *C* y *C++* que lo hacen con el paradigma estructurado:

```haskell

main = putStrLn "Hello World!"

```

## Tabla de comparacion

|                                                  Sintaxis                                                 	|                                        Semantica                                        	|                                  Pragmatica                                  	| Lenguaje 	|
|:---------------------------------------------------------------------------------------------------------:	|:---------------------------------------------------------------------------------------:	|:----------------------------------------------------------------------------:	|:--------:	|
|                                        Utiliza biblioteca *stdio.h*                                       	|                                    Llamada a funcion                                    	|         **Escribe** al *string* y agrega una  *newline* en *stdout*.         	|     C    	|
|                 Utiliza biblioteca *iostream* utilizacion el operador *::(scope qualifier)*               	|      Realiza una operacion *<< (overload de bitwise)*  y llama a una funcion *endl*     	|  **Inserta** al *string* en el *ostream* y **Realiza** un *flush* del mismo  	|    C++   	|
|  Los parametros se especifican solo un espacio en blanco No se incluyen librerias No se define un *scope* 	|   Se declara una igualdad donde "se le asigna" otro nombre a una funcion ya determinada 	|                   **Escribe** en el *standard output device*                 	|  Haskell 	|