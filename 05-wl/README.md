# 05 - wl

## Arboles

### Inicializacion de Contadores

![ci](dot/ci.dot.svg)

### Expresiones de Control

![ce](dot/ce.dot.svg)

## Maquina de Estado

![wl](dot/wl.svg)

Nota: EOL representa *end of line characters* que incluye el ingreso de *'\n', '\t', etc*, mientras que *char* un caracter cualquiera distinto a los de EOL.

### Switch - Enum

El usar un *typedef* para el *state* permite el encapsulamiento, mayor comprension del contexto y por ende mas legibilidad; sin embargo a cambio tenemos un codigo mas extenso; esto se ve claramente si comparamos:

```c
if( c == ' ' || c == '\n' || c == '\t');
```

Con

```c
switch(c){
    case '\n':
    case '\t':
    case ' ':
    default:
}
```
