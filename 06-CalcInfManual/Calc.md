# Calculadora Infima :: Construccion Manual

Debo mencionar que mal interprete la consgina del trabajo practico: asumiendo que el objetvio era crear una calculadora, teniendo en cuenta los conceptos de scanner para el input, que verificase los caracteres validos; y el parser que estos esten en correcto orden, ver [`10-old_manualCalc`](../10-old_manualCalc/Calc.md).

## Diseño Lexico

Para esta primera iteracion busque cumplir con la consigna implementando lo basico, con esto encontraremos los siguientes tokens:

- EOL
- NUMBER
- VAR
- ADD
- MUL

Los mismos se hayan en [`sanner.h`](inc/scanner.h) bajo el enum `token_t`. Fragmento:

```c
typedef enum Token{
    //\n
    EOL,
    //[0-9]+
    NUMBER,
    //[a-zA-Z]
    VAR,
    //( + )
    ADD,
    //( * )
    MUL,
    //( . )
    UNDEFINED
}token_t;
```

### EOL

Representa *end of line*, para este el lenguaje que lo reconoce consta de:

```c
<EOL>   ->   \n
    o bien
EOL     =   [\n]
```

### Number

Number abarca a los numeros en base 10, siendo:

```c
<NUMBER>    -> DIGIT | DIGIT NUMBER
<DIGIT>     -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
                o bien
NUMBER      = [0-9]+
```

### VAR

Variables

```c
<VAR>       -> <LETTER> | <VAR> <LETTER>
<LETTER>    -> a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z
                o bien
VAR         = [a-zA-Z]+
```

### ADD

Sumatoria

```c
<ADD> -> +
        o bien
ADD   = [+]
```

### MUL

Multiplicación

```c
<MUL>   -> *
        o bien
MUL     =   [*]
```

## Diseño Sintáctico

En cuanto a la codificación, se optó por la propuesta sugerida en el libro de MUCHNIK. Donde cada transición del automáta esta representada por una funcion, para este caso un formato `static void transition()`, donde se espía al próximo token y luego se realiza, de requerirse un terminal, `match(TERMINAL)` y las transiciones correspondientes.

Además, me inspire en el manual de [`BISON`](https://www.gnu.org/software/bison/manual/bison.pdf) para los nombres y diseño de las transiciones.

Si bien, esto se puede simplificar, para una mayor visibilidad encontramos el siguiente automáta:

```c
    <Lines>     ->              |    <Line> <Lines>
    <Line>      ->  EOL         |   <Expr> EOL
    <Expr>      ->  <Terms>
    <Terms>     ->  <Term>      | <Term> ADD <Terms>
    <Term>      ->  <Factors>
    <Factors>   ->  <Factor>    | <Factor> MUL <Factors>
    <Factor>    ->  NUMBER      | VAR
```

Véase el suigiente framento de [`parcer.c`](./src/parser.c)

Donde a cada transición le corresponde una función.

```c
        // Gets next token from scanner
        static void match(int);

        // Handles error parsing
        static void yyperror();

        // <INPUT>
        static void lines();

        // <LINE>
        static void line();

        // <EXPR>
        static void expr();

        // <TERMS>
        static void terms();

        // <TERM>
        static void term();

        // <FACTORS>
        static void factors();

        // NUMBER || VAR
        static void factor();
```