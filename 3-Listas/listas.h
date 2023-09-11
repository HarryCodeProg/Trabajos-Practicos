#ifndef LISTAS_H
#define LISTAS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tipo_elemento.h"

#define TAMANIO_MAXIMO 100 // Tamaño máximo del arreglo

struct ListaRep
{
    TipoElemento *valores; // Arreglo de TipoElemento
    int cantidad;          // Cantidad de elementos en la lista
};

typedef struct ListaRep *Lista;

struct IteradorRep
{
    Lista lista; // Lista asociada al iterador
    int indice;  // Índice del elemento actual del iterador
};

typedef struct IteradorRep *Iterador;

Lista l_crear();

bool l_es_vacia(Lista lista);

bool l_es_llena(Lista lista);

int l_longitud(Lista lista);

void l_agregar(Lista lista, TipoElemento elemento);

void l_borrar(Lista lista, int clave);

TipoElemento l_buscar(Lista lista, int clave);

void l_insertar(Lista lista, TipoElemento elemento, int pos);

void l_eliminar(Lista lista, int pos);

TipoElemento l_recuperar(Lista lista, int pos);

void l_mostrarLista(Lista lista);

// Funciones de iterador de la lista
Iterador iterador(Lista lista);

bool hay_siguiente(Iterador iterador);

TipoElemento siguiente(Iterador iterador);

// Crear una lista vacía
Lista l_crear()
{
    Lista lista = (Lista)malloc(sizeof(struct ListaRep));
    lista->valores = (TipoElemento *)calloc(TAMANIO_MAXIMO, sizeof(TipoElemento));
    lista->cantidad = 0;
    return lista;
}

// Verificar si la lista está vacía
bool l_es_vacia(Lista lista)
{
    return lista->cantidad == 0;
}

// Verificar si la lista está llena (en este caso, no se permite)
bool l_es_llena(Lista lista)
{
    return lista->cantidad == TAMANIO_MAXIMO;
}

// Obtener la longitud (cantidad de elementos) de la lista
int l_longitud(Lista lista)
{
    return lista->cantidad;
}

// Agregar un elemento al final de la lista
void l_agregar(Lista lista, TipoElemento elemento)
{
    if (l_es_llena(lista))
    {
        printf("Error: la lista está llena\n");
        return;
    }
    lista->valores[lista->cantidad] = elemento;
    lista->cantidad++;
}

// Borrar un elemento de la lista por su clave
void l_borrar(Lista lista, int clave)
{
    int i;
    for (i = 0; i < lista->cantidad; i++)
    {
        if (lista->valores[i]->clave == clave)
        {
            // Encontramos el elemento, lo eliminamos
            free(lista->valores[i]);
            lista->valores[i] = lista->valores[lista->cantidad - 1];
            lista->cantidad--;
            return;
        }
    }
    printf("Error: elemento con clave %d no encontrado\n", clave);
}

// Buscar un elemento en la lista por su clave
TipoElemento l_buscar(Lista lista, int clave)
{
    int i;
    for (i = 0; i < lista->cantidad; i++)
    {
        if (lista->valores[i]->clave == clave)
        {
            // Encontramos el elemento, lo retornamos
            return lista->valores[i];
        }
    }
    printf("Error: elemento con clave %d no encontrado\n", clave);
    return NULL;
}

// Insertar un elemento en una posición dada de la lista
void l_insertar(Lista lista, TipoElemento elemento, int pos)
{
    if (l_es_llena(lista))
    {
        printf("Error: la lista está llena\n");
        return;
    }
    if (pos < 0 || pos > lista->cantidad)
    {
        printf("Error: posición inválida\n");
        return;
    }
    // Movemos los elementos a la derecha para hacer espacio
    for (int i = lista->cantidad; i > pos; i--)
    {
        lista->valores[i] = lista->valores[i - 1];
    }
    lista->valores[pos] = elemento;
    lista->cantidad++;
}

// Crear un iterador para la lista
Iterador l_iterador_crear(Lista lista)
{
    Iterador iterador = (Iterador)malloc(sizeof(struct IteradorRep));
    iterador->lista = lista;
    iterador->indice = 0;
    return iterador;
}

// Verificar si el iterador ha llegado al final de la lista
bool l_iterador_es_final(Iterador iterador)
{
    return iterador->indice == iterador->lista->cantidad;
}

// Avanzar el iterador al siguiente elemento de la lista
void l_iterador_avanzar(Iterador iterador)
{
    if (!l_iterador_es_final(iterador))
    {
        iterador->indice++;
    }
}

// Obtener el elemento actual del iterador
TipoElemento l_iterador_elemento_actual(Iterador iterador)
{
    if (!l_iterador_es_final(iterador))
    {
        return iterador->lista->valores[iterador->indice];
    }
    else
    {
        printf("Error: iterador al final de la lista\n");
        return NULL;
    }
}

// Destruir el iterador
void l_iterador_destruir(Iterador iterador)
{
    free(iterador);
}

// Destruir la lista
void l_destruir(Lista lista)
{
    for (int i = 0; i < lista->cantidad; i++)
    {
        free(lista->valores[i]);
    }
    free(lista->valores);
    free(lista);
}

Iterador iterador(Lista lista)
{
    Iterador it = (Iterador)malloc(sizeof(struct IteradorRep));
    it->lista = lista;
    it->indice = 0;
    return it;
}

bool hay_siguiente(Iterador iterador)
{
    return iterador->indice < iterador->lista->cantidad;
}

TipoElemento siguiente(Iterador iterador)
{
    TipoElemento te = iterador->lista->valores[iterador->indice];
    iterador->indice++;
    return te;
}

#endif // LISTAS_H
