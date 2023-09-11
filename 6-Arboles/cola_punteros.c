#include "tipo_elemento.h"
#include "colas.h"
#include <stdio.h>
#include <stdlib.h>

static const int TAMANIO_MAXIMO_COLA = 10;

struct Nodo
{
    TipoElemento datos;
    struct Nodo *siguiente;
};

struct ColaRep
{
    struct Nodo *frente;
    struct Nodo *final;
};

Cola c_crear()
{
    Cola nuevaCola = (Cola)malloc(sizeof(struct ColaRep));
    nuevaCola->frente = NULL;
    nuevaCola->final = NULL;

    return nuevaCola;
}

void c_encolar(Cola cola, TipoElemento elemento)
{
    if (c_es_llena(cola))
        return;

    struct Nodo *nuevoNodo = malloc(sizeof(struct Nodo));
    nuevoNodo->datos = elemento;
    nuevoNodo->siguiente = NULL;

    if (c_es_vacia(cola))
        cola->frente = nuevoNodo;
    else
        cola->final->siguiente = nuevoNodo;

    cola->final = nuevoNodo;
}

TipoElemento c_desencolar(Cola cola)
{
    if (c_es_vacia(cola))
        return NULL;

    struct Nodo *inicio = cola->frente;
    TipoElemento elemento = inicio->datos;
    cola->frente = inicio->siguiente;

    free(inicio);
    return elemento;
}

bool c_es_vacia(Cola cola)
{
    return (cola->frente == NULL);
}

int longitud(Cola cola)
{
    int i = 0;
    struct Nodo *N = cola->frente;
    while (N != NULL)
    {
        i++;
        N = N->siguiente;
    }

    return i;
}

bool c_es_llena(Cola cola)
{
    return (longitud(cola) == TAMANIO_MAXIMO_COLA);
}

void c_mostrar(Cola cola)
{
    if (c_es_vacia(cola))
    {
        printf("Cola Vacia \n");
        return;
    }

    Cola cAux = c_crear();
    TipoElemento el = te_crear(0);

    // Desencolo y guardo en auxiliar
    while (c_es_vacia(cola) != true)
    {
        el = c_desencolar(cola);
        printf("%d ", el->clave);
        c_encolar(cAux, el);
    }

    //  Ahora paso la auxiliar a la cola original
    while (c_es_vacia(cAux) != true)
    {
        el = c_desencolar(cAux);
        c_encolar(cola, el);
    }
}

void c_encolar_al_frente(Cola cola, TipoElemento elemento)
{
    struct Nodo *nuevo = (struct Nodo *)malloc(sizeof(struct Nodo));
    nuevo->datos = elemento;
    nuevo->siguiente = cola->frente;
    cola->frente = nuevo;

    if (cola->final == NULL)
    {
        cola->final = nuevo;
    }
}
