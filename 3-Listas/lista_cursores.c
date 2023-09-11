#include "../listas.h"
#include <stdlib.h>
#include <stdio.h>

static const int TAMANIO_MAXIMO = 100;
static const int VACIO = -1;

struct Nodo
{
    TipoElemento valor;
    int siguiente;
};

struct ListaRep
{
    struct Nodo *cursor; // Apuntador al Arreglo que contiene la lista
    int primero;
    int libre;
    int cant; // cantidad
};

struct IteradorRep
{
    Lista lista;
    int posActual;
};

bool l_es_vacia(Lista lista)
{
    return lista->cant == 0;
}

bool l_es_llena(Lista lista)
{
    return lista->cant == TAMANIO_MAXIMO;
}

int l_longitud(Lista lista)
{
    return lista->cant;
}

Lista l_crear()
{
    // Almaceno espacio para la nueva lista
    Lista nuevaLista = (Lista)malloc(sizeof(struct ListaRep));
    // Almaceno espacio VACIO para el cursor
    nuevaLista->cursor = calloc(TAMANIO_MAXIMO, sizeof(struct Nodo));
    nuevaLista->cant = 0;
    nuevaLista->primero = VACIO;

    // Encadeno todos los nodos
    for (int i = 0; i < TAMANIO_MAXIMO - 2; i++)
    {
        nuevaLista->cursor[i].siguiente = i + 1;
    }

    nuevaLista->libre = 0;
    nuevaLista->primero = VACIO; // El 1er elemento esta vacio (-1)
    nuevaLista->cursor[TAMANIO_MAXIMO - 1].siguiente = VACIO;

    return nuevaLista;
}

void l_agregar(Lista lista, TipoElemento elemento)
{
    //     printf("Estado de la lista antes de agregar un elemento:\n");
    // l_mostrarLista(lista);
    if (l_es_llena(lista))
    {
        printf("La lista esta llena, no es posible agregar elementos \n");
        return;
    }

    int primero = lista->libre;
    // indico que el elemento posterior al cual agregue esta libre
    lista->libre = lista->cursor[primero].siguiente;
    lista->cursor[primero].valor = elemento;
    lista->cursor[primero].siguiente = VACIO;

    // Controlo que no sea el primer elemento el que este vacío
    if (lista->primero == VACIO)
        lista->primero = primero;
    else
    {
        int sig = lista->primero;
        while (lista->cursor[sig].siguiente != VACIO)
        {
            sig = lista->cursor[sig].siguiente;
        }
        lista->cursor[sig].siguiente = primero;
    }
    lista->cant++;

    // printf("Estado de la lista después de agregar un elemento:\n");
    // l_mostrarLista(lista);
}

void l_insertar(Lista lista, TipoElemento elemento, int pos)
{
    if (l_es_llena(lista))
    {
        printf("La lista esta llena, no es posible insertar elementos \n");
        return;
    };

    if (pos < 1 || pos > lista->cant)
    {
        printf("Posición inválida\n");
        return;
    }

    int primer = lista->libre;
    lista->libre = lista->cursor[primer].siguiente;
    lista->cursor[primer].valor = elemento;
    lista->cursor[primer].siguiente = VACIO;

    // Entro en el if si el usuario quiere insertar el elemento en la primer posicion
    if (pos == 1)
    {
        lista->cursor[primer].siguiente = lista->primero;
        lista->primero = primer;
    }
    else
    {
        int temp = lista->primero;
        for (int i = 0; i < pos - 2; i++)
            temp = lista->cursor[temp].siguiente;

        lista->cursor[primer].siguiente = lista->cursor[temp].siguiente;
        lista->cursor[temp].siguiente = primer;
    }
    lista->cant++;
}

void l_eliminar(Lista lista, int pos)
{
    if (l_es_vacia(lista))
    {
        printf("La lista esta vacía, no es posible eliminar elementos \n");
        return;
    }

    int primer;
    int actual = lista->primero;

    // Si el usuario quiere eliminar la primer posicion...
    if (pos <= 1 && pos <= l_longitud(lista))
    {
        primer = actual;
        lista->primero = lista->cursor[actual].siguiente;
        lista->cursor[primer].siguiente = lista->libre;
        lista->libre = primer; // El nodo que elimine se va a la pila de memoria libre
    }
    // Si el usuario quiere eliminar otro nodo debere de reacomodar la lista
    else
    {
        // -2 ya que me tengo que quedar atras del nodo que quiero eliminar, para poder reconectar los nodos (-1 xq el usuario pone la pos ordinal y -1 xq tengo q qdar atras del nodo a eliminar)
        for (int i = 0; i < pos - 2; i++)
        {
            actual = lista->cursor[actual].siguiente;
        }
        primer = lista->cursor[actual].siguiente;
        lista->cursor[actual].siguiente = lista->cursor[primer].siguiente;
        lista->cursor[lista->libre].siguiente = primer;
        lista->libre = primer; // El nodo que elimine se va a la memoria libre reservada para utilizarla mas tarde
    }

    lista->cant--;
}

void l_borrar(Lista lista, int clave)
{
    if (l_es_vacia(lista))
    {
        printf("La lista está vacía, no es posible borrar elementos \n");
        return;
    }
    int q;
    int pos = lista->primero;

    while (pos != VACIO && lista->cursor[pos].valor->clave == clave)
    {
        q = pos;
        lista->primero = lista->cursor[pos].siguiente;
        lista->cursor[q].siguiente = lista->libre;
        lista->libre = q;
        lista->cant--;
        pos = lista->primero;
    }
    pos = lista->primero;
    int ant = VACIO;
    while (pos != VACIO && lista->cursor[pos].siguiente != VACIO)
    {
        if (lista->cursor[pos].valor->clave == clave)
        {
            if (ant == VACIO) // El nodo a eliminar es el primero
            {
                lista->primero = lista->cursor[pos].siguiente;
            }
            else // El nodo a eliminar es distinto al primero
            {
                lista->cursor[ant].siguiente = lista->cursor[pos].siguiente;
            }

            // Encadenar el nodo eliminado en la lista de nodos libres
            lista->cursor[pos].siguiente = lista->libre;
            lista->libre = pos;
            lista->cant--;

            // Salir del while ya que se eliminó el elemento
            break;
        }

        ant = pos;
        pos = lista->cursor[pos].siguiente;
    }
}

TipoElemento l_buscar(Lista lista, int clave)
{
    if (l_es_vacia(lista))
    {
        printf("La lista está vacía, no es posible buscar elementos \n");
        return NULL;
    }
    int actual = lista->primero;
    while (actual != VACIO)
    {
        if (lista->cursor[actual].valor->clave == clave)
        {
            return lista->cursor[actual].valor;
        }
        actual = lista->cursor[actual].siguiente;
    }
    // Si no se encuentra la clave, retorna un elemento nulo o vacío
    return NULL;
}

TipoElemento l_recuperar(Lista lista, int pos)
{
    // Verifico que la lista no esté vacía
    if (l_es_vacia(lista))
    {
        printf("La lista está vacía \n");
        return NULL;
    }
    // Verifico que la posición sea válida
    if (pos < 1 || pos > lista->cant)
    {
        // Si la posición no es válida retorno un elemento nulo o vacío
        return NULL;
    }
    // Busco el nodo en la posición indicada
    struct Nodo *actual = lista->cursor + lista->primero;
    for (int i = 1; i < pos; i++)
    {
        actual = lista->cursor + actual->siguiente;
    }
    // Retorno el valor del nodo encontrado
    return actual->valor;
}

void l_mostrarLista(Lista lista)
{
    if (l_es_vacia(lista))
    {
        printf("Lista vacia.\n");
        return;
    }

    printf("Contenido de la lista:\n");
    int actual = lista->primero;
    while (actual != VACIO)
    {
        // lista->cursor[sig].siguiente != VACIO
        printf("%d ", lista->cursor[actual].valor->clave);
        actual = lista->cursor[actual].siguiente;
    }
    printf("\n");
}

// Funciones sobre el iterador
Iterador iterador(Lista lista)
{
    Iterador iter = (Iterador)malloc(sizeof(struct IteradorRep));
    iter->lista = lista;
    iter->posActual = lista->cursor + lista->primero;
    return iter;
}

bool hay_siguiente(Iterador iter)
{
    return (iter->posActual != iter->lista->cant);
}

TipoElemento siguiente(Iterador iter) {
    if (iter == NULL) {
        printf("Error: el iterador es nulo\n");
        return NULL;
    }
    if (iter->posActual == VACIO) {
        printf("Error: el iterador ha alcanzado el final de la lista\n");
        return NULL;
    }
    
    if (iter->posActual<0 || iter->posActual>=iter->lista->cant) {
        iter->posActual = iter->lista->primero;
    }

    TipoElemento actual = iter->lista->cursor[iter->posActual].valor;
    iter->posActual = iter->lista->cursor[iter->posActual].siguiente;

    return actual;
}
