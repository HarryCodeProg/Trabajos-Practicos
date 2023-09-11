#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "tipo_elemento.h"
#include "tipo_elemento.c"
#include "tabla_hash.h"
#include "tabla_hash_lista_colisiones.c"
#include "arbol-avl.h"
#include "arbol-avl.c"
#include "arbol-binario-busqueda.c"
#include "arbol-binario-busqueda.h"
#include "nodo.h"
#include "nodo.c"
#include "listas.h"
#include "list_cursor.c"

void agregarLista(Lista l, int cantidad)
{
    TipoElemento x;
    for (int i = 1; i <= cantidad; i++)
    {
        printf("ingresa el elemento %d :\n", i);
        int valor;
        scanf("%d", &valor);
        x = te_crear(valor);
        l_agregar(l, x);
    }
}

void insertarClaves(ArbolBinarioBusqueda A, int cantidad)
{
    TipoElemento x;
    for (int i = 1; i <= cantidad; i++)
    {
        printf("ingresa el elemento %d :\n", i);
        int valor;
        scanf("%d", &valor);
        x = te_crear(valor);
        abb_insertar(A, x);
    }
}

void separar(NodoArbol raiz, int nivel, char separador)
{
    if (raiz == NULL)
    {
        return;
    }

    for (int i = 0; i <= nivel; i++)
    {
        printf(" ");
    }

    printf("%c", separador);

    printf(" %d", raiz->datos->clave);
}

void imprimirArbol(ArbolBinarioBusqueda A, NodoArbol actual, int nivel)
{
    if (actual == NULL)
    {
        return;
    }

    separar(n_hijoizquierdo(actual), nivel - 1, '/');
    separar(n_hijoderecho(actual), nivel - 1, '\\');
    printf("\n");
    imprimirArbol(A, n_hijoizquierdo(actual), nivel - 1);
    imprimirArbol(A, n_hijoderecho(actual), nivel - 1);
}

void main()
{
    /*ArbolBinarioBusqueda A = abb_crear();
    printf("cantidad de elementos :\n");
    int cantidad;
    scanf("%d", &cantidad);
    insertarClaves(A, cantidad);

    separar(abb_raiz(A), 20, ' ');
    printf("\n");
    imprimirArbol(A, abb_raiz(A), 20);

    if (abb_EstaEquilibrado(A))
    {
        printf("si\n");
    }
    else
    {
        printf("no\n");
    }*/

    //////////////////////////////////

    Lista l = l_crear();
    printf("cantidad de elementos :\n");
    int cantidad;
    scanf("%d", &cantidad);
    agregarLista(l, cantidad);
    if (esAscendente(l))
    {
        printf("es ascendente\n");
    }
    else
    {
        printf("No es ascendente\n");
    }
}