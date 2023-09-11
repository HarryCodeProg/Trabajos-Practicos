#include "listas.h"
#include <stdlib.h>
#include <stdio.h>

static const int TAMANIO_MAXIMO = 100;

struct ListaRep
{
    TipoElemento *valores; // Puntero a Arreglo de "TipoElemento"
    int inicio;
    int cantidad; // Cantidad de elementos en la lista
};

struct IteradorRep
{
    Lista lista;        // Puntero a la lista (Lista lista)
    int posicionActual; // Posicion actual del iterador en la lista
};

// "lista" es un puntero a una estructura del tipo 'ListaRep', por lo que necesito utilizar la notacion de flecha (->) para acceder a los miembros/propiedades de la estructura, tambien puede usar (*lista).propiedad

Lista l_crear()
{
    // Reservo en memoria espacio para una nueva instacia de "struct ListaRep" (asigno un bloque de memoria del tamaño que necesite la estructura ListaRep), y luego asigno la direccion de memoria a la variable "lista".
    Lista lista = (Lista)malloc(sizeof(struct ListaRep));
    lista->valores = calloc(TAMANIO_MAXIMO, sizeof(TipoElemento));
    // lista->valores = NULL; // Digo que el arreglo no ha sido inicializado, por lo que no tiene ningun elemento
    lista->cantidad = 0;
    return lista;
}

// Comprueba si la cantidad de elementos en la lista es igual a 0. Si es 0 la funcion retorna 'true', de lo contrario retorna 'false'
bool l_es_vacia(Lista lista)
{
    return lista->cantidad == 0;
}

// Comprueba si la cantidad de elementos en la lista es igual al maximo permitido (100), si la lista esta llena retorna 'true' de lo contrario 'false'
bool l_es_llena(Lista lista)
{
    return lista->cantidad == TAMANIO_MAXIMO;
}

// Retorna la cantidad de elementos en la lista
int l_longitud(Lista lista)
{
    return lista->cantidad;
}

void l_agregar(Lista lista, TipoElemento elemento)
{
    if (l_es_llena(lista))
    {
        printf("Error: La lista esta llena. \n");
        return;
    }

    int indice = lista->cantidad;      // Indice del próximo elemento a agregar
    lista->valores[indice] = elemento; // Lo almaceno en la sig posicion en la que no haya nada
    lista->cantidad++;
}

// Borra un elemento con una clave especifica de una lista. En el caso de que la clave no se encuentre imprime un mensaje por consola, en el caso de que haya mas de una clave igual, borra la primera ocurrencia
void l_borrar(Lista lista, int clave)
{
    int pos = -1;

    if (l_es_vacia(lista))
    {
        printf("La lista esta vacia");
        return;
    }

    // Busco la posicion del elemento con la clave especificada para poder eliminarlo
    for (int i = 0; i < lista->cantidad; i++)
    {
        if (lista->valores[i]->clave == clave)
        {
            pos = i;
            break; // Salgo del bucle porque ya encontre el elemento con esa clave
        }
    }

    if (pos == -1)
    {
        printf("La clave %i no se enuentra en la lista\n", clave);
        return;
    } // Salgo de la funcion porque no se encontró el elemento (Nose si esta bien utilizar break y return para forzar una salida de la funcion)

    // Si se encontro el elemento con x clave, necesito mover todos los elementos posteriores a este hacia atrás (para pisar el elemento que se quiere borrar con el que le sigue)
    for (int i = pos + 1; i < lista->cantidad; i++)
    {
        lista->valores[i - 1] = lista->valores[i];
    }
    lista->cantidad--;
}

// Recibe una lista, una clave y un retorna el elemento que contiene esa clave, de lo contrario retorna NULL
TipoElemento l_buscar(Lista lista, int clave)
{
    for (int i = 0; i < lista->cantidad; i++)
    {
        if (lista->valores[i]->clave == clave)
        {
            return lista->valores[i];
        }
    }

    // Si no se encontró el elemento, devuelvo un valor nulo
    return NULL;
}

// Se ingresa la lista, el elemento y la posicion ORDINAL en la que se quiere insertar el elemento
void l_insertar(Lista lista, TipoElemento elemento, int pos)
{
    int indice = pos - 1;

    // Validaciones
    if (pos < 1 || indice > lista->cantidad)
    {
        printf("Posición inválida\n");
        return;
    }

    if (lista->cantidad == TAMANIO_MAXIMO)
    {
        printf("La lista está llena, no es posible agregar el elemento\n");
        return;
    }

    for (int i = lista->cantidad; i > indice; i--)
    {
        lista->valores[i] = lista->valores[i - 1];
    }

    lista->valores[indice] = elemento;
    lista->cantidad++;
}

// Elimina un elemento de una lista dada una posicion ORDINAL
void l_eliminar(Lista lista, int pos)
{
    int indice = pos - 1;

    if (l_es_vacia(lista))
    {
        printf("La lista esta vacia");
        return;
    }
    if (pos < 1 || pos >= lista->cantidad)
    {
        printf("Posición inválida\n");
        return;
    }

    for (int i = indice; i < lista->cantidad - 1; i++)
    {
        lista->valores[i] = lista->valores[i + 1];
    }

    lista->cantidad--;
}

// Busca un elemento de una lista dada una posicion ORDINAL y lo retorna, retorna NULL en caso contrario
TipoElemento l_recuperar(Lista lista, int pos)
{
    int indice = pos - 1;
    if (pos < 0 || pos > lista->cantidad)
    {
        printf("Posición inválida\n");
        return NULL;
    }

    return lista->valores[indice];
}

void l_mostrarLista(Lista lista)
{
    printf("Lista: \n");
    for (int i = 0; i < lista->cantidad; i++)
        printf("%d ", lista->valores[i]->clave);
    printf("\n");
}

// Metodos del iterador

// Crea un Iterador para recorrer los elementos de una lista basada en arreglos
Iterador iterador(Lista lista)
{
    Iterador iter = malloc(sizeof(struct IteradorRep));
    iter->lista = lista; // Apunto a la lista que voy a recorrer
    iter->posicionActual = 0;
    return iter;
}

//  Verifica si la posición actual del iterador es menor que la cantidad de elementos que contiene la lista. Retorna true si hay elementos siguiente y false en caso contrario
bool hay_siguiente(Iterador iterador)
{
    if (iterador->posicionActual <= iterador->lista->cantidad - 1)
    {
        iterador->posicionActual++;
        return true;
    }
    else
        return false;
}

// Verifica si hay elemento siguiente, en el caso de que no haya se retorna NULL, en el caso de que exista se retorna el elemento (TipoElemento)
TipoElemento siguiente(Iterador iterador)
{
    if (hay_siguiente(iterador) == false)
    {
        printf("No hay elemento siguiente\n");
        return NULL;
    }

    return iterador->lista->valores[iterador->posicionActual];
}