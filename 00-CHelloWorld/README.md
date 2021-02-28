# 00 - C Hello World

## Objetivos

1. Demostrar  con,  un  programa  simple,  que  se  está  en  capacidad  de  editar, compilar, y ejecutar un programa C.
2. Contar  con  las  herramientas  necesarias  para  abordar  la  resolución  de  los trabajos posteriores.

### Objetivos Personales

0. Sacar el máximo provecho al TP, a pesar de su simpleza.
1. Familiarizarme con Visual Studio Code; hasta el momento venía trabajando con Visual Studio Community 2019.
2. Aprender a utilizar github vía terminal.
3. Aprender a compilar un .c vía terminal.
4. Introducirme a Linux con Windows Subsystem for Linux (WSL2).

## Metodología de Resolución

Para resolver el trabajo utilicé el editor de texto Visual Studio Code. Cloné el repositorio SSL, ya creado para el Examen#00, y creé el directorio pedido.

```$ mkdir 00-CHelloworld && touch $_/hello.c```

Para que el código se lo más simple posible utilicé ```puts()``` y no ```printf()```, nótese que el compilador habría de reemplazar printf por puts.

Compilé usando gcc

```$ gcc -o hello hello.c -std=c18 -Wall```

Generé el archivo ```.txt``` directo desde la terminal

```$ ./hello > output.txt```
