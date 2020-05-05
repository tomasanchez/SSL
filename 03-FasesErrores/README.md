# 03 - Fases de la Traducción y Errores

## Objetivos

- Identificar las fases de Traduccion y Errores.

## Tareas

1. Investigar  las  funcionalidades  y  opciones  que  su  compilador  presenta  paralimitar el inicio y fin de las fases de traducción.
2. Para la siguiente secuencia de pasos:
   - Transicribir en readme.md cada comando ejecutado.
   - Describir en readme.md el resultado u error obtenidos para cada paso

## Desarrollo

### Investigacion

Utilizo el compilador gcc

```bash
$gcc --version
```

Obtengo:

```bash
gcc (Ubuntu 9.2.1-17ubuntu1~18.04.1) 9.2.1 20191102
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

*QED* que se cumplen los requisitos de utilizar el *standard* **c18**.

Considero que la mejor manera de invesitgar el compilador es leyendo su manual, para ello:

```bash
$man gcc
```

Resultados de investigacion:

```
-E

Stop after the preprocessing stage; do not run the compiler proper. The output is in the form of preprocessed source code, which is sent to the standard output.
Input files which don't require preprocessing are ignored.
```

Como no queremos *ensuciar* la terminal...

```
-o file

Place output in file file. This applies regardless to whatever sort of output is being produced, whether it be an executable file, an object file, an assembler file or preprocessed C code.

If -o is not specified, the default is to put an executable file in a.out, the object file for source.suffix in source.o, its assembler file in source.s, a precompiled header file in source.suffix.gch, and all preprocessed C source on standard output. 
```

Por fines academicos:

```
Options to Request or Suppress Warnings

Warnings are diagnostic messages that report constructions which are not inherently erroneous but which are risky or suggest there may have been an error.

The following language-independent options do not enable specific warnings but control the kinds of diagnostics produced by GCC .
```

```
-Werror
    Make all warnings into errors.
```

```
-pedantic
    Issue all the warnings demanded by strict ISO C and ISO C ++ ; reject all programs that use forbidden extensions, and some other programs that do not follow ISO C and ISO C ++ . For ISO C, follows the version of the ISO C standard specified by any -std option used.

-pedantic-errors
    Like -pedantic, except that errors are produced rather than warnings.

-
```

```
-Wall
    This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros.
```

```
-Wextra
    This enables some extra warning flags that are not enabled by -Wall. (This option used to be called -W. The older name is still supported, but the newer name is more descriptive).
```

Utilizaria entonces para,

- Preprocesado:

```bash
$gcc hellon.c -E -o hellon.i
```

- Compilacion:
  
```bash
$gcc hellon.c -o hellon.out -std=c18 -Werror -Wall -pedantic-errors -Wextra
```

Durante el analisis del primer preprocesado, *hello2.i*, note que era necesario profundizar la investigacion:

Resultados:

```
Source file name and line number information is conveyed by lines of the form

# linenum filename flags

These are called linemarkers. They are inserted as needed into the output (but never within a string or character constant). They mean that the following line originated in file filename at line linenum. filename will never contain any non-printing characters; they are replaced with octal escape sequences.

After the file name comes zero or more flags, which are ‘1’, ‘2’, ‘3’, or ‘4’. If there are multiple flags, spaces separate them. Here is what the flags mean:

‘1’

    This indicates the start of a new file. 
‘2’

    This indicates returning to a file (after having included another file). 
‘3’

    This indicates that the following text comes from a system header file, so certain warnings should be suppressed. 
‘4’

    This indicates that the following text should be treated as being wrapped in an implicit extern "C" block. 

```

Fuente:

[GCC - Preprocessor Output](https://gcc.gnu.org/onlinedocs/cpp/Preprocessor-Output.html)

### hello2.c

```bash
$mkdir 03-FasesErrores && touch $_/hello2.c
```

Luego en el *source file*

```c
#include <stdio.h>

int/*medio*/main(void){
     int i=42;
      prontf("La respuesta es %d\n");
```

#### Precompilado

Utilizando:

```bash
$gcc hello2.c -E -o hello2.i
```

Analisis:

A partir de la linea 791:

```c
# 868 "/usr/include/stdio.h" 3 4

# 12 "hello2.c" 2


# 13 "hello2.c"
int main(void){
     int i=42;
      prontf("La respuesta es %d\n");
```

Observo que:

- Se incluye el header stdio.h, ocupando mas de 700 lineas.
- Los flags 3 y 4, *linemarkers*, aclaran esto; *following text comes from a system header file* y *following text should be treated as being wrapped in an implicit extern "C" block* respectivamente.
- El programa arranca en la linea 12, y esto se debe al *header comments*, obligatorios.
- Los comentarios se sustituyen por espacios vacios.

#### No compilacion

Utilizando:

```bash
$gcc hello2.c -o hello2.out -std=c18 -Werror -Wall -pedantic-errors -Wextra
```
Obtengo

```
hello2.c: In function ‘main’:
hello2.c:15:7: error: implicit declaration of function ‘prontf’; did you mean ‘printf’? [-Wimplicit-function-declaration]
   15 |       prontf("La respuesta es %d\n");
      |       ^~~~~~
      |       printf
hello2.c:15:7: error: expected declaration or statement at end of input
hello2.c:14:10: error: unused variable ‘i’ [-Werror=unused-variable]
   14 |      int i=42;
      |          ^
cc1: all warnings being treated as errors
```

### hello3.c

#### Setup

```bash
$touch hello3.c
```

```c
int printf(const char *s, ...);

int main(void){
     int i=42;
     prontf("La respuesta es %d\n");
```

#### Investigacion

>
Theproperdeclarationforprintfis
intprintf(char*fmt,...)
wherethedeclaration...meansthatthenumberandtypesoftheseargumentsmayvary.The
declaration...canonlyappearattheendofanargumentlist.

