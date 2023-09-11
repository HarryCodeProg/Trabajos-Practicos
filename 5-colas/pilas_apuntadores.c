#include <stdlib.h>
#include <stdio.h>
#include "pilas.h"
#include "tipo_elemento.h"

static const int TAMANIO_MAXIMO_PILA = 50;

struct NodoPila
{
    TipoElemento datos;
    struct NodoPila *siguiente;
};

struct PilaRep
{
    struct NodoPila *tope;
};

Pila p_crear()
{
    Pila nueva_pila = (Pila)malloc(sizeof(struct PilaRep));
    nueva_pila->tope = NULL;
}

void p_apilar(Pila pila, TipoElemento elemento)
{
    if (p_es_llena(pila))
    {
        printf("La pila esta llena, no se pueden apilar mas elementos");
        return;
    }

    struct NodoPila *nuevo_nodo = malloc(sizeof(struct NodoPila));
    nuevo_nodo->datos = elemento;
    nuevo_nodo->siguiente = pila->tope;
    pila->tope = nuevo_nodo;
}

TipoElemento p_desapilar(Pila pila)
{
    if (p_es_vacia(pila))
    {
        printf("La pila esta vacia, no se pueden desapilar elementos");
        return NULL;
    }

    struct NodoPila *tope_actual = pila->tope;
    TipoElemento elemento = tope_actual->datos;
    pila->tope = tope_actual->siguiente;
    free(tope_actual);
    return elemento;
}

TipoElemento p_tope(Pila pila)
{
    if (p_es_vacia(pila))
    {
        return NULL;
    }

    struct NodoPila *tope_actual = pila->tope;
    return tope_actual->datos;
}

bool p_es_vacia(Pila pila)
{
    return pila->tope == NULL;
}

void p_mostrar(Pila pila)
{
    if (p_es_vacia(pila))
    {
        printf("Pila Vacia \n");
        return;
    }

    Pila pAux = p_crear();
    TipoElemento X = te_crear(0);

    // printf("Contenido de la pila: ");
    //  Recorro la pila desapilandola y pasando sus elementos a la auxiliar
    while (p_es_vacia(pila) != true)
    {
        X = p_desapilar(pila);
        printf("%d ", X->clave);
        p_apilar(pAux, X);
    }

    while (p_es_vacia(pAux) != true)
    {
        X = p_desapilar(pAux);
        p_apilar(pila, X);
    }

    printf("\n");
}

int p_longitud(Pila pila)
{
    int i = 0;
    struct NodoPila *N = pila->tope;
    while (N != NULL)
    {
        i++;
        N = N->siguiente;
    }

    return i;
}

bool p_es_llena(Pila pila)
{
    return (p_longitud(pila) == TAMANIO_MAXIMO_PILA);
}

Pila cargarPila()
{
    Pila pila = p_crear();
    bool cargando = true;

    printf("Por favor ingrese enteros positivos para cargar la lista (Cualquier otro valor para salir)\n");

    int i;
    int aux = scanf("%i", &i);

    while (i >= 0 && aux > 0)
    {
        TipoElemento te = te_crear(i);

        p_apilar(pila, te);
        fflush(stdin);
        aux = scanf("%i", &i);
    }

    return pila;
}