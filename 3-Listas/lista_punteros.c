#include "listas.h"
#include <stdlib.h>
#include <stdio.h>

static const int TAMANIO_MAXIMO = 100;

struct Nodo
{
    TipoElemento valor;
    struct Nodo *siguiente;
};

struct ListaRep
{
    struct Nodo *primero; // Apuntador al primer nodo de la lista
    int cantidad;         // Cantidad de nodos en la lista
};

struct IteradorRep
{
    struct Nodo *posActual; // Apuntador al nodo actual del iterador en la lista
};

Lista l_crear()
{
    Lista lista = (Lista)malloc(sizeof(struct ListaRep));
    lista->primero = NULL;
    lista->cantidad = 0;
    return lista;
}

bool l_es_vacia(Lista lista)
{
    return lista->cantidad == 0;
}

bool l_es_llena(Lista lista)
{
    return lista->cantidad == TAMANIO_MAXIMO;
}

int l_longitud(Lista lista)
{
    return lista->cantidad;
}

TipoElemento l_recuperar(Lista lista, int pos)
{
    struct Nodo *temp = lista->primero;
    for (int i = 0; i < pos - 1; i++)
    {
        temp = temp->siguiente;
    }
    return temp->valor;
}

void l_agregar(Lista lista, TipoElemento elemento)
{
    if (l_es_llena(lista))
        return;

    // Creo un nuevo nodo con el elemento y lo agrego al final de la lista
    struct Nodo *nuevoNodo = malloc(sizeof(struct Nodo));
    nuevoNodo->valor = elemento;
    nuevoNodo->siguiente = NULL;

    if (lista->primero == NULL)
    {
        lista->primero = nuevoNodo;
    }
    else
    {
        struct Nodo *temp = lista->primero;
        while (temp->siguiente != NULL)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }

    lista->cantidad++;
}

// X
void l_borrar(Lista lista, int clave)
{
    if (l_es_vacia(lista))
        return;

    struct Nodo *nodoActual = lista->primero;

    while (nodoActual != NULL && nodoActual->valor->clave == clave)
    {
        lista->primero = nodoActual->siguiente;
        free(nodoActual);
        lista->cantidad--;
        nodoActual = lista->primero;
    }

    while (nodoActual != NULL && nodoActual->siguiente != NULL)
    {
        if (nodoActual->siguiente->valor->clave == clave)
        {
            struct Nodo *temp = nodoActual->siguiente;
            nodoActual->siguiente = temp->siguiente;
            free(temp);
            lista->cantidad--;
        }
        else
        {
            nodoActual = nodoActual->siguiente;
        }
    }
}

void l_insertar(Lista lista, TipoElemento elemento, int pos)
{
    if (l_es_llena(lista))
    {
        printf("La lista esta llena\n");
        return;
    }

    struct Nodo *nuevoNodo = malloc(sizeof(struct Nodo));
    nuevoNodo->valor = elemento;
    nuevoNodo->siguiente = NULL;

    if (pos == 1)
    {
        nuevoNodo->siguiente = lista->primero;
        lista->primero = nuevoNodo;
    }
    else
    {
        struct Nodo *temp = lista->primero;
        for (int i = 0; i < pos - 2; i++)
        {
            temp = temp->siguiente;
        }
        nuevoNodo->siguiente = temp->siguiente;
        temp->siguiente = nuevoNodo;
    }

    lista->cantidad++;
}

// x
TipoElemento l_buscar(Lista lista, int clave)
{
    // Comprobar si la lista está vacía
    if (l_es_vacia(lista))
    {
        return NULL;
    }

    struct Nodo *nodoActual = lista->primero;
    while (nodoActual != NULL)
    {
        if (nodoActual->valor->clave == clave)
        {
            return nodoActual->valor;
        }
        nodoActual = nodoActual->siguiente;
    }

    return NULL;
}

// Elimina el nodo en la posición dada X
void l_eliminar(Lista lista, int pos)
{
    if (l_es_vacia(lista))
        return;

    struct Nodo *nodoActual = lista->primero;

    if (pos <= 1 || pos <= l_longitud(lista))
    {
        if (pos == 1)
        {
            lista->primero = nodoActual->siguiente;
            free(nodoActual);
        }
        else
        {
            for (int i = 0; i < pos - 2; i++)
            {
                nodoActual = nodoActual->siguiente;
            }
            struct Nodo *temp = nodoActual->siguiente;
            nodoActual->siguiente = temp->siguiente;
            free(temp);
        }
        lista->cantidad--;
    }
}

// Muestra los valores de los nodos de la lista
void l_mostrarLista(Lista lista)
{
    if (l_es_vacia(lista))
    {
        printf("Lista vacia.\n");
        return;
    }

    struct Nodo *temp = lista->primero;
    printf("Datos de la Lista: ");
    while (temp != NULL)
    {
        printf("%d ", temp->valor->clave);
        temp = temp->siguiente;
    }
    printf("\n");
}

// Funciones de iterador de la lista
Iterador iterador(Lista lista)
{
    Iterador iter = (Iterador)malloc(sizeof(struct IteradorRep));
    iter->posActual = lista->primero;
    return iter;
}

bool hay_siguiente(Iterador iter)
{
    return (iter->posActual != NULL);
}

TipoElemento siguiente(Iterador iter)
{
    TipoElemento actual = iter->posActual->valor;
    iter->posActual = iter->posActual->siguiente;
    return actual;
}