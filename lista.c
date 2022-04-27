#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo {
	void * dato;
	struct nodo * prox;
} nodo_t;

typedef struct lista {
	struct nodo * prim;
	struct nodo * ult;
	size_t largo;
} lista_t;


nodo_t * _nodo_crear(void * dato) {
	nodo_t * nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL) return NULL;
	nodo->dato = dato;
	nodo->prox = NULL;
	return nodo;
}
lista_t * lista_crear(void) {
	lista_t * lista = malloc(sizeof(lista_t));
	if (lista == NULL) return NULL;
	lista->prim = NULL;
	lista->ult = NULL;
	return lista;
}

bool lista_esta_vacia(lista_t * lista) {
	return (lista->prim == NULL && lista->ult == NULL);
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
	nodo_t * nodo_actual = _nodo_crear(dato);
	if (nodo_actual == NULL) return false;
	nodo_t * nodo_siguiente = lista->prim;

}
