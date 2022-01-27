#include "pila.h"
#include "testing.h"
#include <stdio.h>

/*****FUNCION AUXILIAR PARA COMPROBAR QUE SE GUARDA LA CADENA COMPLETA*****/
bool comparar_cadena(char cadena1[], char cadena2[], int len){
    for (int i = 0; i < len; i++){
        if (cadena1[i] != cadena2[i]){
            return false;
        }
    }
    return true;
}
/**************************************************************************/

static void prueba_pila_vacia(void) {
    pila_t *pila = pila_crear();

    /*  La pila está vacía  */
    print_test("La pila está vacía", pila_esta_vacia(pila));
    print_test("No hay tope", pila_ver_tope(pila) == NULL);
    print_test("Desapilar devuelve NULL por estar vacia", pila_desapilar(pila) == NULL);

    /*  La pila no está vacía  */
    int i = 2;
    pila_apilar(pila, &i);
    print_test("Agrego un elemento y deja de estar vacia", !pila_esta_vacia(pila));

    pila_destruir(pila);
}

static void prueba_algunos_elementos(void){
    pila_t *pila = pila_crear();

    int numeros[] = {3,2,1};
    char cadena_1[] = "algoritmos";
    int len_1 = 10;
    char cadena_2[] = "programacion";
    int len_2 = 12;

    /* Pruebo que se apilan los elementos  */
    print_test("Se apila el numero 3", pila_apilar(pila, &numeros[0]));
    print_test("Se apila 'algoritmos'", pila_apilar(pila, &cadena_1));
    print_test("Se apila el numero 2", pila_apilar(pila, &numeros[1]));
    print_test("Se apila el numero 1", pila_apilar(pila, &numeros[2]));
    print_test("Apilar NULL es valido", pila_apilar(pila, NULL));
    print_test("Se apila 'programacion'", pila_apilar(pila, &cadena_2));

    char * tope_cadena = pila_ver_tope(pila);
    print_test("El tope es 'programacion'", comparar_cadena(tope_cadena, cadena_2, len_2));

    printf("Comienzo a desapilar\n");

    char *desapilar_cadena = pila_desapilar(pila);
    print_test("Desapilar devuelve 'programacion'", comparar_cadena(tope_cadena, cadena_2, len_2));

    print_test("Ahora el tope es NULL", pila_ver_tope(pila) == NULL);
    print_test("Desapilar devuelve NULL", pila_desapilar(pila) == NULL);

    int *tope_entero = pila_ver_tope(pila);
    print_test("Ahora el tope es 1", *tope_entero == numeros[2]);

    int *desapilar_entero = pila_desapilar(pila);
    print_test("Desapilar devuelve 1", *desapilar_entero == numeros[2]);

    tope_entero = pila_ver_tope(pila);
    print_test("Ahora el tope es 2", *tope_entero == numeros[1]);

    desapilar_entero = pila_desapilar(pila);
    print_test("Desapilar devuelve '2'", *desapilar_entero == numeros[1]);

    tope_cadena = pila_ver_tope(pila);
    print_test("Ahora el tope es 'algoritmos'", comparar_cadena(tope_cadena, cadena_1, len_1));

    desapilar_cadena = pila_desapilar(pila);
    print_test("Desapilar devuelve 'algoritmos'", comparar_cadena(desapilar_cadena, cadena_1, len_1));

    desapilar_entero = pila_desapilar(pila);
    print_test("Desapilar devuelve 3", *desapilar_entero == numeros[0]);

    print_test("No hay tope", pila_ver_tope(pila) == NULL);
    print_test("Desapilar devuelve NULL por estar vacia", pila_desapilar(pila) == NULL);

    printf("La pila queda como recien creada\n");
    print_test("Se puede volver apilar elementos", pila_apilar(pila, &numeros[0]));

    pila_destruir(pila);
}

static void prueba_dinamismo(void){
    pila_t *pila = pila_crear();

    /*  Creo un vector de 1000 elementos diferentes  */
    int numeros[1000];
    for (int i = 0; i < 1000; i++){
        numeros[i] = i;
    }    

    printf("Apilo mil elementos\n");
    /*  Apilo todos los elementos  */
    for (int j = 0; j < 1000; j++){
        pila_apilar(pila, &numeros[j]);
    }

    int *tope;
    int *desapilar;
    for (int r = 1000; r > 0; r--)
    {
        printf("El tope es %i\n", r);
        tope = pila_ver_tope(pila);
        print_test("Tope correcto", *tope == numeros[r - 1]);

        printf("Se desapila %i\n", r);
        desapilar = pila_desapilar(pila);
        print_test("Desapilado correcto", *desapilar == numeros[r - 1]);
    }
    print_test("La pila esta vacia", pila_esta_vacia(pila));

    pila_destruir(pila);
}


void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_algunos_elementos();
    prueba_dinamismo();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
