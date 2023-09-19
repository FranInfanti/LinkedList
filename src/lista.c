#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#define PRIMERA_POSICION 0
#define NO_HAY_NODOS 0

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
 * le asigna el valor de elemento. 
 */
struct nodo *crear_nodo(void *elemento)
{
	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
	if (nuevo_nodo == NULL)
		return NULL;
	nuevo_nodo->elemento = elemento;
	return nuevo_nodo;
}

/*
 * Recorre los nodos hasta la posicion indicada y devuelve el nodo de dicha posicion.
 */
nodo_t *recorrer_hasta_posicion(struct lista *lista, size_t posicion)
{
	nodo_t *nodo = lista->nodo_inicio;
	void *aux = NULL;
	int i = 0;
	while (i != posicion) {
		aux = nodo->siguiente;
		nodo = aux;
		i++;
	}
	return nodo;
}

/*
 * Libera toda la memoria ocupada por los nodos. Ademas si aplico_funcion es true,
 * se le aplica la funcion a todos los elementos antes de ser eliminados.
 */
void destruir_nodos(nodo_t *eliminar, size_t cantidad, bool aplico_funcion,
		    void (*f)(void *))
{
	int n = 0;
	void *aux = NULL;
	while (n < cantidad) {
		if (aplico_funcion && f != NULL)
			f(eliminar->elemento);
		aux = eliminar->siguiente;
		free(eliminar);
		eliminar = aux;
		n++;
	}
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

	if (lista->cantidad == 0) 
		lista->nodo_inicio = nuevo_nodo;
	else
		lista->nodo_fin->siguiente = nuevo_nodo;

	lista->nodo_fin = nuevo_nodo;
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

	nodo_t *nuevo_nodo = crear_nodo(elemento);
	if (nuevo_nodo == NULL)
		return NULL;

	nodo_t *anterior = NULL;

	if (posicion == PRIMERA_POSICION) {
		nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo;		
	} else {
		anterior = recorrer_hasta_posicion(lista, posicion - 1);
		nuevo_nodo->siguiente = anterior->siguiente;
		anterior->siguiente = nuevo_nodo;		
	}
	lista->cantidad++;

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (lista == NULL)
		return NULL;

	if (lista->cantidad == 0)
		return NULL;

	nodo_t *nodo_removido = lista->nodo_fin;
	void *elemento_removido = nodo_removido->elemento;
	free(nodo_removido);
	lista->cantidad--;

	if (lista->cantidad == 0) {
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;	
	} else {
		nodo_t *ultimo_nodo = recorrer_hasta_posicion(lista, lista->cantidad - 1);
		ultimo_nodo->siguiente = NULL;
		lista->nodo_fin = ultimo_nodo;		
	}

	return elemento_removido;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL)
		return NULL;

	if (lista->cantidad == 0)
		return NULL;

	if (posicion >= lista->cantidad-1)
		return lista_quitar(lista);
	
	nodo_t *nodo_removido = NULL;

	if (posicion == PRIMERA_POSICION) {
		nodo_removido = lista->nodo_inicio;
		lista->nodo_inicio = nodo_removido->siguiente;
	} else {
		nodo_t *anterior = recorrer_hasta_posicion(lista, posicion-1);
		nodo_removido = anterior->siguiente;
		anterior->siguiente = nodo_removido->siguiente;
	}
	
	void* elemento_removido = nodo_removido->elemento;
	free(nodo_removido);
	lista->cantidad--;		

	return elemento_removido;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL)
		return NULL;
	if (lista->cantidad <= posicion)
		return NULL;

	nodo_t *buscado = recorrer_hasta_posicion(lista, posicion);
	return buscado->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (lista == NULL || comparador == NULL || lista->cantidad == 0)
		return NULL;

	nodo_t *buscado = lista->nodo_inicio;
	void *aux = NULL;
	int i = 0;
	while ((i < lista->cantidad) &&
	       comparador(buscado->elemento, contexto)) {
		aux = buscado->siguiente;
		buscado = aux;
		i++;
	}
	return i < lista->cantidad ? buscado->elemento : NULL;
}

void *lista_primero(lista_t *lista)
{
	if (lista == NULL || lista->cantidad == 0)
		return NULL;
	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (lista == NULL || lista->cantidad == 0)
		return NULL;
	return lista->nodo_fin->elemento;
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
		destruir_nodos(lista->nodo_inicio, lista->cantidad, false,
			       NULL);
		free(lista);
	}
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (lista != NULL) {
		destruir_nodos(lista->nodo_inicio, lista->cantidad, true,
			       funcion);
		free(lista);
	}
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
