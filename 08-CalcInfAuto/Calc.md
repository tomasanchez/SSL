# Calculadora Infija :: Construcción Semi-Automática

Debo mencionar que mal interprete la consgina del trabajo practico: asumiendo que el objetvio era crear una calculadora, teniendo en cuenta los conceptos de scanner para el input, que verificase los caracteres validos; y el parser que estos esten en correcto orden, ver [`12-old_autoCalc`](../12-old_autoCalc/Calc.md).

## Diseño Léxico

No se realizan modificaciones respecto a la versión anterior.

- EOL
- NUMBER
- VAR
- ADD
- MUL
- EQ
- LET
- L_BRACKET
- R_BRACKET

Los mismos se hayan en [`scanner.h`](inc/scanner.h) bajo el enum `token_t`. Fragmento:

```c
typedef enum Token{

    EPSILON,
    //\n
    EOL,
    //[0-9]+
    NUMBER,
    //[a-zA-Z]
    VAR,
    //[ + ]
    ADD,
    //[ * ]
    MUL,
    //[=]
    EQ,
    //[ ( ]
    L_BRACKET,
    //[ ) ]
    R_BRACKET,
    // [let||LET]
    LET,
    //[ . ]
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

### LET

Permite identificar una asignación

```c
<LET>   -> let | LET | Let
    o bien
LET =   (let)|(LET)|(Let)
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
MUL     = [*]
```

### EQ

Asignación

```c
<EQ>    -> =
        o bien
EQ      = [=]
```

### BRACKETS

Parentésis

```c
<L_BRACKET> -> (
    o bien
L_BRACKET   = [(]

<R_BRAKCET> -> )
    o bien
R_BRACKET   -> [)]
```

### Codificación

En esta iteración se introduce el scanner realizado automaticámente por Flex.

Dónde se definieron las siguientes reglas

```l
%%
[ \t]
[0-9]+                                          { yylval.num = atoi(yytext); return NUMBER; }
[+]                                             { return ADD; }
[*]                                             { return MUL; }
[=]                                             { return EQ; }
[(]                                             { return L_BRACKET; }
[)]                                             { return R_BRACKET; }
("let")|("LET")|("Let")                         { return LET; }
[a-zA-Z]+                                       { yylval.index = add_variable(yytext); return VAR;}
[\n]                                            { return EOL; }
.                                               { yyerror(*yytext);} 
%%
```


## Diseño Sintáctico

En cuanto a la codificación, se optó por la propuesta sugerida en el libro de MUCHNIK. Donde cada transición del automáta esta representada por una funcion, para este caso un formato `static void PAS()`, donde se espía al próximo token y luego se realiza, de requerirse un terminal, `match(TERMINAL)` y las transiciones correspondientes.

Esta técnica utilizada es la de `Análisis Sintáctico Descendente Recursivo` (ASDR), la cual se implementa por rutinas que se van invocando de forma recursiva, contruyendo así el analisis sintactico. Cada función se llama `Procedimiento de Análisis Sintáctico` (PAS)

Además, me inspire en el manual de [`BISON`](https://www.gnu.org/software/bison/manual/bison.pdf) para los nombres y diseño de las transiciones.

Si bien, esto se puede simplificar, para una mayor visibilidad encontramos el siguiente automáta:

```c
    <Lines>         ->              |    <Line> <Lines>
    <Line>          ->  EOL         |   <Calc> EOL
    <Calc>          ->  expr        |   <Assignment>
    <Expr>          ->  <Terms>
    <Terms>         ->  <Term>      | <Term> ADD <Terms>
    <Term>          ->  <Factors>
    <Factors>       ->  <Factor>    | <Factor> MUL <Factors>
    <Factor>        ->  NUM         |      VAR       |      L_BRACKET <Expr> R_BRACKET
    <Assignment>    ->  LET VAR EQ <Calc>
```

Véase el suigiente framento de [`parcer.c`](src/parser.c)

Donde a cada transición le corresponde una función.

```c
        // <LINES>
        static void lines();

        // <LINE>
        static void line();

        // <CALC>
        static int calc();

        // <EXPR>
        static int expr();
        
        // <ASSIGMENT>
        static int assignment();

        // <TERMS>
        static int terms();

        // <TERM>
        static int term();

        // <FACTORS>
        static int factors();

        // NUMBER || VAR || ( EXPR )
        static int factor();
```

Para poder obtener cada resultado se produce una reducción, lo que podemos asociar con el concepto visto en [`Paradigmas de la Programación`](https://github.com/tomasanchez/pps/blob/master/README.md), [*folding*](https://en.wikipedia.org/wiki/Fold_(higher-order_function)), donde cada ciertos PAS reducen a un entero, por ello `static int PAS()`

Para la resolución de variables opté por contstruir un módulo de memoria [`memory.h`](./inc/memory.h), el cual se encarga de gestionar una "tabla" de símbolos a través de operaciones básicas como `create`,`read` y `update`. Por defecto, las variables no inicializadas se les otorga el valor `0` en el momento de su creación.

Las mismas se inicializan ingresando: `LET <var> = <calc>`, donde `<var>` representa una variable reconocida por el scanner y `<calc>` una operación aritmética.
