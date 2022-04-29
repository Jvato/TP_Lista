#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo nodo_t;

struct lista {
	nodo_t * prim;
	nodo_t * ult;
	size_t largo;
};

struct nodo {
	void * dato;
	nodo_t * prox;
};

nodo_t * _nodo_crear(void * dato) {
	nodo_t * nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL) return NULL;
	nodo->dato = dato;
	nodo->prox = NULL;
	return nodo;
}

void _nodo_destruir(nodo_t* nodo){
	free(nodo);
}

lista_t * lista_crear(void) {
	lista_t * lista = malloc(sizeof(lista_t));
	if (lista == NULL) return NULL;
	lista->prim = NULL;
	lista->ult = NULL;
	lista->largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
	return (lista->prim == NULL && lista->ult == NULL);
}

// bool lista_insertar_primero(lista_t *lista, void *dato) {
// 	nodo_t * nodo_actual = _nodo_crear(dato);
// 	if (nodo_actual == NULL) return false;
// 	nodo_t * nodo_siguiente = lista->prim;

// }

// No entendi muy bien la implementacion que hiciste de lista_insertar_primero,
// entonces no se si esta bien. Por las dudas deje una implementacion que creo 
// que esta bien :)

bool lista_insertar_primero(lista_t *lista, void *dato) {
	nodo_t * nodo_actual = _nodo_crear(dato);
	if (nodo_actual == NULL) return false;
	nodo_actual->prox = lista->prim;
	if(lista_esta_vacia(lista)){
		lista->prim = nodo_actual;
		lista->ult = nodo_actual;
	}else{
		lista->prim = nodo_actual;
	}
	lista->largo++;
	return true;
}


bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t* nodo_actual = _nodo_crear(dato);
	if(nodo_actual == NULL) return false;
	lista->ult->prox = nodo_actual;
	if(lista_esta_vacia(lista)){
		lista->prim = nodo_actual;
		lista->ult = nodo_actual;
	}else{
		lista->ult = nodo_actual;
	}
	lista->largo++;
	return true;
}

void *lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;

	void* dato = lista->prim->dato;
	nodo_t* nodo_aux = lista->prim;
	if(lista->prim == lista->ult){
		lista->prim = NULL;
		lista->ult = NULL;
		lista->largo = 0;
	}else{
		lista->prim = lista->prim->prox;
		lista->largo--; 
	}
	
	_nodo_destruir(nodo_aux);
	return dato;
}


void *lista_ver_primero(const lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if(lista_esta_vacia(lista)) return NULL;
	return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
	while(!lista_esta_vacia(lista)){
		if(destruir_dato != NULL){
			destruir_dato(lista->prim->dato);
		}
		lista_borrar_primero(lista);
	}
	free(lista);
}

typedef struct lista_iter {
	struct nodo * actual;
	struct nodo * anterior;
	struct lista * lista;
} lista_iter_t;

lista_iter_t *lista_iter_crear(lista_t *lista) {
	lista_iter_t * iter = malloc(sizeof(lista_iter_t));
	if (iter == NULL) return NULL;
	iter->actual = lista->prim;
	iter->anterior = NULL;
	iter->lista = lista;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
	if (lista_iter_al_final(iter) == true)
		return false;
	nodo_t * actual = iter->actual;
	iter->actual = actual->prox;
	iter->anterior = actual;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
	return iter->actual->dato;	
}

bool lista_iter_al_final(const lista_iter_t *iter) {
	return (iter->actual == NULL);
}

void lista_iter_destruir(lista_iter_t *iter) {
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
	nodo_t * nodo_nuevo = _nodo_crear(dato);
	if (nodo_nuevo == NULL) return false;
	if (iter->anterior == NULL) 
		iter->lista->prim = nodo_nuevo;
	else 
		iter->anterior->prox = nodo_nuevo;
	nodo_nuevo->prox = iter->actual;
	iter->actual = nodo_nuevo;
	return true;
}
