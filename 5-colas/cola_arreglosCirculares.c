#include "tipo_elemento.h"
#include "colas.h"
#include <stdio.h>
#include <stdlib.h>

static const int TAMANIO_MAXIMO = 11;

struct ColaRep
{
    TipoElemento *valores;
    int frente;
    int final;
    int longitud;
};

int paso(int pos)
{
    return ((pos % TAMANIO_MAXIMO) + 1);
}

Cola c_crear()
{
    Cola nuevaCola = (Cola)malloc(sizeof(struct ColaRep));
    nuevaCola->valores = calloc((TAMANIO_MAXIMO + 1), sizeof(TipoElemento));
    nuevaCola->longitud = 0;
    nuevaCola->frente = 1;
    nuevaCola->final = TAMANIO_MAXIMO;
    return nuevaCola;
}

void c_encolar(Cola cola, TipoElemento elemento)
{
    if (c_es_llena(cola))
        return;

    cola->final = paso(cola->final); // Avanzo hacia el final de la cola
    cola->valores[cola->final] = elemento;
    cola->longitud += 1;
}

TipoElemento c_desencolar(Cola cola)
{
    if (c_es_vacia(cola))
        return NULL;

    TipoElemento elemento = cola->valores[cola->frente];
    cola->frente = paso(cola->frente);
    cola->longitud -= 1;

    return elemento;
}

bool c_es_vacia(Cola cola)
{
    return (paso(cola->final) == cola->frente);
}

bool c_es_llena(Cola cola)
{
    return (paso(paso(cola->final)) == cola->frente);
}

TipoElemento c_recuperar(Cola cola)
{
    TipoElemento x;

    if (c_es_vacia(cola))
        x = NULL;
    else
        x = cola->valores[cola->frente];

    return x;
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

int longitud(Cola cola)
{
    return cola->longitud;
}

void c_encolar_al_frente(Cola cola, TipoElemento elemento)
{
    int nueva_posicion = (cola->frente - 1 + cola->longitud) % cola->longitud;
    cola->valores[nueva_posicion] = elemento;
    cola->frente = nueva_posicion;

    if (cola->final == -1)
    {
        cola->final = nueva_posicion;
    }
}
