#ifdef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

struct lista
typedef struct lista lista_t

// Crea una lista
// Post: devuelve una lista vacia
lista_t *lista_crear(void);

// Verifica si la lista esta vacia
// devuelve true si la lista no tiene elementos y false en caso contrario
// Pre: la lista fue creada
bool lista_esta_vacia(const lista_t *lista);

// Agrega un elemento en la primera posicion de la lista
// Pre: la lista esta creada
// Pos: se agrego un nuevo elemento a la lista, este elemento es el primero
bool lista_insertar_primero(lista_t *lista, void *dato);
bool lista_insertar_ultimo(lista_t *lista, void *dato);
void *lista_borrar_primero(lista_t *lista);
void *lista_ver_primero(const lista_t *lista);
void *lista_ver_ultimo(const lista_t* lista);
size_t lista_largo(const lista_t *lista);
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));



#endif
