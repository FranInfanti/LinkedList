#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#define PRIMERA_POSICION 0

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_fin;
	size_t cantidad;
};

struct lista_iterador {
	//y acá?
	int sarasa;
};

/*
 * Crea un nodo con todos sus campos inicializados en 0. Y luego 
 * le asigna el valor de void* elemento. 
 */
struct nodo *crear_nodo(void* elemento)
{
	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
	if (nuevo_nodo == NULL)
		return NULL;
	nuevo_nodo->elemento = elemento;
	return nuevo_nodo;
}

/*
 * Crea un nuevo nodo con la informacion de elemento, y lo inserta en la primera posicion.
 */
struct lista *insertar_primera_posicion(struct lista *lista, void* elemento)
{
	nodo_t *nuevo_nodo = crear_nodo(elemento);
	if (nuevo_nodo == NULL)
		return NULL;

	nuevo_nodo->siguiente = lista->nodo_inicio;
	lista->nodo_inicio = nuevo_nodo;
	lista->cantidad++;
	return lista;
}

/*
 * 
 */
nodo_t *recorrer_hasta_posicion(struct lista *lista, size_t posicion)
{
	nodo_t *aux = lista->nodo_inicio;
	void* ptr = NULL;
	int i = 1;
	while (i < posicion) {
		ptr = aux->siguiente;
		aux = ptr;
		i++;
	}	
	return aux;
}

lista_t *lista_crear()
{
	struct lista *lista = calloc(1, sizeof(struct lista));
	return lista != NULL ? lista : NULL;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (lista == NULL)
		return NULL;
		
	nodo_t *nuevo_nodo = crear_nodo(elemento);
	if (nuevo_nodo == NULL)
		return NULL;

	if (lista->cantidad == 0) {
		lista->nodo_inicio = nuevo_nodo;
		lista->nodo_fin = nuevo_nodo;
	} else {
		lista->nodo_fin->siguiente = nuevo_nodo;
		lista->nodo_fin = nuevo_nodo;	
	}
	lista->cantidad++;
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (lista == NULL)
		return NULL;

	if (posicion >= lista->cantidad)
		return lista_insertar(lista, elemento);
	
	if (posicion == PRIMERA_POSICION)
		return insertar_primera_posicion(lista, elemento);

	nodo_t *nuevo_nodo = crear_nodo(elemento);
	if (nuevo_nodo == NULL)
		return NULL;

	nodo_t *aux = recorrer_hasta_posicion(lista, posicion);
	nuevo_nodo->siguiente = aux->siguiente;
	aux->siguiente = nuevo_nodo;
	lista->cantidad++;
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	return NULL;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	return lista != NULL && lista->cantidad != 0 ? lista->nodo_inicio->elemento : NULL;
}

void *lista_ultimo(lista_t *lista)
{
	return lista != NULL && lista->cantidad != 0 ? lista->nodo_fin->elemento : NULL;
}

bool lista_vacia(lista_t *lista)
{
	if (lista == NULL)
		return true;
	return lista->cantidad == 0 ? true : false;
}

size_t lista_tamanio(lista_t *lista)
{
	return lista != NULL ? lista->cantidad : 0;
}

void lista_destruir(lista_t *lista)
{
	if (lista != NULL) {
		int n = 0;
		nodo_t *aux = lista->nodo_inicio;
		void* ptr = NULL;
		while (n < lista->cantidad) {
			ptr = aux->siguiente;
			free(aux);
			aux = ptr;
			n++;
		}
		free(lista);	
	}
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}
