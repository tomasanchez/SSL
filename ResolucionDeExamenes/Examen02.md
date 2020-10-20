# Resolucion de Finales

## Ejercicio 1:

Analice la siguiente expresion C: `(lim x->0)`

- **Es sintacticamaente correcta?** Que *unica declaracion* la haria semanticamente correcta. Si no, justifique,
    Si: Podemos verlo mejor como `lim(x-- > 0)`.
    De tener:

    ```c
    lim(x --> 0);
    ```

    Bastaria con agregar.

    ```c
        /*Agregado*/
        int x;
        lim(x --> 0);
        /*Implicit function declaration*/
    ```

- **La expresion permite calcular el limite de una funcion cuando x tiende a 0?**
  No, en un principio necesitaria una forma de ligar lo que hasta el momento es `int lim(int);` con una *"funcion"*. Y en segundo definir esta ultlima; Aparte `x --> 0` no siempre evalua a 0, podria evaluar en 1 para ciertos casos.

  Sugiero `int lim(int, char *);`, donde el primer parametro representaria el valor al que tiene x, y el segundo la funcion. Y luego definir una logica donde se reemplace todas las apariciones de x en la expresion por el valor de tendencia y devuelva el valor resultado de esa evaluacion.

  Como ejemplo: `lim(0, x);` resultaria en `0`.

- **Agregar un espacio modificaria la cantidad de lexemas?**
  Si: `lim(x --> 0)` a `lim(x - -> 0)` o `l im(x --> 0)` tendriamos un lexema mas y errores de sintaxis. Para el primer caso evaluaria `x - `, esperando otra expresion, sin envargo al segurile `->` hay un quiebre; En el segundo caso, se leeria `l im` supone a `l` como un *type*.