# Calculadora Infima :: Construccion Manual

## Diseño Lexico

Podemos encontrar dos categorias:

- **OPERAND**
- **OPERATOR**
  
Donde a su vez, *OPERAND* se puede subdividir en...

- **INTEGER**
- **ID**


Cada categoria tiene una gramatica propia asociada.

### Integer

```
INTEGER     -> DIGIT | DIGIT • DIGIT_CHAIN
DIGIT       -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
DIGIT_CHAIN -> DIGIT | DIGIT • DIGINT_CHAIN
```

O bien

```
INTEGER = [0-9]+
```

### ID

```
ID          -> a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z | CAP_LETTER
CAP_LETTER  -> A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z
```

O bien,

```
ID = [A-Za-z]
```

### OPERATOR

```
OPEATOR -> + | * | -
```

### OPERAND

```
OPERAND -> INTEGER | ID
```

### En BNF

```
<TOKEN> -> one of <OPERAND> <OPERATOR>

<OPERATOR> -> one of <ID> <INTEGER>

<ID> -> one of a-zA-Z

<INTEGER> -> 0-9
```

## Diseño Sintactico

Las expresiones seran validas unicamente si cumplen con las *producciones*.

*Producciones*:

```
FEXPR -> OPERAND | OPERAND • EXPR
EXPR  -> OPERATOR • FEXPR
```
