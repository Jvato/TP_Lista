#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

static void prueba_lista_vacia(void){
    printf("INICIO DE LAS PRUEBAS CON LISTA VACIA\n");
    lista_t* lista = lista_crear();

    print_test("La lista esta vacia", lista_esta_vacia(lista) == true);
    print_test("Borrar el primer elemento de la lista da NULL", lista_borrar_primero(lista) == NULL);
    print_test("Ver el primer elemento de la lista devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("Ver el ultimo elemento de la lista devuelve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Ver el largo de la lista es 0", lista_largo(lista) == 0);

    lista_destruir(lista, NULL);
}

static void prueba_listar_numeros(void){
    printf("INICIO DE LAS PRUEBAS DE LISTAR ALGUNOS NUMEROS\n");
    lista_t* lista = lista_crear();

    int i = 1;
    int x = 2;
    int y = 3;

    print_test("Insertar un 1 al comienzo es posible", lista_insertar_primero(lista, &i) == true);
    print_test("La lista no esta vacia", lista_esta_vacia(lista) == false);
    print_test("El primero de la lista es 1", *(int*)lista_ver_primero(lista) == 1);
    print_test("El ultimo de la lista es 1", *(int*)lista_ver_ultimo(lista) == 1);
    print_test("Insertar un 2 al final es posible", lista_insertar_ultimo(lista, &x) == true);
    print_test("El primero de la lista sigue siendo 1", *(int*)lista_ver_primero(lista) == 1);
    print_test("El ultimo de la lista es 2", *(int*)lista_ver_ultimo(lista) == 2);
    print_test("Insertar un 3 al comienzo es posible", lista_insertar_primero(lista, &y) == true);
    print_test("El primero de la lista es 3", *(int*)lista_ver_primero(lista) == 3);
    print_test("El ultimo de la lista sigue siendo 2", *(int*)lista_ver_ultimo(lista) == 2);
    print_test("El largo de la lista es 3", lista_largo(lista) == 3);
    
    lista_destruir(lista, NULL);
}


void pruebas_lista_estudiante(){
    prueba_lista_vacia();
    prueba_listar_numeros();
}


#ifndef CORRECTOR

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;
}

#endif