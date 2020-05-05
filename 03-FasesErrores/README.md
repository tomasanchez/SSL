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

### hello2.c

Setup:
```bash
$mkdir 03-FasesErrores && touch $_/hello2.c
```
