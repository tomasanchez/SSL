# Examen \#00

## Parte 1

1. Resolucion de problemas relacionados con la informacion mediante un sistema para la misma.

2. Conjunto de datos utiles pertinentes al problema a resolver.

3. Matematica discreta, Algoritmos y Estructura de Datos, Sintaxis y Semantica de Lenguajes, Paradigmas de la programacion, Gestion de Datos.

4. Sistemas y Organizaciones, Analisis de Sistemas, Diseño de Sistemas, Administracion de Recursos, otras materias con codigo K, tal que no se incluyan las del punto anterior.

5. Paradigma orientado a objetos.

6. Conceptualizacion donde se aisla a una razon de su contexto con el fin de ser operada sin la necesidad de conocer el mismo.

## Parte 2

1. Las secuencias poseen un orden a diferencia de los conjuntos.

2. > Coleccion enumerada de objetos, donde se admiten repeticiones y el orden es de importancia.

3. Una funcion es una relacion entre dos conjuntos:
> 𝐿𝑒𝑡 𝐹: 𝐴 → 𝐵, 𝐹 𝑖𝑠 𝑓𝑢𝑛𝑐𝑡𝑖𝑜𝑛 ↔
> ∀𝑥 ∈ 𝐴 ∃𝑦 ∈ 𝐵: (𝑥; 𝑦) ∈ 𝐹 ∧
> ∀𝑥 ∈ 𝐴: ∀𝑦1, 𝑦2 ∈ 𝐵: (𝑥; 𝑦1), (𝑥; 𝑦2) ∈ 𝐹 → 𝑦1 = 𝑦2

4. Un grafo es una terna:
> G =(E; V; Φ) ∶ V≠∅ ∧ Φ:E→V

5. > 𝐿𝑒𝑡 𝑆 𝑏𝑒 𝑎 𝑠𝑒𝑡 𝑎𝑛𝑑 𝑃 ⊆ 𝑆: 𝑃 = {𝑆1, 𝑆2, … , 𝑆𝑛}
> 𝐼𝑓 𝑃 𝑖𝑠 𝑝𝑎𝑟𝑡𝑖𝑡𝑖𝑜𝑛 𝑜𝑓 𝑆 𝑡ℎ𝑒𝑛
> ∀𝑖 ∈ 𝑁: 𝑆𝑖 ≠ ∅
> ∀𝑖, 𝑗 ∈ 𝑁: 𝑆𝑖 ∩ 𝑆𝑗 = ∅
> 
> Then partition is defined as a subsequent of unions from i to n of  𝑆 sub 𝑖; 𝑛, 𝑖 ∈ 𝑁

6. > 𝐿𝑒𝑡 X={a; b}
>
> Then 𝒫(X)={{∅}; {a}; {b}; {a; b}}  

7. > Let L be a set and V an alphabet. L is language if and only if L ∈ V*.

8. > A=(Q;V;δ;q0;F). Es finito cuando Q es un conjunto finito de estados.

## Parte 3

1. > Secuencia finita de pasos para resolver un problema.

2. Es un paradigma de programacion que tiene como objetivo mejorar la claridad, precision, calidad y tiempo de desarrollo.

3. Segun el teorema del programa estructurado: 
  - Secuencial
  - Seleccion
  - Iteracion
  
4. Los parametros estan estan definidos en la declaracion de una funcion, se les asigna un nombre y tipo; en cambio los argumentos son expresiones que son llamados por una funcion.

5. Por valor y por referencia

6. Parametros de entrada son los que se le deben asignar un valor al llamar a la funcion, los de salida retornar un valor, y por ultimo esta la combinacion de estos dos.

7. Tipo de dato abstracto (ADT) es una clase de objetos cuyo comportamiento esta definido por un conjunto de valores y operaciones.

8. La diferencia esta en el metodo de acceso y adicion de elementos: los stacks usan LIFO y las queues FIFO.

9. Es un objeto que almacena informacion.

10. Recorrer el array a, sumar todos los valores y promediar con n, en C++:

`double prom = 0;`

`for (auto& element : a)`
	`prom += element;`

`prom /= n;`

En C:

`double prom = 0;`

	for (int i = 0; i < n; i++)
		prom += a[i];`
	
	prom /= n;



