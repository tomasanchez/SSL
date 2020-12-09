# Calculadora Infija :: Construcción Semi-Automática

Debo mencionar que mal interprete la consgina del trabajo practico: asumiendo que el objetvio era crear una calculadora, teniendo en cuenta los conceptos de scanner para el input, que verificase los caracteres validos; y el parser que estos esten en correcto orden, ver [`13-old_autoCalc`](../13-old_autoCalc/README.md).

## Diseño Léxico

No se realizan modificaciones respecto a la versión anterior. Sin embargo estos son definidos por Bison

```c
%token<num>     NUMBER
%token<num>     L_BRACKET R_BRACKET
%token<num>     MUL ADD EQ
%token<num>     LET
%token<index>   VAR
%token<num>     EOL
```

### Reglas

Reutilizando el scanner, de la versión anterior, realizado automaticámente por Flex.

Dónde se definieron las siguientes reglas

```c
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

Ahora el código es generado automáticamente por Bison.

Se utiliza la técnica de `Análisis Sintáctico Descendente Recursivo` (ASDR), la cual se implementa por rutinas que se van invocando de forma recursiva, contruyendo así el analisis sintactico. Cada función se llama `Procedimiento de Análisis Sintáctico` (PAS)

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

Definido en [`parser.y`](/09-CalcInfAutoV2/bison/parser.y).

```c
/*Grammar Rules*/
%%
lines:                                          {printf("  > ");}
        |   lines line                          {printf("  > ");}

    ;
line:
            EOL                                 { printf("Please enter a calculation:\n"); }
        |   calc EOL                            { printf("  = %d\n", $1); }
    ;
calc:
            expr
        |   assignment
    ;
expr:
            terms
    ;
terms:
            term
        |   terms ADD term                      { $$ = $1 + $3; }
    ;
term:
            factors
    ;
factors:
            factor
        |   factors MUL factor                  { $$ = $1 * $3; }
    ;
factor:
            NUMBER                              { $$ = $1; }
        |   VAR                                 { $$ = get_variable($1); }
        |   L_BRACKET expr  R_BRACKET           { $$ = $2; }
    ;
assignment:
            LET VAR EQ calc                     { $$ = set_variable($2, $4); }
        ;
%%
```

Para poder obtener cada resultado se produce una reducción, lo que podemos asociar con el concepto visto en [`Paradigmas de la Programación`](https://github.com/tomasanchez/pps/blob/master/README.md), [*folding*](https://en.wikipedia.org/wiki/Fold_(higher-order_function)), donde cada ciertos PAS reducen a un entero, `$$`.

Nótese como la precesedencia de operadores esta implícita en los PAS, donde primero se `TERMS` evalúa `TERMS ADD TERM` y luego `FACTORS` evalúa `FACTORS MUL FACTOR`. [Bison advierte esto](https://www.gnu.org/software/bison/manual/html_node/Why-Precedence.html).

Opté por especificar asociatividad sólo por las dudas.

```c
/*Associativity*/
%left ADD
%left MUL 
%left L_BRACKET R_BRACKET
```

> The relative precedence of different operators is controlled by the order in which they are declared. The first precedence/associativity declaration in the file declares the operators whose precedence is lowest, the next such declaration declares the operators whose precedence is a little higher, and so on.

[*Bison Manual - Specifying Operator Precedence*](https://www.gnu.org/software/bison/manual/html_node/Using-Precedence.html).

Para la resolución de variables opté por contstruir un módulo de memoria [`memory.h`](./inc/memory.h), el cual se encarga de gestionar una "tabla" de símbolos a través de operaciones básicas como `create`,`read` y `update`. Por defecto, las variables no inicializadas se les otorga el valor `0` en el momento de su creación.

Las mismas se inicializan ingresando: `LET <var> = <calc>`, donde `<var>` representa una variable reconocida por el scanner y `<calc>` una operación aritmética.
