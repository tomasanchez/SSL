# 00 - C Hello World

## Objetivos

1. Demostrar  con,  un  programa  simple,  que  se  está  en  capacidad  de  editar,compilar, y ejecutar un programa C.
2. Contar  con  las  herramientas  necesarias  para  abordar  la  resolución  de  lostrabajos posteriores.

### Objetivos Personales

0. Sacar el maximo provecho al TP por mas simple que sea.
1. Familiarizarme con Visual Studio Code; hasta el momento venia trabajando con Visual Studio Community 2019.
2. Aprender a utilizar github via terminal.
3. Aprender a compilar un .c via terminal.
4. Introducirme a Linux con Windows Subsystem for Linux.

## Metodologia de Resolucion

Para resolver el trabajo utilice el editor de texto Visual Studio Code. Clone el repositorio SSL, ya creado para el Examen#00, y cree el directorio pedido.

```$ mkdir 00-CHelloworld && touch $_/hello.c```

Para que el codigo se lo mas simple posible utilice ```puts()``` y no ```printf()```.

Compile usando gcc

```$ gcc -o hello hello.c -std=c18 -Wall```

Genere el archivo ```.txt``` directo desde la terminal

```$ ./hello > output.txt```
