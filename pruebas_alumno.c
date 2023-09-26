#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"
#include "pa2m.h"
#include <stdbool.h>
#include <stdlib.h>

void puedo_crear_una_lista() 
{
        lista_t *lista = lista_crear();
        pa2m_afirmar(lista != NULL, "Puedo crear una lista correctamente");
        lista_destruir(lista);
}

void una_lista_recien_creada_tiene_cero_elementos()
{
        lista_t *lista = lista_crear();
        pa2m_afirmar(lista_tamanio(lista) == 0, "El tamaño de la lista recien creada es 0");
        lista_destruir(lista);
}

void los_punteros_de_una_lista_recien_creada_apuntan_a_null() 
{
        lista_t *lista = lista_crear();
        pa2m_afirmar(lista_primero(lista) == NULL, "nodo_incio apunta a NULL con una lista recien creada");
        pa2m_afirmar(lista_ultimo(lista) == NULL, "nodo_incio apunta a NULL con una lista recien creada");
        lista_destruir_todo(lista, NULL);
}

void no_puedo_insertar_con_lista_nula()
{
        lista_t *lista = NULL;
        int elemento = 33;
        pa2m_afirmar(lista_insertar(lista, &elemento) == NULL, "No se puede insertar elementos al final de una lista nula");
        lista_destruir(lista);
}

void puedo_insertar_un_elemento_nulo()
{
        lista_t *lista = lista_crear();
        lista = lista_insertar(lista, NULL);
        pa2m_afirmar(lista_ultimo(lista) == NULL, "Se puede insertar un elemento nulo");
        lista_destruir(lista);
}

void se_inserta_un_elemento_en_el_final_correctamente()
{
        lista_t *lista = lista_crear();
        int insertar;
        lista = lista_insertar(lista, &insertar);
        pa2m_afirmar(lista_ultimo(lista) == &insertar, "El elemento insertado en el final es correcto");
        lista_destruir(lista);
}

void no_se_puede_insertar_en_posiciones_aleatorias_en_una_lista_nula() 
{
        lista_t *lista = NULL;
        int numero;
        pa2m_afirmar(lista_insertar_en_posicion(lista, &numero, 2) == NULL, "No se puede insertar elementos en posiciones arbitrarias en una lista nula");       
}

void se_puede_insertar_en_posiciones_aleatorias()
{
        lista_t *lista = lista_crear();
        int numeros[] = {1, 2, 3, 4};
        for (int n = 0; n < sizeof(numeros) / sizeof(int); n++)
                lista = lista_insertar(lista, &numeros[n]);

        int nuevo_numero;
        lista = lista_insertar_en_posicion(lista, &nuevo_numero, 2);
        pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == &nuevo_numero, "Se puede insertar elementos en posiciones aleatorias correctamente");
        lista_destruir(lista);
}

void inserto_un_elemento_en_una_posicion_que_no_existe_y_se_inserta_al_final()
{
        lista_t *lista = lista_crear();
        int numeros[] = {1, 2, 3, 4};
        for (int n = 0; n < sizeof(numeros) / sizeof(int); n++)
                lista = lista_insertar(lista, &numeros[n]);

        int nuevo_numero;
        lista = lista_insertar_en_posicion(lista, &nuevo_numero, 24654);
        pa2m_afirmar(lista_ultimo(lista) == &nuevo_numero, "Inserto en una posicion que no existe y se inserta al final");
        lista_destruir(lista);       
}

void no_se_puede_eliminar_elementos_de_una_lista_nula()
{
        lista_t *lista = NULL;
        pa2m_afirmar(lista_quitar(lista) == NULL, "No se puede quitar elementos de una lista nula");
}

void se_pueden_eliminar_elementos_de_final_de_una_lista()
{
        lista_t *lista = lista_crear();
        int numeros[] = {1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
                lista = lista_insertar(lista, &numeros[i]);
        pa2m_afirmar(lista_quitar(lista) == &numeros[7], "Se puede eliminar elementos de la ultima posicion y son correctos");
        lista_destruir(lista);
}

void se_pueden_eliminar_todos_los_elementos_de_una_lista()
{
        lista_t *lista = lista_crear();
        int numeros[] = {1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
                lista = lista_insertar(lista, &numeros[i]);
        while (!lista_vacia(lista)) {
                lista_quitar(lista);
        }
        pa2m_afirmar(lista_tamanio(lista) == 0, "Se eliminan todos los elementos y la lista queda vacia");
        lista_destruir(lista);      
}

void no_se_pueden_eliminar_elementos_en_posiciones_aleatorias_de_una_lista_nula()
{
        lista_t *lista = NULL;
        pa2m_afirmar(lista_quitar_de_posicion(lista, 45) == NULL, "No se puede quitar elementos de una lista nula");
}

void se_pueden_eliminar_elementos_en_posiciones_aleatorias()
{
        lista_t *lista = lista_crear();
        int numeros[] = {1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
                lista = lista_insertar(lista, &numeros[i]);  
        pa2m_afirmar(lista_quitar_de_posicion(lista, 5) == &numeros[5], "Se puede eliminar el elemento de una posicion arbitraria correctamente");
        lista_destruir(lista);
}

void no_se_puede_elimina_elementos_de_una_lista_vacia()
{
        lista_t *lista = lista_crear();
        pa2m_afirmar(lista_quitar(lista) == NULL, "No puedo eliminar elementos del final de una lista vacia");
        lista_destruir(lista);
}

void no_se_puede_eliminar_elementos_en_posiciones_aleatorias_de_una_lista_vacia()
{
        lista_t *lista = lista_crear();
        pa2m_afirmar(lista_quitar_de_posicion(lista, 5) == NULL, "No puedo eliminar elementos del final de una lista vacia");
        lista_destruir(lista);      
}

void elimino_en_una_posicion_que_no_existe_y_se_elimina_el_ultimo()
{
        lista_t *lista = lista_crear();
        int numeros[] = {1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
                lista = lista_insertar(lista, &numeros[i]);  
        pa2m_afirmar(lista_quitar_de_posicion(lista, 654654) == &numeros[7], "Elimino el elemento de una posicion que no existe y se elimina el ultimo");
        lista_destruir(lista);       
}

void no_puedo_buscar_elementos_en_una_posicion_en_una_lista_nula()
{
        lista_t *lista = NULL;
        pa2m_afirmar(lista_elemento_en_posicion(lista, 4) == NULL, "No puedo buscar un elemento en una poscion en una lista nula");
}

void no_puedo_buscar_elementos_en_una_posicion_en_una_lista_vacia()
{
        lista_t *lista = lista_crear();
        pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL, "No puedo buscar un elemento segun su posicionen una lista vacica");
        lista_destruir(lista);
}

void busco_en_una_posicion_un_elemento_y_lo_encuentro()
{
        lista_t *lista = lista_crear();
        int numeros[] = {1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
                lista = lista_insertar(lista, &numeros[i]);  
        pa2m_afirmar(lista_elemento_en_posicion(lista, 4) == &numeros[4], "Busco un elemento segun su posicion y lo encuentro");
        lista_destruir(lista);       
}

void busco_un_elemento_en_una_posicion_que_no_existe_y_no_lo_encuentro()
{
        lista_t *lista = lista_crear();
        int numeros[] = {1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
                lista = lista_insertar(lista, &numeros[i]);  
        pa2m_afirmar(lista_elemento_en_posicion(lista, 40) == NULL, "Busco un elemento en una posicion que no existe y no lo encuentro");
        lista_destruir(lista);        
}

void si_la_funcion_es_null_no_se_le_aplica_a_ningun_elemento()
{
        lista_t *lista = lista_crear();
        int numeros[] = {1, 2, 3, 4, 5, 6};
        for (int i = 0; i < sizeof(numeros) / sizeof(int); i++) 
                lista = lista_insertar(lista, &numeros[i]);
        pa2m_afirmar(lista_con_cada_elemento(lista, NULL, &numeros[5]) == 0, "No se puede aplicar una funcion NULL");
        lista_destruir(lista);
}

bool es_el_buscado(void* numero, void* buscado)
{
        return numero != buscado;
}

void puedo_aplicarle_la_funcion_a_todos_los_elementos_de_la_lista()
{
        lista_t *lista = lista_crear();
        int numeros[] = {1, 2, 3, 4, 5, 6};
        for (int i = 0; i < sizeof(numeros) / sizeof(int) -1; i++) 
                lista = lista_insertar(lista, &numeros[i]);
        pa2m_afirmar(lista_con_cada_elemento(lista, es_el_buscado, &numeros[5]) == 5, "Se le aplica la funcion a todos los elementos");
        lista_destruir(lista);
}

void puedo_aplicarle_la_funcion_a_algunos_los_elementos_de_la_lista()
{
        lista_t *lista = lista_crear();
        int numeros[] = {1, 2, 3, 4, 5, 6};
        for (int i = 0; i < sizeof(numeros) / sizeof(int); i++) 
                lista = lista_insertar(lista, &numeros[i]);
        pa2m_afirmar(lista_con_cada_elemento(lista, es_el_buscado, &numeros[1]) == 2, "Se le aplica la funcion a algunos elementos");
        lista_destruir(lista);
}

void no_puedo_crear_un_it_con_una_lista_nula()
{
        lista_iterador_t *it = lista_iterador_crear(NULL);
        pa2m_afirmar(it == NULL, "No puedo crear un iterador externo con una lista nula");
}

void puedo_crear_un_it_externo()
{
        lista_t *lista = lista_crear();
        lista_iterador_t *it = lista_iterador_crear(lista);
        pa2m_afirmar(it != NULL, "Puedo crear un iterador externo con una lista no nula");
        lista_iterador_destruir(it);
        lista_destruir(lista);
}

void creo_un_it_externo_y_apunta_al_primer_elemento_de_la_lista()
{
        lista_t *lista = lista_crear();
        int numero;
        int otro_numero;
        lista = lista_insertar(lista, &numero);
        lista = lista_insertar(lista, &otro_numero);
        lista_iterador_t *it = lista_iterador_crear(lista);
        pa2m_afirmar(lista_iterador_elemento_actual(it) == &numero, "Creo un iterador externo y este apunta al primer elemento de la lista");
        lista_iterador_destruir(it);
        lista_destruir(lista);
}

void no_puedo_recorrer_una_lista_vacia()
{
        lista_t *lista = lista_crear();
        lista_iterador_t *it = lista_iterador_crear(lista);
        pa2m_afirmar(lista_iterador_avanzar(it) == false, "No puedo avanzar con una lista vacia");
        pa2m_afirmar(lista_iterador_tiene_siguiente(it) == false, "No puedo avanzar con una lista vacia");
        lista_iterador_destruir(it);
        lista_destruir(lista);     
}

void puedo_recorrer_una_lista()
{
        lista_t *lista = lista_crear();
        int numeros[] = {1, 2, 3, 4, 5};
        for (int i = 0; i < sizeof(numeros) / sizeof(int); i++) 
                lista = lista_insertar(lista, &numeros[i]);
        lista_iterador_t *it = lista_iterador_crear(lista);
        size_t elementos_recorridos = 0;
        while (lista_iterador_tiene_siguiente(it)) {
                lista_iterador_avanzar(it);
                elementos_recorridos++;
        }
        pa2m_afirmar(elementos_recorridos == 5, "Se recorrieron todos los elementos de la lista");
        lista_iterador_destruir(it);
        lista_destruir(lista);        
}

void puedo_crear_una_cola()
{
        cola_t *cola = cola_crear();
        pa2m_afirmar(cola != NULL, "Puedo crear una cola");
        cola_destruir(cola);
}

void no_puedo_encolar_un_elemento_en_una_cola_nula()
{
        cola_t *cola = NULL;
        pa2m_afirmar(cola_encolar(cola, NULL) == NULL, "No puedo encolar en una cola nula");
}

void puedo_encolar_un_elemento()
{
        cola_t *cola = cola_crear();
        int numero;
        cola = cola_encolar(cola, &numero);
        pa2m_afirmar(cola_frente(cola) == &numero, "Se puede encolar un elemento en la cola y es correcto");
        cola_destruir(cola);
}

void puedo_desencolar_un_elemento()
{
        cola_t *cola = cola_crear();
        int numero;
        cola = cola_encolar(cola, &numero);
        void* elemento = cola_desencolar(cola);
        pa2m_afirmar(cola_tamanio(cola) == 0 && elemento == &numero, "Se puede desencolar un elemento en la cola y es correcto");
        cola_destruir(cola);  
}

void puedo_encolar_varios_elementos()
{
        cola_t *cola = cola_crear();
        int numeros[] = {1, 2, 3, 4};
        for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
                cola = cola_encolar(cola, &numeros[i]);
        pa2m_afirmar(cola_tamanio(cola) == 4, "Se encolaron todos los elementos correctamente");
        cola_destruir(cola); 
}

void puedo_desencolar_todos_los_elementos()
{
        cola_t *cola = cola_crear();
        int numeros[] = {1, 2, 3, 4};
        for (int i = 0; i < 4; i++) 
                cola = cola_encolar(cola, &numeros[i]);
        int i = 0;
        while (!cola_vacia(cola)) {
                pa2m_afirmar(cola_desencolar(cola) == &numeros[i], "El elemento desencolado es correcto");
                i++;
        }
        pa2m_afirmar(cola_tamanio(cola) == 0, "Se desencolaron todos los elementos");
        cola_destruir(cola);
}

void puedo_crear_una_pila()
{
        pila_t *pila = pila_crear();
        pa2m_afirmar(pila != NULL, "Puedo crear una pila correctamente");
        pila_destruir(pila);
}

void no_puedo_apilar_en_una_pila_nula()
{
        pila_t *pila = NULL;
        pa2m_afirmar(pila_apilar(pila, NULL) == NULL, "No se puede apilar en una pila nula");
}

void puedo_apilar_un_elemento()
{
        pila_t *pila = pila_crear();
        pila = pila_apilar(pila, NULL);
        pa2m_afirmar(pila_tope(pila) == NULL, "El elemento apilado es correcto");
        pa2m_afirmar(pila_tamanio(pila) == 1, "El tamaño de la pila es correcto");
        pila_destruir(pila);     
}

void puedo_desapilar_un_elemento()
{
        pila_t *pila = pila_crear();
        pila = pila_apilar(pila, NULL);
        pa2m_afirmar(pila_desapilar(pila) == NULL, "Puedo desapilar un elemento correctamente");
        pa2m_afirmar(pila_tamanio(pila) == 0, "La pila queda vacia");
        pila_destruir(pila);             
}

void puedo_apilar_varios_elementos()
{
        pila_t *pila = pila_crear();
        int numeros[] = {1, 2, 3, 4};
        for (int i = 0; i < 4; i++) {
                pila = pila_apilar(pila, &numeros[i]);
                pa2m_afirmar(pila != NULL, "Puedo apilar un elemento");
        }
        pa2m_afirmar(pila_tamanio(pila) == 4, "La cantidad de elementos insertada es correcta");
        pila_destruir(pila);
}

void puedo_desapilar_todos_los_elementos()
{
        pila_t *pila = pila_crear();
        int numeros[] = {1, 2, 3, 4};
        for (int i = 0; i < 4; i++) 
                pila = pila_apilar(pila, &numeros[i]);
        int i = 3;
        while(!pila_vacia(pila)) {
                pa2m_afirmar(pila_desapilar(pila) == &numeros[i], "El elemento desapilado es correcto");
                i--;
        }
        pa2m_afirmar(pila_tamanio(pila) == 0, "La pila esta vacia");
        pila_destruir(pila);
}

int main()
{
        pa2m_nuevo_grupo("Pruebas de crear una Lista");
        puedo_crear_una_lista(); 
        una_lista_recien_creada_tiene_cero_elementos(); 
        los_punteros_de_una_lista_recien_creada_apuntan_a_null(); 

        pa2m_nuevo_grupo("Pruebas de insertar en la Lista");
        no_puedo_insertar_con_lista_nula(); 
        puedo_insertar_un_elemento_nulo(); 
        se_inserta_un_elemento_en_el_final_correctamente(); 
        no_se_puede_insertar_en_posiciones_aleatorias_en_una_lista_nula(); 
        se_puede_insertar_en_posiciones_aleatorias(); 
        inserto_un_elemento_en_una_posicion_que_no_existe_y_se_inserta_al_final();

        pa2m_nuevo_grupo("Pruebas de eliminar elementos de una Lista");
        no_se_puede_eliminar_elementos_de_una_lista_nula();
        se_pueden_eliminar_elementos_de_final_de_una_lista();
        se_pueden_eliminar_todos_los_elementos_de_una_lista();
        no_se_pueden_eliminar_elementos_en_posiciones_aleatorias_de_una_lista_nula();
        se_pueden_eliminar_elementos_en_posiciones_aleatorias();
        no_se_puede_elimina_elementos_de_una_lista_vacia();
        no_se_puede_eliminar_elementos_en_posiciones_aleatorias_de_una_lista_vacia();
        elimino_en_una_posicion_que_no_existe_y_se_elimina_el_ultimo();

        pa2m_nuevo_grupo("Pruebas de busqueda de un elemento en una Lista");
        no_puedo_buscar_elementos_en_una_posicion_en_una_lista_nula();
        no_puedo_buscar_elementos_en_una_posicion_en_una_lista_vacia();
        busco_en_una_posicion_un_elemento_y_lo_encuentro();
        busco_un_elemento_en_una_posicion_que_no_existe_y_no_lo_encuentro();

        pa2m_nuevo_grupo("Pruebas de Iterador Interno");
        si_la_funcion_es_null_no_se_le_aplica_a_ningun_elemento();
        puedo_aplicarle_la_funcion_a_todos_los_elementos_de_la_lista();
        puedo_aplicarle_la_funcion_a_algunos_los_elementos_de_la_lista();

        pa2m_nuevo_grupo("Pruebas de Iterador Externo");
        no_puedo_crear_un_it_con_una_lista_nula();
        puedo_crear_un_it_externo();
        creo_un_it_externo_y_apunta_al_primer_elemento_de_la_lista();
        no_puedo_recorrer_una_lista_vacia(); 
        puedo_recorrer_una_lista();

        pa2m_nuevo_grupo("Pruebas de Cola");
        puedo_crear_una_cola();
        no_puedo_encolar_un_elemento_en_una_cola_nula();
        puedo_encolar_un_elemento();
        puedo_desencolar_un_elemento();
        puedo_encolar_varios_elementos();
        puedo_desencolar_todos_los_elementos();

        pa2m_nuevo_grupo("Pruebas de Pila");
        puedo_crear_una_pila();
        no_puedo_apilar_en_una_pila_nula();
        puedo_apilar_un_elemento();
        puedo_desapilar_un_elemento();
        puedo_apilar_varios_elementos();
        puedo_desapilar_todos_los_elementos();
      
        return pa2m_mostrar_reporte();
}