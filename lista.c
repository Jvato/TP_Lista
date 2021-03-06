#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo nodo_t;

struct lista {
	nodo_t* prim;
	nodo_t* ult;
	size_t largo;
};

struct nodo {
	void* dato;
	nodo_t* prox;
};

nodo_t * _nodo_crear(void * dato) {
	nodo_t * nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL){
		return NULL;
	}
	nodo->dato = dato;
	nodo->prox = NULL;
	return nodo;
}

void _nodo_destruir(nodo_t* nodo){
	free(nodo);
}

lista_t * lista_crear(void) {
	lista_t * lista = malloc(sizeof(lista_t));
	if (lista == NULL){
		return NULL;
	}
	lista->prim = NULL;
	lista->ult = NULL;
	lista->largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
	return (lista->largo == 0);
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
	nodo_t * nodo_actual = _nodo_crear(dato);
	if (nodo_actual == NULL){
		return false;
	}
	if (lista_esta_vacia(lista) == true){
		lista->ult = nodo_actual;
	}
	nodo_actual->prox = lista->prim;
	lista->prim = nodo_actual;
	lista->largo++;
	return true;
}


bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t* nodo_nuevo = _nodo_crear(dato);
	if(nodo_nuevo == NULL){
		return false;
	}
	if (lista_esta_vacia(lista)){
		lista->prim = nodo_nuevo;
	}else{
		lista->ult->prox = nodo_nuevo;
	}
	lista->ult = nodo_nuevo;
	lista->largo++;
	return true;
}

void *lista_borrar_primero(lista_t *lista){
	if (lista_esta_vacia(lista) == true){
		return NULL;
	}
	void* dato = lista->prim->dato;
	nodo_t* nodo_aux = lista->prim;
	if (lista_largo(lista) == 1){
		lista->ult = NULL;
	}
	lista->prim = lista->prim->prox;
	lista->largo--;
	_nodo_destruir(nodo_aux);
	return dato;
}


void *lista_ver_primero(const lista_t *lista){
	if (lista_esta_vacia(lista) == true){
		return NULL;
	}
	return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if (lista_esta_vacia(lista) == true){
		return NULL;
	}
	return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
	while(!lista_esta_vacia(lista)){
		void* dato = lista_borrar_primero(lista);
		if(destruir_dato != NULL){
			destruir_dato(dato);
		}
	}
	free(lista);
}

struct lista_iter {
	struct nodo* actual;
	struct nodo* anterior;
	struct lista* lista;
};

lista_iter_t *lista_iter_crear(lista_t *lista) {
	lista_iter_t * iter = malloc(sizeof(lista_iter_t));
	if (iter == NULL){
		return NULL;
	}
	iter->actual = lista->prim;
	iter->anterior = NULL;
	iter->lista = lista;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
	if (lista_iter_al_final(iter) == true){
		return false;
	}
	iter->anterior = iter->actual;
	iter->actual = iter->actual->prox;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
	return (lista_iter_al_final(iter) == true) ? NULL : iter->actual->dato;	
}

bool lista_iter_al_final(const lista_iter_t *iter) {
	return (iter->actual == NULL);
}

void lista_iter_destruir(lista_iter_t *iter) {
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
	if(iter->actual == iter->lista->prim){
		lista_insertar_primero(iter->lista, dato);
		iter->actual = iter->lista->prim;
		iter->anterior = iter->lista->prim;
	}else{
		nodo_t* nodo_nuevo = _nodo_crear(dato);
		if (nodo_nuevo == NULL){
			return false;
		}
		iter->anterior->prox = nodo_nuevo;
		if (lista_iter_al_final(iter) == true){
			iter->lista->ult = nodo_nuevo;
		}else{
			nodo_nuevo->prox = iter->actual;
		}
		iter->actual = nodo_nuevo;
		iter->lista->largo++;
	}
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
	if (lista_iter_al_final(iter) == true){
		return NULL;
	}
	void* dato;
	if (iter->lista->prim == iter->actual){
		dato = lista_borrar_primero(iter->lista);
		iter->actual = iter->lista->prim;
		iter->anterior = iter->lista->prim;
	}else{
		dato = iter->actual->dato;
		nodo_t* a_borrar = iter->actual;
		iter->actual = iter->actual->prox;
		if(iter->actual == NULL){
			iter->lista->ult = iter->anterior;
		}
		iter->anterior->prox = iter->actual;
		_nodo_destruir(a_borrar);
		iter->lista->largo--;
	}
	return dato;
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
	nodo_t* nodo = lista->prim;
	while(nodo != NULL && visitar(nodo->dato, extra)){
		nodo = nodo->prox;
	}
}
