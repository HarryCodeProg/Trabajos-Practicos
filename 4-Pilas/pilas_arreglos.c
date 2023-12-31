#include "pilas.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Tipo_Elemento.c"

static const int TAM_MAX = 100;

struct PilaRep
{
    TipoElemento *valores;
    unsigned int tope;
};

Pila p_crear()
{
    Pila n_p = (Pila)malloc(sizeof(struct PilaRep));
    n_p->valores = calloc((TAM_MAX + 1), sizeof(TipoElemento));
    n_p->tope = 0;
    return n_p;
}

void p_apilar(Pila pila, TipoElemento elemento)
{
    if (p_es_llena(pila))
    {
        return;
    }
    pila->tope++;
    pila->valores[pila->tope] = elemento;
}

TipoElemento p_desapilar(Pila pila)
{
    if (p_es_vacia(pila))
    {
        return NULL;
    }
    TipoElemento x = pila->valores[pila->tope];
    pila->tope--;
    return x;
}

TipoElemento p_tope(Pila pila)
{
    if (p_es_vacia(pila))
    {
        return NULL;
    }
    TipoElemento x = pila->valores[pila->tope];
    return x;
}

bool p_es_vacia(Pila pila)
{
    return (pila->tope <= 0);
}

/*int p_longitud(Pila p){
    int i=0;
    struct PilaRep *p= p->valores[i];
    while (p!=NULL)
    {
        i++;
        p=p->valores[i];
    }
    return i;

}*/

bool p_es_llena(Pila pila)
{
    return (pila->tope == TAM_MAX);
}

void p_mostrar(Pila pila)
{
    while (p_es_vacia(pila))
    {
        printf("\n-----es vacia-----\n");
        return;
    }

    Pila p_aux = p_crear();
    TipoElemento x = te_crear(0);

    // printf("\n--ELEMENTOS DE LA PILA--\n");
    printf("\n {");
    while (p_es_vacia(pila) != true)
    {
        x = p_desapilar(pila);
        printf("%i,", x->clave);
        p_apilar(p_aux, x);
    }
    printf("}\n");

    while (p_es_vacia(p_aux) != true)
    {
        x = p_desapilar(p_aux);
        p_apilar(pila, x);
    }
}
