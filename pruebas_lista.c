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











/* Pruebas con iterador externo */

void prueba_lista_iterador_externo_crear() {
	lista_t * lista = lista_crear();
	print_test("Se creo una lista vacia",lista != NULL);
	lista_insertar_primero(lista,"TP1");
	lista_iter_t * iter = lista_iter_crear(lista);
	print_test("Se creo un iterador externo",iter != NULL);
	lista_destruir(lista,NULL);
	lista_iter_destruir(iter);
}

void prueba_lista_iterador_externo_crear_apunta_al_inicio() {
	lista_t * lista = lista_crear();
	print_test("Se creo una lista vacia",lista != NULL);
	int dato[1];
	print_test("Se inserto un elemento en la lista",lista_insertar_primero(lista,dato) == true);
	lista_iter_t * iter = lista_iter_crear(lista);
	print_test("Se creo un iterador externo",iter != NULL);
	print_test("El iterador apunta al primer elemento de la lista", lista_iter_ver_actual(iter) == dato);
	lista_iter_destruir(iter);	
	lista_destruir(lista,NULL);
}

void prueba_lista_iterador_externo_recorrer_lista() {
	lista_t * lista = lista_crear();
	int v[10];
	for (size_t i = 0; i < 9; i++) {
		if (lista_insertar_ultimo(lista,v+i) == false)
			return;
	}
	print_test("Se creo una lista con 10 elementos",lista_insertar_ultimo(lista,v+9) == true);
	lista_iter_t * iter = lista_iter_crear(lista);
	print_test("Se creo un iterado y apunta al primer elemento de la lista", iter != NULL);
	for (size_t i = 0; i < 9; i++) {
		if (lista_iter_ver_actual(iter) != v+i) {
			lista_iter_destruir(iter);
			lista_destruir(lista,NULL);
			return;
		}
		lista_iter_avanzar(iter);
	}
	print_test("Lo datos obtenidos con el iterador coinciden con los cargados en la lista",lista_iter_ver_actual(iter) == v+9);
	lista_iter_destruir(iter);
	lista_destruir(lista,NULL);
}

void prueba_lista_iterador_externo_esta_al_final() {
	lista_t * lista = lista_crear();
	int v[10];
	for (size_t i = 0; i < 9; i++) {
		if (lista_insertar_ultimo(lista,v+i) == false) {
			lista_destruir(lista,NULL);
			return;
		}
	}
	print_test("Se creo una lista con 10 elementos",lista_insertar_ultimo(lista,v+9) == true);
	lista_iter_t * iter = lista_iter_crear(lista);
	for (size_t i = 0; i < 8; i++) {
		if (lista_iter_al_final(iter) == true) {
			lista_iter_destruir(iter);
			lista_destruir(lista,NULL);
			return;
		}
	}
	print_test("Se recorrio la lista por 9 elementos y el iterador esta aun no llega al final", lista_iter_al_final(iter) == false);
	lista_iter_destruir(iter);
	lista_destruir(lista,NULL);

}

void pruebas_lista_estudiante(){
	puts("PRUEBA DE LISTA VACIA");
   	prueba_lista_vacia();

	puts("PRUEBA DE LISTA CARGAR NUMEROS");
   	prueba_listar_numeros();

	puts("PROBAR QUE SE PUEDE CREAR UN ITERADOR EXTERNO");
	prueba_lista_iterador_externo_crear();

	puts("PROBAR QUE EL ITERADOR CREADO APUNTA AL INICIO DE LA LISTA");
    	prueba_lista_iterador_externo_crear_apunta_al_inicio();

	puts("PROBAR QUE EL ITERADOR MUESTRA LOS MISMO DATOS DE UNA LISTA CUANDO SE RECORRE CON UN ITERADOR");
    	prueba_lista_iterador_externo_recorrer_lista();

	prueba_lista_iterador_externo_esta_al_final();








}


#ifndef CORRECTOR

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;
}

#endif
