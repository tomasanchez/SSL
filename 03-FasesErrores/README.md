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
-C

Compile or assemble the source files, but do not link. The linking stage simply is not done. The ultimate output is in the form of an object file for each source file.
By default, the object file name for a source file is made by replacing the suffix .c, .i, .s, etc., with .o.

Unrecognized input files, not requiring compilation or assembly, are ignored.

-S

Stop after the stage of compilation proper; do not assemble. The output is in the form of an assembler code file for each non-assembler input file specified.
By default, the assembler file name for a source file is made by replacing the suffix .c, .i, etc., with .s.

Input files that don't require compilation are ignored.

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
$ gcc hellon.c -E -o hellon.i
```

- Compilado:

```bash
$ gcc hellon.c -S -std=c18 -Werror -Wall -pedantic-errors -Wextra
```

- Ensamble

```bash
$ gcc hellon.s -C -o hellon.o -std=c18 -Werror -Wall -Wextra -pedantic-errors -g
```

- Linkeo

```bash
$ gcc hellon.o -o hellon.exe 
```

- Compilacion & Linkeo:
  
```bash
$ gcc -o hellon.exe hellon.c -std=c18 -Werror -Wall -pedantic-errors -Wextra -g
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

#### Setup

```bash
$ mkdir 03-FasesErrores && touch $_/hello2.c
```

Luego en el *source file*

```c
#include <stdio.h>

int/*medio*/main(void){
     int i=42;
      prontf("La respuesta es %d\n");
```

#### Preprocesado

Utilizando:

```bash
$ gcc hello2.c -E -o hello2.i
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

#### Compilado

No.

### hello3.c

#### Setup

```bash
$ touch hello3.c
```

```c
int printf(const char *s, ...);

int main(void){
     int i=42;
     prontf("La respuesta es %d\n");
```

#### Investigacion

The proper declaration for *printf* is

```c
int printf(char*fmt,...)
```

where the declaration **...** means that the number and types of these arguments may vary. The declaration **...** canonly appear at the end of anargument list.

Cita textual de [The C Programming Language, 2nd Edition](https://www.amazon.com/Programming-Language-2nd-Brian-Kernighan/dp/0131103628), *Chapter 7 - Input and Output*.

#### Preprocesado

```bash
$ gcc hello3.c -E -o hello3.i
```

Analisis:

Esta vez, se obtiene un codigo menor, respecto a hello2.i:

```c
# 1 "hello3.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "hello3.c"
# 11 "hello3.c"
int printf(const char *s, ...);

int main(void){
     int i=42;
     prontf("La respuesta es %d\n");
```

Esto se debe a que no se utilizo la directiva

```c
#include <stdio.h>
```

#### Compilado

Utilizando:

```bash
$ gcc hello3.c -S -Werror -Wall -Wextra -pedantic-errors
```

Obtengo:

```
hello3.c: In function ‘main’:
hello3.c:15:6: error: implicit declaration of function ‘prontf’; did you mean ‘printf’? [-Wimplicit-function-declaration]
   15 |      prontf("La respuesta es %d\n");
      |      ^~~~~~
      |      printf
hello3.c:15:6: error: expected declaration or statement at end of input
hello3.c:14:10: error: unused variable ‘i’ [-Werror=unused-variable]
   14 |      int i=42;
      |          ^
cc1: all warnings being treated as errors
```

Y el *hello3.s*:

```s
	.file	"hello3.c"

```

Podemos observar que no cargo ninguna instruccion.

### hello4.c

#### Setup

```bash
$ touch hello4.c
```

Basadome en  los errores de compilacion de *hello3.c*:

Debemos solucionar

```
implicit declaration of function ‘prontf’
expected declaration or statement at end of input
unused variable ‘i’ [-Werror=unused-variable]
```

Entonces:

- prontf; did you mean 'printf'? Yes.
- expected declaration or statement.
- unused variable i. Warning treated as error, delete i if not used.

```c
int printf(const char *s, ...);

int main(void){
     //int i = 42;
     printf("La respuesta es %d\n");
}
```

#### Compilado

Utilizando:

```bash
$ gcc hello4.c -S -std=c18 -Werror -Wall -Wextra -pedantic-errors
```

Obtengo:

```
hello4.c: In function ‘main’:
hello4.c:15:31: error: format ‘%d’ expects a matching ‘int’ argument [-Werror=format=]
   15 |      printf("La respuesta es %d\n");
      |                              ~^
      |                               |
      |                               int
cc1: all warnings being treated as errors
```

Y en *hello4.s*:

```s
	.file	"hello4.c"
	.text
	.section	.rodata
.LC0:
	.string	"La respuesta es %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.2.1-17ubuntu1~18.04.1) 9.2.1 20191102"
	.section	.note.GNU-stack,"",@progbits
```

Se observa que, esta vez, si se generaron ciertas instrucciones.

#### Ensamble

Usando:

```bash
$ gcc -C hello4.s -o hello4.o
```

Se obtiene hello4.o sin ningun output en la terminal.

#### Linkeo

Usando:

```bash
$ gcc -o hello4.exe hello4.o
```

Se obtiene *hello4.exe*.

Esto se debe ya que *printf()* esta definida en *libc.so*, por lo que el *dynamic linker* va a resolver *symbol printf()*.
Por default, *gcc*, tiene a *libc* en todos sus programas.

#### Ejecucion

Se obtiene:

```bash
$ ./hello4.exe
La respuesta es -270054632
```

Esto  se debe a que no utilizamos *variable i*, como nos advertia el comiplador.

### hello5.c

#### Setup

```bash
$ touch hello5.c 
```

Corregimos nuestro codigo:

```c
int printf(const char *s, ...);

int main(void){
     int i = 42;
     printf("La respuesta es %d\n", i);
}
```

#### Compilacion & Linkeo

Como no se piden pasos intermedios, directamente:

```bash
$ gcc -o hello5.exe hello5.c -std=c18 -Werror -Wall -pedantic-errors -Wextra -g
```

Como era de esperarse no obtenemos ningun *error*; por consiguiente ningun *warning*, que eran *treated as errors*.

#### Ejecucion

```bash
$ ./hello5.exe
La respuesta es 42
```

### hello6.c

#### Setup

```bash
$ touch hello6.c
```

Como no teniamos errores en *hello5.c*, no es necesario corregir nada.

```
int printf(const char *s, ...);

int main(void){
     int i = 42;
     printf("La respuesta es %d\n", i);
}
```

Esto se debe por el flag *-Werror*, que permitio solucionar todos los problemas en menos pasos, prohibiendo generar el ejecutable sin haber solucionado las advertencias.

#### Compilacion & Linkeo

```bash
gcc -o hell6.exe hello6.c -std=c18 -Werror -Wall -pedantic-errors -Wextra
```

Como era de esperarse, no obtenemos ningun error.

#### Ejecucion

```bash
./hello6.exe
La respuesta es  42
```

### hello7.c

#### Setup

```
touch hello7.c
```

Tenemos una nueva variante:

```c
int main(void){
    int i=42;
    printf("La respuesta es %d\n", i);
}
```

#### Compilacion & Linkeo

```bash
gcc -o hello7.exe hello7.c -std=c18 -Werror -Wall -pedantic-errors -Wextra
```

Como **NO** era de esperarse, no compila:

```
hello7.c: In function ‘main’:
hello7.c:13:6: error: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
   13 |      printf("La respuesta es %d\n", i);
      |      ^~~~~~
hello7.c:13:6: error: incompatible implicit declaration of built-in function ‘printf’ [-Werror]
hello7.c:1:1: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
  +++ |+#include <stdio.h>
    1 | /* ---------------------------------------------------------------------------------
cc1: all warnings being treated as errors
```

Si bien esto se debe al parametro *-Werror*, indica que estamos haciendo *bad programming*.
Estamos haciendo *implicit declaration* de una funcion, lo cual nunca deberiamos hacer.

Sacando *-Werror*:

```
$ gcc -o hello7.exe hello7 -stc=c18
```

```
hello7.c: In function ‘main’:
hello7.c:13:6: warning: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
   13 |      printf("La respuesta es %d\n", i);
      |      ^~~~~~
hello7.c:13:6: warning: incompatible implicit declaration of built-in function ‘printf’
hello7.c:1:1: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
  +++ |+#include <stdio.h>
    1 | /* ---------------------------------------------------------------------------------
```

Pero esta vez si se crea el ejecutable.

Si bien funciona; esto se debe a que, como se expreso anteriormente, por default, *gcc*, tiene a *libc* en todos sus programas; no existen mas errores sintacticos como en los casos anteriores. No considero correcta esta aplicacion.

Considerar correcto a *hello7.c* es ignorar los *warnings* del compilador, lo cual creo que es mala practica: por algo se nos informa de esto.


