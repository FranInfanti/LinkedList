#include "cola.h"
#include "lista.h"

struct _cola_t {
	struct nodo *nodo_inicio;
	struct nodo *nodo_fin;
	size_t cantidad;
};

cola_t *cola_crear()
{
	return calloc(1, sizeof(struct _cola_t));
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	void *cola_aux = lista_insertar((void *)cola, elemento);
	if (cola_aux == NULL)
		return NULL;

	cola = cola_aux;
	return cola;
}

void *cola_desencolar(cola_t *cola)
{
	return lista_quitar_de_posicion((void *)cola, 0);
}

void *cola_frente(cola_t *cola)
{
	return lista_primero((void *)cola);
}

size_t cola_tamanio(cola_t *cola)
{
	return lista_tamanio((void *)cola);
}

bool cola_vacia(cola_t *cola)
{
	return lista_vacia((void *)cola);
}

void cola_destruir(cola_t *cola)
{
	lista_destruir((void *)cola);
}
