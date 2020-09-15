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

## Solucion

Opte por una la siguiente resolucion:

```c
    /* Poseemos el siguiente flujo*/

    calculator_t this_calculator = calculator_create();

    calculator_update(&this_calculator);

    calculator_print_results(&this_calculator);

    return calculator_destroy(&this_calculator);
```

**Que es un calculator?**

Vemos que tenemos una calculadora, que *'realiza'* distintos *'metodos'*.


```c
/*Una calculadora basicamente cuenta con:*/

#define buffer_size 32

typedef struct Calculator{
    scanner_t scanner;
    parser_t parser;
    char tbuffer[buffer_size];
} calculator_t;
```

**Update**

```c
int calculator_update(calculator_t * this){

    /*Aqui entra en juego el scanner, quien scannea unicamente caracteres validos*/
    calculator_read(this);

    /*Consideramos que funciona mientras hay tokens para parsear*/
    while( calculator_is_running(this)){
        /*GetNextToken permite comunicar scanner con parser*/
        calculator_GetNextToken(this);
    }

    return 0;
}
```

**GetNextToken** 

```c
int calculator_GetNextToken(calculator_t * this){

    /* El buffer del scanner se mueve token a token al buffer de la calculadora*/
    scanner_GetNextToken(this->tbuffer, &this->scanner);
    tokens_g = ++this->tokens;
    
    /*Se valida el token*/
    this->token_type        =                           calculator_validate_token(this);
    this->previous_token    = this->token_parsed    =   this->token_type;

    /*Y pasa del buffer de la calculadora a un buffer en el paser*/
    parser_GetNextToken(&this->parser, this->tbuffer, this->token_parsed);

    this->index = buffer_clean(this->tbuffer);

    return 0;
}
```

Como se vio, *GetNextToken* comunica nuestros tres objetos basicos, donde:

1. *Scanner* mantiene la expresion que se ingreso.
2. *Calculator* unicamente posee un token a la vez.
3. *Parser* genera internamente una lista de tokens.

**Print_Results**

```c
inline int calculator_print_results(calculator_t * this){
    /*El scannner primero valida la sintaxis*/
    scanner_syntax_check(&this->scanner);
    /*Luego informa los errores*/
    scanner_print(&this->scanner);
    /*Finalmente, el parser itera sobre su lista de tokens, evaluandolos 1 a 1*/
    return parser_print_results(&this->parser);
}
```

**Destroy**

```c
int calculator_destroy(calculator_t * this){
    /* Se libera la memoria pedida por la lista del parser*/
    parser_destroy(&this->parser);
    return 0;
}
```
