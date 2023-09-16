#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

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

lista_t *lista_crear()
{
	struct lista *lista = calloc(1, sizeof(struct lista));
	return lista != NULL ? lista : NULL;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	return NULL;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	/* 
	if (posicion >= lista->cantidad)
		return lista_insertar(lista, elemento);

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
	if (nuevo_nodo == NULL)
		return NULL;
	nuevo_nodo->elemento = elemento;

	nodo_t *aux = lista->nodo_inicio;
	int i = 0;
	while (i < posicion) {
		aux = lista->nodo_inicio->siguiente;
		i++;
	}
	nuevo_nodo->siguiente = aux->siguiente;
	aux->siguiente = nuevo_nodo;
	lista->cantidad++;
	*/
	return NULL;
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
	return true;
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
