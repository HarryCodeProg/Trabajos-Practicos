#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo.h"
#include "arbol-binario.h"

struct ArbolBinarioRep
{
    NodoArbol raiz;
    int cantidad_nodos;
};

typedef struct ArbolBinarioRep *ArbolBinario;

ArbolBinario a_crear()
{
    ArbolBinario nuevo_arbol = malloc(sizeof(struct ArbolBinarioRep));
    if (nuevo_arbol != NULL)
    {
        nuevo_arbol->raiz = NULL;
    }
    return nuevo_arbol;
}

bool a_es_vacio(ArbolBinario a)
{
    return (a->raiz == NULL);
}

int contar_nodos(NodoArbol nodo)
{
    if (nodo == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + contar_nodos(n_hijoizquierdo(nodo)) + contar_nodos(n_hijoizquierdo(nodo));
    }
}

int a_cantidad_elementos(ArbolBinario a)
{
    if (a->raiz == NULL)
    {
        return 0;
    }
    else
    {
        return contar_nodos(a->raiz);
    }
}

bool a_es_rama_nula(NodoArbol pa)
{
    return (pa == NULL);
}

NodoArbol a_raiz(ArbolBinario a)
{
    return a->raiz;
}

NodoArbol a_establecer_raiz(ArbolBinario a, TipoElemento te)
{
    NodoArbol nueva_raiz = n_crear(te);
    a->raiz = nueva_raiz;
    return nueva_raiz;
}

NodoArbol a_conectar_hi(ArbolBinario a, NodoArbol pa, TipoElemento te)
{
    NodoArbol nuevo_nodo = n_crear(te);
    nuevo_nodo = n_hijoizquierdo(pa);
    // Incrementar la cantidad de nodos en el árbol 'a'
    a->cantidad_nodos++;
    return nuevo_nodo;
}

NodoArbol a_conectar_hd(ArbolBinario a, NodoArbol pa, TipoElemento te)
{
    NodoArbol nuevo_nodo = n_crear(te);
    nuevo_nodo = n_hijoderecho(pa);
    // Incrementar la cantidad de nodos en el árbol 'a'
    a->cantidad_nodos++;
    return nuevo_nodo;
}

bool a_similar(ArbolBinario a, ArbolBinario b)
{
}

/*void a_eliminar_nodo(ArbolBinario a, NodoArbol n)
{
    if (n == NULL)
    {
        return; // No hay nada que eliminar si el nodo es NULL
    }

    // Caso especial: Nodo con dos hijos válidos
    if (n_hijoizquierdo(n) != NULL && n_hijoderecho(n) != NULL)
    {
        // Encontrar el nodo sucesor (el nodo más a la izquierda en el subárbol derecho)
        NodoArbol sucesor = n_hijoderecho(n);
        while (n_hijoizquierdo(sucesor) != NULL)
        {
            sucesor = n_hijoizquierdo(sucesor);
        }

        // Copiar el elemento del sucesor al nodo que queremos eliminar
        n->elemento = sucesor->elemento;

        // Eliminar el sucesor
        a_eliminar_nodo(a, sucesor);
    }
    // Caso general: Nodo con cero o un hijo
    else
    {
        NodoArbol hijo = (n_hijoizquierdo(n) != NULL) ? n_hijoizquierdo(n) : n_hijoderecho(n);

        // Actualizar el enlace del padre del nodo a eliminar con su hijo correspondiente
        if (n->padre == NULL)
        {
            // El nodo a eliminar es la raíz del árbol
            a->raiz = hijo;
        }
        else if (n->padre->hijo_izquierdo == n)
        {
            // El nodo a eliminar es el hijo izquierdo de su padre
            n->padre->hijo_izquierdo = hijo;
        }
        else
        {
            // El nodo a eliminar es el hijo derecho de su padre
            n->padre->hijo_derecho = hijo;
        }

        if (hijo != NULL)
        {
            // Actualizar el puntero al padre del hijo
            hijo->padre = n->padre;
        }

        // Liberar la memoria del nodo a eliminar
        free(n);

        // Decrementar la cantidad de nodos en el árbol 'a'
        a->cantidad_nodos--;
    }
}*/