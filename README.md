<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# NOMBRE TP/TDA

## Repositorio de Francisco Infanti - 110822 - finfanti@fi.uba.ar

- Para compilar:

```bash
make pruebas_chanutron
```

- Para ejecutar:

```bash
./pruebas_chanutron
```

- Para ejecutar con valgrind:
```bash
make valgrind-chanutron
```
---
##  Funcionamiento

El funcionamiento del TDA *lista* consiste en crear una lista, utilizarla de la manera que se necesite y destruirla. La implementación que se utilizó para la lista fue la de *nodos simplemente enlazados* con una referencia al primer y último nodo. Dentro de cada nodo se almacena la dirección de memoria del nodo que le sigue, en caso de que no existe se guarda `NULL`, y el elemento que el usuario desee almacenar en la lista. En los gráficos se va a ver que los nodos están al lado de otros nodos, pero en realidad pueden estar en cualquier parte de la memoria.

---

<div align="center">
<img width="40%" src="img/nodo.png">
</div>

---

Para poder crear una lista se utiliza la función `lista_crear()`, en esta se declara un puntero `lista` que apunta a un bloque de memoria en el heap. Dicho bloque guardará el número de la cantidad de elementos que se almacenan en la lista y la dirección de memoria del primer y último nodo. De este modo la complejidad de las operaciones será mejor, estamos hablando de que al tener dos referencias podemos hacer que una operación que fuera `O(n)` pase a ser `O(1)`.

---

<div align="center">
<img width="50%" src="img/DDM1.png">
</div>

---

Una vez creada la lista, el usuario puede ingresar y eliminar elementos en cualquier posición de esta. Si el usuario quisiera ingresar un elemento en una posición inválida o borrar un elemento que no existe, el programa intentará insertar el elemento en la última posición de la lista o borrar el último elemento de la lista. El usuario puede guardar cualquier tipo de dato que quiera en los nodos, al programa no le afecta que este sea un *int*, *char*, *bool*, etc... Solamente se necesita que a las funciones se les pase la dirección de memoria de ese tipo de dato.

Cada vez que queramos almacenar un elemento, vamos a tener que reservar un bloque de memoria en el heap, el cual será apuntado por un puntero `nodo`. En dicho bloque se guarda la dirección de memoria del elemento ingresado y la dirección de memoria del nodo que le sigue. Puede que le siga un nodo, como puede que no. Pero es muy importante que si no le sigue ninguno, que esa dirección sea `NULL`, pues sino se podría estar accediendo a un lugar de memoria que no sabemos que tiene. Como mencioné antes, se puede ingresar un elemento en cualquier parte de la lista, pero cada posición tendrá un proceso diferente. En la respuesta a la 2da pregunta teórica pueden verse los gráficos detallados de cada uno de estos procesos. Pero en general si tuviéramos un único elemento, se vería de la siguiente forma.

---

<div align="center">
<img width="50%" src="img/DDM2.png">
</div>

---

Para poder eliminar un elemento de una lista solamente debemos liberar el bloque de memoria donde esta el elemento que queremos eliminar, para liberarlo hacemos uso del puntero `nodo` que apunta a ese bloque. Pero para poder realizar esta operacion con exito y no perder ningun nodo, debemos seguir una serie de pasos. La idea general seria que deberiamos posicionarnos en el `nodo anterior` al cual queremos eliminar y guardar, en un puntero `aux`, la direccion de memoria que `nodo anterior` guarda. Esa direccion seria la del nodo siguiente, que en nuestro caso seria la direccion del nodo que almacena el elemento que queremos borrar. Antes de liberar la memoria, debemos hacer que el `nodo anterior` almacene la direccion de memoria la cual guarda el nodo que queremos borrar. Luego podemos liberar el bloque que esta siendo apuntado por `nodo eliminar` y `aux`. Tambien en la respuesta a la 2da pregunta teorica puede verse los graficos detalladamente. En general con una lista con `n` elementos se veria de la siguiente forma.

---

<div align="center">
<img width="55%" src="img/DDM3.png">
</div>

---

El usuario también puede ver cuántos elementos tiene una lista, ver si está vacía o no y buscar elementos en cualquier parte de la lista. Puede buscar un elemento según una posición o según una condición, ahora según dónde y cómo lo busque hay distintos procesos con distintas complejidades.
 - El caso con la mejor complejidad (`O(1)`) serían que el usuario quisiera ver el primer o último elemento de la lista, en ese caso lo único que se hace es usar los punteros que tiene la lista al primer y último elemento.
 - Si el usuario quisiera buscar un elemento en la posición `n` o que cumpla la condición `x`, en el peor de los casos sería `O(n)`, pues debería recorrer todos los elementos de mi lista.
 - En el caso de que la lista esté vacía o la posición no exista se devolverá directamente `NULL`. Ahora en caso de que ningún elemento cumpla la condición también se devolverá `NULL`, pero tuve que recorrer toda la lista primero.
Al usuario se le devolverá un puntero al tipo de dato que él haya ingresado, el después deberá hacer el casteo correspondiente para poder ver el valor de ese elemento.



---

<div align="center">
<img width="45%" src="img/DDM4.png">
</div>

---

Por último el usuario tiene la posibilidad de utilizar dos iteradores, uno *externo* y uno *interno*.
- El iterador *interno* funcionaria de la siguiente manera, a la función `lista_con_cada_elemento()` se le deberá pasar la lista sobre la que se quiere iterar, la función la cual se le quiera aplicar a los elementos y un puntero, que suele utilizarse como la memoria en común que se tiene entre el usuario y la función. En este caso la función es de tipo *bool*, por lo tanto se puede decidir cuando se termina de iterar.
- El iterador *externo* sería un conjunto de funciones, que le permiten al usuario crear una lista sin conocer como está está implementada. El iteraria como si estuviera iterando un vector. Lo primero que se debería hacer es crear un iterador externo, para eso se reserva un bloque de memoria en el heap, el cual será apuntado por el puntero `iterador`. En dicho bloque se almacena la dirección de memoria de la lista y la dirección de memoria del primer nodo de la lista. Luego una vez creada la lista, ya está apuntando al primer elemento. En caso de que no exista una lista (no tendría sentido crear el iterador), se devolverá `NULL`. Una vez tenemos creado el iterador, podemos hacer tres cosas.

  - Verificar si seguimos teniendo elementos para iterar, es decir, si el `nodo actual` guarda la dirección de memoria de algún nodo. Por este motivo es por el cual mencione antes que es importante que si a un nodo no lo sigue otro, entonces que apunte a `NULL`, sino en este caso estaríamos diciendo que si tiene un siguiente cuando en realidad no es cierto.

  - Mostrar el elemento del nodo actual, en este caso lo único que se hace es devolver la dirección de memoria de donde está el elemento. Claramente si el nodo es `NULL`, se devolverá `NULL`, pero no hay problema si el elemento que está guardado en esa dirección de memoria es `NULL`.

  - Lo último sería lo principal de la iteración, que es avanzar de elemento. Esto le permite al usuario que la dirección de memoria que hace referencia al nodo, pase al siguiente nodo. Es decir, si el `nodo actual` apuntaba al primer nodo, y ese tiene siguiente, ahora `nodo actual` apunta al siguiente de ese nodo. En el caso de que el primer nodo no tenga siguiente, se avanza el iterador igualmente. En caso de que se pueda avanzar exitosamente, se devolverá *true*, pero en caso de que se avance y el `nodo actual` sea `NULL`, se devuelve *false*. También en el caso de que falle algo se devuelve *false*.

  - También es muy importante que una vez que se termina de usar el iterador, debemos liberar la memoria que este ocupaba en memoria. Pero solamente la del iterador, la de la lista se elimina una vez se quiera dejar de utilizar el programa.

---

<div align="center">
<img width="50%" src="img/DDM5.png">
</div>

---

Finalmente una vez que queramos dejar de usar el programa, debemos liberar toda la memoria utilizada por la lista. Hay dos formas "diferentes" de eliminar una lista. La primera será aplicar la función `lista_destruir()` la cual solamente libera la memoria de la lista y la otra sería aplicar `lista_destruir_todo()` la cual antes de eliminar la lista le aplica una función a cada elemento de esta. Las funciones hacen exactamente lo mismo, porque en el caso de que la función pasada por parámetro sea `NULL`, se va a seguir liberando la memoria de la listas como si fuera la función `lista_destruir()`. La forma en la que se destruiría sería ir nodo por nodo liberando la memoria, hasta que solamente quede el bloque apuntado por `lista`.

---

<div align="center">
<img width="55%" src="img/DDM6.png">
</div>

---

Finalmente se liberaría el bloque apuntado por `lista`.

---

<div align="center">
<img width="45%" src="img/DDM7.png">
</div>

---

También se implementaron otros dos TDA, el de *pila* y *cola*. Ambos TDA utilizan las funciones de *lista*, pero tienen algunas restricciones. En ambos casos se siguió utilizando la implementación de *nodos simplemente enlazados* con una referencia al primer y último nodo.

En el caso de la *pila*, también se debe crear reservando un bloque de memoria en el heap, el cual será apuntado por el puntero `pila`. Dentro de este bloque se guardarán los mismos datos que se guardaban en el de la lista. 

---

<div align="center">
<img width="40%" src="img/DDM8.png">
</div>

---

Una diferencia fundamental, en comparación con el TDA lista, es que en este caso solamente podemos insertar, eliminar y ver el elemento que se encuentra en la posición del tope de la pila. La idea es la misma que en la lista, se recibe qué elemento se quiere insertar y se crea un nodo y se lo inserta en la última posición. Lo mismo con eliminar, voy a tener que liberar la memoria que me ocupa el nodo del tope de la lista.

---

<div align="center">
<img width="70%" src="img/DDM9.png">
</div>

---

También podemos hacer operaciones como chequear si está vacía o la cantidad de elementos que tiene. Por último y muy importante es que debemos liberar toda la memoria utilizada por la pila. El proceso para eliminar es el mismo que el de lista, solamente que en este caso no es necesario aplicarle una función a los elementos.

---

<div align="center">
<img width="100%" src="img/DDM10.png">
</div>

---

En el caso de la *cola*, también debemos reservar un bloque de memoria en el heap, el cual será apuntado por el puntero `cola`. Dicho bloque guardará lo mismo que el de pila y lista.

---

<div align="center">
<img width="50%" src="img/DDM11.png">
</div>

---

Una diferencia con respecto al TDA de lista y pila, es que en este caso solamente podemos insertar elementos en la última posición de la cola. El proceso sigue siendo el mismo, creamos un nodo con la dirección de memoria del elemento que se quiere insertar y se lo inserta en la última posición de la cola. En cuanto a eliminar, solamente podemos eliminar el elemento de la primera posición de la pila. El proceso sigue siendo el mismo que el de querer eliminar un elemento de la primera posición en la lista. Y por último, si queremos ver un elemento, solamente tenemos acceso al elemento que se encuentra en la primera posición de la cola.

---

<div align="center">
<img width="90%" src="img/DDM12.png">
</div>

---

También siguen estando las operaciones de ver si la cola está vacía o no, y ver la cantidad de elementos tenemos en esta. A su vez, cuando terminemos de utilizar el programa, debemos liberar toda la memoria utilizada. También el proceso de eliminar es el mismo que el de lista, solamente que no hace falta aplicarle una función a los elementos de esta.

---

<div align="center">
<img width="100%" src="img/DDM13.png">
</div>


## Respuestas a las preguntas teóricas 

**1.** Una Lista, Pila y Cola son tipos de datos abstractos (TDA), los cuales nos permiten almacenar elementos de cualquier tipo de dato. Cada uno de estos TDA tienen un conjunto mínimo de operaciones, algunas son similares entre los TDA y otras no tanto. El conjunto mínimo de operaciones son los siguientes: *crear*, *destruir*, *insertar*, *eliminar*, *vacía* y *ver elemento*.

Las operaciones de *crear**, *destruir* y *vacía*, funcionan de la misma manera en los tres TDA. La función que cumplen es crear, destruir y determinar si tiene elementos una lista, cola o pila. Las que valen la pena hacer hincapié en cada TDA son la de *insertar*, *eliminar* y *ver elemento*, pues estas si son diferentes en cada uno.

**LISTA**: Para este TDA, se puede utilizar la implementación de lista simplemente enlazada con una referencia al primer elemento y al último.

---

<div align="center">
<img width="40%" src="img/lista.png">
</div>

---

- La operación de *insertar* no tiene ninguna restricción, el usuario puede insertar un elemento en cualquier parte de mi lista, si es que esta posición existe. A la hora de insertar un elemento pueden darse 3 casos diferentes.

  - *1)* El primer caso consiste en querer insertar un elemento en la primera posición de mi lista. 

  - *2)* El segundo caso consiste en insertar un elemento en la última posición de mi lista.

  - *3)* El último caso consiste en querer insertar el elemento en una posición aleatoria, puede ser en la primera, medio o final.

- Para la operación de *eliminar* tampoco nos encontramos con alguna restricción, el usuario puede eliminar elementos de cualquier posición, también si es que dicha posición existe. En esta también se pueden dar 3 casos diferentes.

  - *1)* El primer caso consiste en querer eliminar el elemento que está en la primera posición.

  - *2)* El segundo caso consiste en querer eliminar el elemento que se encuentra en una posición aleatoria, puede ser la primera, una cualquiera o la última.

  - *3)* Por último el tercer caso consiste en querer eliminar el elemento que se encuentra en la última posición.

- Por último para la operación de *ver elemento*, el usuario puede ver cualquier elemento que se encuentre en la lista.

**PILA**: Para este TDA ya empiezan a haber una serie de restricciones a la hora de usarlo. Primero de todo, para poder implementarlo conviene utilizar nodos simplemente enlazada con una referencia al último elemento de la pila.

---

<div align="center">
<img width="40%" src="img/pila.png">
</div>

---

Una pila almacena elementos "apilados uno arriba de otro". Es decir se lo puede pensar como una pila de ropa, donde uno siempre deja una nueva prenda encima de la anterior. Se dice que este TDA sigue una estructura de **L.I.F.O** (Last In, First Out), esta consiste en que el último elemento que agrego va a ser el primero en salir.

- La operación de *insertar*, también llamada *apilar* o *push*, se comporta de la forma mencionada anteriormente. El usuario solamente va a poder insertar elementos en la última posición, también conocida como *tope*.

- En cuanto a la operación de *eliminar*, también conocido como *desapilar* o *pop*, el usuario solamente va a poder eliminar el elemento que se encuentra en la posición del tope.

- Por último para la operación de *ver elemento*, el usuario solamente tiene acceso al elemento que se encuentra en la posición del tope.

**COLA**: Para este TDA también existen ciertas restricciones a la hora de usarlo. En este caso conviene tener una implementación de nodos simplemente enlazados, en la cual la cola tiene una referencia al primer elemento.

---

<div align="center">
<img width="40%" src="img/cola.png">
</div>

---

Como los TDA anteriores, una cola lo que hace es almacenar elementos, pero en este caso "los pone uno atrás del otro". Este TDA tiene una estructura llamada **F.I.F.O** (First In, First Out), la cual consiste en que el primer elemento que ingresamos, será el primero en salir. Por eso se lo puede pensar como una cola de autos donde el primer auto que ingresa es el primero en salir.

- La operación de *insertar*, también conocida como *encolar* o *enqueue*, consiste en que el usuario solamente puede ingresar elementos en la última posición de la cola.

- La operación de *eliminar*, también conocida como *desencolar* o *dequeue*, consiste en que el usuario únicamente puede eliminar el elemento que se encuentra en la primera posición de la cola.

- Por último la operación de *ver elemento*, consiste en que el usuario solamente puede ver el elemento que está en la primera posición.

**2.** Hay distintas formas de poder implementar el TDA de lista, en este caso voy a comparar tres diferentes implementaciones: lista *simplemente enlazada*, *doblemente enlazada* y *vector dinámico*. Para cada una de estas implementaciones voy a analizar cómo se inserta, obtiene y elimina un elemento en diferentes posiciones.

Antes de empezar a explicar las operaciones, voy a mencionar por encima como funciona cada implementación. El *vector dinámico* consiste en tener un vector de un tamaño no fijo, el cual puedo ir agrandando o reduciendo a medida que se insertan o eliminan elementos. La lista *simplemente enlazada* y *doblemente enlazada* consisten en utilizar un TDA llamado nodos. Los nodos almacenan dos cosas, un elemento `(void*)` y la dirección de memoria del nodo que le sigue (en el caso de la doblemente enlazada tengo la direccion del anterior y el siguiente), pues los nodos funcionan como una especie de vector dinámico, el cual nos permite almacenar elementos sin necesidad de tener bloques contiguos de memoria libre.
La forma la cual tendrán estas implementaciones sería la siguiente:

---

<div align="center">
<img width="80%" src="img/implementaciones.png">
</div>

---

Si queremos insertar, eliminar o ver un elemento en una lista, se pueden dar 3 casos diferentes:

- El primero sería insertar un elemento en la primera posición de nuestra lista. En el caso de la lista *simplemente enlazada* lo que debemos hacer es usar la referencia de `nodo_inicio` para hacer que `nodo_nuevo` apunte a donde estaba apuntando `nodo_inicio`, luego `nodo_inicio` debe apuntar a `nuevo_nodo`. Para la *doblemente enlazada* se realiza una operación similar, con la única diferencia de que `nodo_primero` apunta a `nodo_nuevo`. La complejidad de estos casos es `O(1)`, pues lo único que estamos haciendo son operaciones simples, como asignar nuevas direcciones de memoria a punteros. En cuanto al caso del *vector dinámico* lo que debemos hacer, en el peor de los casos, es agrandar el bloque de memoria usando `realloc()`. Por lo tanto estamos realizando una operación de `O(n)`. Además debemos correr todos los elementos un lugar a la derecha, a partir de la primera posición, para así poder "dejarle el lugar" al nuevo elemento (otra operación `O(n)`). Pero finalmente la complejidad total de insertar seria `O(n)`, la cual es peor a la de la implementación de *simplemente enlazada* y  *doblemente enlazada*.

---

<div align="center">
<img width="80%" src="img/insertar_principio.png">
</div>

---

- En cuanto a querer eliminar un elemento, en la lista *simplemente enlazada*, usamos la referencia que tiene `nodo_inicio` al `nodo_primero` y hacemos que un puntero `aux` apunte a `nodo_primero`. Luego `nodo_primero` debe apuntar al siguiente de `nodo_inicio`. En el caso de la *doblemente enlazada* también es muy similar el proceso, solo que ahora no necesitamos usar un `aux`, directamente accedemos a `nodo_eliminar` y hacemos que `nodo_inicio` apunte a `nodo_primero`, luego `nodo_primero` apunta a `NULL`.En ambas implementaciones la complejidad total seria `O(1)`, pues solamente estamos haciendo operaciones simples. Ahora en el caso de la implementación de *vector dinámico*, lo que deberíamos hacer es eliminar el elemento que está en la primera posición y luego mover todos los elementos restantes un lugar a la izquierda. También nuevamente debemos usar `realloc()`. Por lo tanto la complejidad de toda esta operación es `O(n)`, luego veamos que también es peor en comparación con la implementación de nodos.

---

<div align="center">
<img width="80%" src="img/eliminar_principio.png">
</div>

---

- Por último, si queremos ver un elemento en la primera posición. Para todas las implementaciones la complejidad es `O(1)`, pues lo único que debemos hacer es ir a una dirección de memoria del primer elemento, de esta en los tres casos tenemos una referencia directa.

- El segundo caso sería querer insertar un elemento en la posición `n`. En la lista *simplemente enlazada* lo que debemos hacer es recorrer los nodos hasta llegar a `n-1`, sería el anterior a donde queremos insertar. Ahora`nodo_nuevo` debe apuntar a donde está apuntando `nodo_anterior`, y `nodo_anterior` debe apuntar a `nodo_nuevo`. En la lista *doblemente enlazada* también es muy similar el proceso, la única diferencia es que ahora debemos hacer que `nuevo_nodo` apunte a `nodo_anterior` y`nodo_siguiente`, y viceversa. Veamos que para esta implementación la complejidad `O(n)`, pues debemos recorrer hasta la posición `n-1` y hacer algunas operaciones simples que no aportan al tamaño del problema. Por último para el *vector dinámico* debemos agrandar nuevamente el bloque de memoria con `realloc()` y mover todos los elementos un lugar a la derecha, a partir la posición `n`, para así poder insertar el nuevo elemento. Por lo tanto en este caso también la complejidad sería `O(n)`, pero si lo comparamos con la  implementación de nodos esta resulta ser peor, pues realizamos 3 operaciones de `O(n)`

---

<div align="center">
<img width="80%" src="img/insertar_medio.png">
</div>

---

- Para eliminar un elemento en la posición `n`, en la lista *simplemente enlazada* debemos recorrer hasta `n-1` y usar `nodo_anterior` para que un `aux` apunte a `nodo_eliminar`. Antes de eliminarlo debemos hacer que `nodo_anterior` apunte a donde estaba apuntado `nodo_eliminar`. En la lista *doblemente enlazada* debemos hacer lo mismo solo que ahora recorremos hasta la posición `n` y usando las referencias que tiene `nodo_eliminar` para que los nodos que tiene a su lado se apunten entre sí. Veamos que para ambos casos la operación es `O(n)`, pues en el peor de los casos recorremos hasta la `n`, `n-1` posición de la lista. Ahora viendo el caso del *vector dinámico* lo que habría que hacer es recorrer hasta la posición `n` y pisarla con el elemento de la posición `n+1` y así a `n+1` lo pisamos con `n+2`. Luego debemos mover todos los elementos a una posición a la izquierda y por último usar `realloc()`. Pero aún así, veamos que la operación es `O(n)`, pero si lo comparamos con las implementaciones de nodos esta es peor porque debemos recorrer el vector dos veces, aunque ambas por separado.

---

<div align="center">
<img width="80%" src="img/eliminar_medio.png">
</div>

---

- Si queremos ver un elemento en la posición del medio, en todos los casos debemos recorrer hasta la posición `n`. Así que la complejidad para todos sería `O(n)`.

- El último caso consiste en querer insertar un elemento en la última posición de la lista. En la lista *simplemente enlazada* lo que debemos hacer es utilizar la referencia de `nodo_fin` para poder ir hasta la última posición de nuestra lista y hacer que el `nodo_ultimo` apunte a `nuevo_nodo` y luego hacemos que `nodo_fin` apunte a `nuevo_nodo`. Ahora con la lista *doblemente enlazada* el proceso es el mismo solo que ahora `nuevo_nodo` debe apuntar a `nodo_utlimo`. Observemos que la complejidad vuelve a ser `O(1)`, pues solo estamos haciendo operaciones simples. Por último usando el *vector dinámico*, debemos agrandar el bloque de memoria usando `realloc()` y después recorrer todo el vector hasta la última posición e insertar el elemento. Entonces en este caso la complejidad sigue siendo `O(n)`, la cual es peor a las dos implementaciones previas.

---

<div align="center">
<img width="80%" src="img/insertar_final.png">
</div>

---

- Si queremos eliminar un elemento de la posición del final, en la lista *simplemente enlazada* debemos recorrer hasta la posición `n-1`, `nodo_anterior`, y hacer que un puntero `aux` apunte a `nodo_ultimo`. Luego modificamos que `nodo_anterior` apunte a `NULL` y después debemos recorrer todos los nodos hasta el último, para que `nodo_fin` apunte al nuevo último nodo. Ahora para la lista *doblemente enlazada* solamente usamos la referencia de `nodo_fin` al `nodo_ultimo` y usando la referencia que tiene este al `nodo_anterior`, hacemos que `nodo_fin` apunte a `nodo_anterior`. En este caso si hay una diferencia de complejidad entre las implementaciones con nodos, pues para la *simplemente enlazada* la complejidad es `O(n)`, mientras que para la *doblemente enlazada* es `O(1)`. Para la implementación de *vector dinámico* usamos directamente `realloc()`. Luego en este caso la complejidad sería `O(n)`, únicamente por haber usado `realloc()`. Veamos que la mejor implementación en este caso sería la lista *doblemente enlazada*, y la de *vector dinámico* tiene la misma complejidad que *simplemente enlazada*.

---

<div align="center">
<img width="80%" src="img/eliminar_final.png">
</div>

---

- Por último si queremos ver un elemento en la última posición, también sería como verlo en la primera, lo único que debemos hacer es ir hasta esa posición, con una referencia directa, y mostrar el elemento. Es decir, tiene una complejidad `O(1)` para las tres implementaciones.

**3.**