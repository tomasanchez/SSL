#include <stdio.h>
#include <string.h>


int buscarMinimaCantidad(int V[], int tam);
int busquedaTablaMateria(char tabla[500][30], char buscar[]);
int busquedaTablaProfesor(int tabla[], int buscar);
void ordenarMayorAlumnos(int contadorAlumnos[], int id[]);


int main (){

    int legajos[400], legajoIngresado;
    int cargo[7], cargoIngresado;
    char depto[10][15];
    char deptoIngresado[15];

    /*Inicializo contador de cargos*/
    for(int i =0; i<7; i++){
        cargo[i] = 0;
    }

    /* Leo Lote - Inicializo Legajos*/
    for (int i = 0; i < 400; ++i){

        /* Leo todos los datos del lote*/
        scanf("%d%d%s", &legajos[i], &cargoIngresado, &deptoIngresado);

        /* Cuento el cargo, resto uno porque va de 1 a 7 pero el vector de 0 a 6*/
        cargo[cargoIngresado-1]++;
    }

    /* El otro punto*/
    
    char materiaIngresada[30];

    char materiasFacultad[500][30];

    /*Inicializas materias de la facultad*/
    for(int i=0; i <500; i++){
        
        for(int j = 0 ; j < 30; j++){
            materiasFacultad[i][j] = "\0";
        }
    }

    /*Leo el otro lote*/
    scanf("%d", &legajoIngresado);

    /*Inicializo el contador*/
    int contadorXmateria[500];
    for (int i =0; i<500; i++){
        contadorXmateria[i] = 0;
    }

    char modalidad;
    int alumnos, nivel;

    int contadorProfesor[400];
    for(int i = 0; i <400; i++){
        contadorProfesor[i]=0;
    }

    while(legajoIngresado != 0){

        /*Leo alumnos materia nivel y modalidad*/
        scanf("%d%s%c%d", &alumnos, &materiaIngresada, &modalidad, &nivel);


        if(modalidad == 'C'){
            /* Cuento los alumnos en el contador, el indice lo obtengo por la funcion esa, depues vemos la funcion*/
            int indice = busquedaTablaMateria(materiasFacultad, materiaIngresada);
            contadorXmateria[indice] += alumnos;
        }else{
            /* No cuento las anuales*/
            int indice = busquedaTablaMateria(materiasFacultad, materiaIngresada);
            contadorXmateria[indice] = 0;
        }

        int indice = busquedaTablaProfesor(legajoIngresado, legajos);
        contadorProfesor[indice]++;
        /*Leo el nuevo profesor del curso*/
        scanf("%d", &legajoIngresado);
    }

    /* Profesores con menos cursos*/

    /* Busco la minima cantidad de cursos, por ejemplo 3*/
    int cantidadCursosMinima = buscarMinimaCantidad(contadorProfesor, 400);

    /*Busco los profesores con menos cursos*/
    for (int i =0; i <400; i++){

        /* Si tiene esa cantidad o menos, que no deberia pero x las dudas lo imrpimo*/
        if(cantidadCursosMinima <= contadorProfesor[i]){
            printf("Legajo %d", legajos[i]);
        }
    }

    /*Esto es para saber que materias tiene cada alumno, que se van a ordenar, y es dificil ordenar la matriz*/
    int idMaterias[500];
    for(int i = 0; i <500; i++){
        idMaterias[i] = i;
    }

    /* Punto 2 - Primero ordeno, con los idMateiras*/
    ordenarMayorAlumnos(contadorXmateria, idMaterias);
    for(int i = 0; i <500; i++){

        char aux[30];

        /*Buscas en la materia con el Id[i] fijo, solo moves el j para el nombre, la posicion la saco del otro vector*/
        for(int j = 0; j<30; j++){
            aux[j] = materiasFacultad[idMaterias[i]][j];
        }


        /* Esto muestra solo las Cuatrimestralels, recordemos que las Anuales le pongo 0 aproposito*/
        if(contadorXmateria[i] != 0){
        printf("La materia %s, tiene %d alumnos", aux, contadorXmateria[i]);
        }
    }

    /* Punto 3 profesores por cargos    */
    for (int i = 0; i  < 7; i++){
        printf("En el cargo %d, hay %d profesores\n", i+1, cargo[i]);
    }


    return 0;
}

/* Minima cantidad de cursos */
int buscarMinimaCantidad(int V[], int tama){
    int minimo = V[0];
    for(int i = 0 ; i< tama ;  i++){
        if(V[i]<= minimo){
            minimo = V[i];
        }
    }

    return minimo;
}

int busquedaTablaMateria(char tabla[500][30], char buscar[]){
    int i;
    char auxiliar[30];

    for (i=0; i<500; i++){

        /*Copio en auxiliar*/
        for(int j=0; j<30; j++){
            auxiliar[j]=tabla[i][j];
        }

        /*Si la materia no existe la creo*/
        if(auxiliar[0]=="\0"){
            for(int j=0; j<30; j++){
                tabla[i][j]=buscar[j];
            }
            /*Devuelvo el indice*/
            return i;
        }else if(strcmp(auxiliar, buscar) == 0){ /*Sino devuelvo el indice en el que se encontro*/
                return i;
            }
        }

    return i;
}

/*Devuelve el indice en la tabla/ posicion en la tabla*/
int busquedaTablaProfesor(int tabla[], int buscar){
    int i;
    for (i =0; i <400; i++){
        if (tabla[i] == buscar){
            return i;
        }
    }
    return i;
}

/* Ordenar mayor a menor*/
void ordenarMayorAlumnos(int contadorAlumnos[], int id[]){

    int cantidadTotal = 500;
    int aux, auxId;

    for(int z = 1; z < cantidadTotal; ++z) {
      for(int v = 0; v < (cantidadTotal - z); v++) {
         if(contadorAlumnos[v] > contadorAlumnos[v+1]){
            aux = contadorAlumnos[v];
            auxId = id[v];
            contadorAlumnos[v] = contadorAlumnos[v + 1];
            id[v] = id[v+1];
            contadorAlumnos[v + 1] = aux;
            id[v]=auxId;
         }
      }
    }

}