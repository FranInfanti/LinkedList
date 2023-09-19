#include "pila.h"
#include "lista.h"

struct _pila_t {
	struct nodo *nodo_principio;
	struct nodo *nodo_tope;
	size_t cantidad;
};

pila_t *pila_crear()
{	struct _pila_t *pila = calloc(1, sizeof(struct _pila_t));
	return pila != NULL ? pila : NULL;
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	void* pila_aux = lista_insertar((void*)pila, elemento);
	if (pila_aux == NULL)
		return NULL;

	pila = pila_aux;
	return pila;
}

void *pila_desapilar(pila_t *pila)
{
	return lista_quitar((void*)pila);
}

void *pila_tope(pila_t *pila)
{
	return lista_ultimo((void*)pila);
}

size_t pila_tamanio(pila_t *pila)
{
	return pila == NULL ? 0 : pila->cantidad;
}

bool pila_vacia(pila_t *pila)
{
	if (pila == NULL)
		return true;
	return pila->cantidad == 0;
}

void pila_destruir(pila_t *pila)
{
	lista_destruir((void*)pila);
}
