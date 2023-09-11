#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include "listas.h"
#include "list_arreglos.c"
#include "colas.h"
#include "cola_punteros.c"
#include "tipo_elemento.h"
#include "tipo_elemento.c"
#include "nodo.h"
#include "nodo.c"
#include "arbol-binario.h"
#include "arbol-binario-punteros.c"
#include "arbol-binario-busqueda.c"
#include "arbol-avl.h"
#include "arbol-avl.c"

NodoArbol cargarArbolBinario(ArbolBinario arbol)
{
    int dato;
    printf("Ingrese el valor del nodo (o -1 para finalizar): ");
    scanf("%d", &dato);

    if (dato == -1)
    {
        return NULL;
    }

    TipoElemento x = te_crear(dato);
    NodoArbol nuevoNodo = n_crear(x);

    if (a_raiz(arbol) == NULL)
    {
        a_establecer_raiz(arbol, nuevoNodo);
    }

    printf("Ingrese los nodos del subárbol izquierdo de %d:\n", dato);
    NodoArbol hIz = n_hijoizquierdo(nuevoNodo);
    hIz = cargarArbolBinario(arbol);

    printf("Ingrese los nodos del subárbol derecho de %d:\n", dato);
    NodoArbol hDe = n_hijoderecho(nuevoNodo);
    hDe = cargarArbolBinario(arbol);

    return nuevoNodo;
}

// Muestra el arbol a partir de un nodo (de ahi hacia abajo)
void pre_orden(NodoArbol N)
{
    TipoElemento x;
    if (N == NULL)
    {
        printf(".");
    }
    else
    {
        x = n_recuperar(N);
        printf(" %d", x->clave);
        pre_orden(n_hijoizquierdo(N));
        pre_orden(n_hijoderecho(N));
    }
}

// Muestra el arbol a partir de un nodo (de ahi hacia abajo)
void in_orden(NodoArbol N)
{
    TipoElemento x;
    if (N == NULL)
    {
        printf(".");
    }
    else
    {
        in_orden(n_hijoizquierdo(N));
        x = n_recuperar(N);
        printf(" %d", x->clave);
        in_orden(n_hijoderecho(N));
    }
}

// Muestra el arbol a partir de un nodo (de ahi hacia abajo)
void post_orden(NodoArbol N)
{
    TipoElemento x;
    if (N == NULL)
    {
        printf(".");
    }
    else
    {
        post_orden(n_hijoizquierdo(N));
        post_orden(n_hijoderecho(N));
        x = n_recuperar(N);
        printf(" %d", x->clave);
    }
}

//---------------------------------------------------------
// Calcula la Altura del Arbol
//---------------------------------------------------------
// Funcion que realmente calcula la altura
void altint(NodoArbol Q, int *h, int c)
{
    if (Q == NULL)
    {
        if (c > *h)
        {
            *h = c;
        }
    }
    else
    {
        altint(n_hijoizquierdo(Q), h, c++);
        altint(n_hijoderecho(Q), h, c++);
    }
}
// funcion que llama a la que calcula la altura
int altura(ArbolBinario A)
{
    int alt = 0;
    altint(a_raiz(A), &alt, 0);
    return alt;
}

// imprime las hojas
void hojasint(NodoArbol Q)
{
    TipoElemento x;

    if (Q == NULL)
    {
    }
    else
    {
        // averigua si es un hoja
        if ((n_hijoizquierdo(Q) == NULL) && (n_hijoderecho(Q) == NULL))
        {
            x = n_recuperar(Q);
            printf("Hoja: %d \n", x->clave);
        }
        // Llamo para el recorrido
        hojasint(n_hijoizquierdo(Q));
        hojasint(n_hijoderecho(Q));
    }
}
void hojas(ArbolBinario A)
{
    hojasint(a_raiz(A));
};

/////////////////////////////////////////////////// punto 2

///////////////////////// a

void nodosTerminales(NodoArbol nodo, Lista hojas)
{
    if (nodo == NULL)
    {
        return;
    }

    if (n_hijoizquierdo(nodo) == NULL && n_hijoderecho(nodo) == NULL)
    {
        TipoElemento x = n_recuperar(nodo);
        l_agregar(hojas, x);
    }

    nodosTerminales(n_hijoizquierdo(nodo), hojas);
    nodosTerminales(n_hijoderecho(nodo), hojas);
}

///////////////////////// b

typedef struct
{
    NodoArbol *nodos;
    int cantidad;
} NodosInteriores;

void interiores(NodoArbol nodo, NodosInteriores *nInteriores)
{
    if (nodo == NULL || n_hijoizquierdo(nodo) == NULL || n_hijoderecho(nodo) == NULL)
    {
        return;
    }

    // El nodo es un nodo interior, lo agregamos a la estructura
    nInteriores->nodos[nInteriores->cantidad++] = nodo;

    // Recorremos el hijo izquierdo y derecho
    interiores(n_hijoizquierdo(nodo), nInteriores);
    interiores(n_hijoderecho(nodo), nInteriores);
}

NodosInteriores nodosInteriores(ArbolBinario a)
{
    NodosInteriores nInteriores;
    nInteriores.nodos = malloc(sizeof(NodoArbol) * a_cantidad_elementos(a));
    nInteriores.cantidad = 0;

    interiores(a_raiz(a), &nInteriores);

    return nInteriores;
}

///////////////////////// c // falta posicion

typedef struct
{
    NodoArbol *nodos;
    int cantidad;
} OcurrenciasClave;

void buscarClave(NodoArbol nodo, TipoElemento clave, OcurrenciasClave *ocurrencias)
{
    if (nodo == NULL)
    {
        return;
    }

    if (nodo->datos == clave)
    {
        ocurrencias->nodos[ocurrencias->cantidad++] = nodo;
    }

    buscarClave(n_hijoizquierdo(nodo), clave, ocurrencias);
    buscarClave(n_hijoderecho(nodo), clave, ocurrencias);
}

OcurrenciasClave buscar_clave(ArbolBinario a, TipoElemento clave)
{
    OcurrenciasClave ocurrencias;
    ocurrencias.nodos = malloc(sizeof(NodoArbol) * a_cantidad_elementos(a));
    ocurrencias.cantidad = 0;

    buscarClave(a_raiz(a), clave, &ocurrencias);

    return ocurrencias;
}

/////////////////////////////////////////////////// punto 3

///////////////////////// a

NodoArbol buscarNodoPadre(ArbolBinario a, NodoArbol nodo)
{
    if (a_es_vacio(a) || nodo == a_raiz(a))
    {
        return NULL;
    }

    return obtenerNodoPadre(a_raiz(a), nodo);
}

NodoArbol obtenerNodoPadre(NodoArbol actual, NodoArbol nodo)
{
    if (actual == NULL)
    {
        return NULL;
    }

    if ((n_hijoizquierdo(actual) != NULL && n_hijoizquierdo(actual) == nodo))
    {
        return actual; //->datos;
    }

    if ((n_hijoderecho(actual) != NULL && n_hijoderecho(actual) == nodo))
    {
        return actual; //->datos;
    }

    NodoArbol resultadoIzquierdo = obtenerNodoPadre(n_hijoizquierdo(actual), nodo);
    NodoArbol resultadoDerecho = obtenerNodoPadre(n_hijoderecho(actual), nodo);

    if (resultadoIzquierdo != NULL)
    {
        return resultadoIzquierdo;
    }

    if (resultadoDerecho != NULL)
    {
        return resultadoDerecho;
    }

    return NULL;
}

///////////////////////// b

void listarHijos(ArbolBinario a, NodoArbol nodo)
{
    if (nodo == NULL)
    {
        printf("El nodo es nulo.\n");
        return;
    }

    printf("Claves de los hijos del nodo %d:\n", nodo->datos);

    if (n_hijoizquierdo(nodo) != NULL)
    {
        printf("Hijo izquierdo: %d\n", n_hijoizquierdo(nodo)->datos);
    }
    else
    {
        printf("No tiene hijo izquierdo.\n");
    }

    if (n_hijoderecho(nodo) != NULL)
    {
        printf("Hijo derecho: %d\n", n_hijoderecho(nodo)->datos);
    }
    else
    {
        printf("No tiene hijo derecho.\n");
    }
}

///////////////////////// c

void listarHermano(ArbolBinario a, NodoArbol nodo)
{
    if (nodo == NULL)
    {
        printf("El nodo es nulo.\n");
        return;
    }

    NodoArbol padre = obtenerNodoPadre(a, nodo);

    if (padre == NULL)
    {
        printf("El nodo no tiene padre (es la raíz).\n");
        return;
    }

    NodoArbol hermano;
    if (n_hijoizquierdo(padre) == nodo)
    {
        hermano = n_hijoderecho(padre);
    }
    else
    {
        hermano = n_hijoizquierdo(padre);
    }

    if (hermano != NULL)
    {
        printf("Clave del hermano: %d\n", hermano->datos);
    }
    else
    {
        printf("El nodo no tiene hermano.\n");
    }
}

///////////////////////// d

int calcularNivel(NodoArbol raiz, NodoArbol nodo, int nivel_actual)
{
    if (raiz == NULL)
    {
        return -1;
    }

    if (raiz == nodo)
    {
        return nivel_actual;
    }

    int nivelIzquierdo = calcularNivel(n_hijoizquierdo(raiz), nodo, nivel_actual + 1);
    if (nivelIzquierdo != -1)
    {
        return nivelIzquierdo;
    }

    int nivelDerecho = calcularNivel(n_hijoderecho(raiz), nodo, nivel_actual + 1);
    if (nivelDerecho != -1)
    {
        return nivelDerecho;
    }
}

int nivelNodo(ArbolBinario arbol, NodoArbol nodo)
{
    int nivel = calcularNivel(a_raiz(arbol), nodo, 0);
    return nivel;
}

///////////////////////// e

int calcularAlturaRama(NodoArbol nodo)
{
    if (nodo == NULL)
    {
        return 0;
    }

    int alturaIzquierda = calcularAlturaRama(nodo->hi);
    int alturaDerecha = calcularAlturaRama(nodo->hd);

    if (alturaIzquierda > alturaDerecha)
    {
        return alturaIzquierda + 1;
    }
    else
    {
        return alturaDerecha + 1;
    }
}

///////////////////////// f

void nodosMismoNivel(NodoArbol nodo, int nivel, int nivelObjetivo)
{
    if (nodo == NULL)
    {
        return;
    }

    if (nivel == nivelObjetivo)
    {
        printf("%d ", n_recuperar(nodo));
    }

    nodosMismoNivel(n_hijoizquierdo(nodo), nivel + 1, nivelObjetivo);
    nodosMismoNivel(n_hijoderecho(nodo), nivel + 1, nivelObjetivo);
}

void listarNodosMismnivel(ArbolBinario arbol, NodoArbol nodo)
{
    if (a_raiz(arbol) == NULL || nodo == NULL)
    {
        printf("arbol o nodo vacio");
        return;
    }

    int nivelObjetivo = 0; // Nivel objetivo en el que se encuentran los nodos

    // Buscar el nivel del nodo dado
    while (nodo != NULL)
    {
        if (nodo == a_raiz(arbol))
        {
            break; // El nodo dado es la raíz, se encuentra en el nivel 0
        }
        nodo = buscarNodoPadre(arbol, nodo);
        nivelObjetivo++;
    }

    nodosMismoNivel(a_raiz(arbol), 0, nivelObjetivo);
}

/////////////////////////////////////////////////// punto 4

///////////////////////// a

Lista arbolNarioAnchura(NodoArbol nodo)
{
    Lista resultado = l_crear();

    if (nodo == NULL)
    {
        return resultado;
    }

    Cola cola = c_crear();
    c_encolar(cola, nodo);
    int pos = 0;

    while (!c_es_vacia(cola))
    {
        NodoArbol nodo = c_desencolar(cola);
        TipoElemento clave = n_recuperar(nodo);

        l_insertar(resultado, clave, pos);
        pos++;

        NodoArbol hijoIzq = n_hijoizquierdo(nodo);
        if (hijoIzq != NULL)
        {
            c_encolar(cola, hijoIzq);
        }

        NodoArbol hijoDer = n_hijoderecho(nodo);
        if (hijoDer != NULL)
        {
            c_encolar(cola, hijoDer);
        }
    }

    return resultado;
}

///////////////////////// b

int narioHojas(NodoArbol raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    if (n_hijoizquierdo(raiz) == NULL)
    {
        return 1;
    }

    int hojas = 0;
    NodoArbol hijo = n_hijoizquierdo(raiz);

    while (hijo != NULL)
    {
        hojas += narioHojas(hijo);
        hijo = n_hijoderecho(hijo);
    }

    return hojas;
}

///////////////////////// c

bool mismaEstructura(NodoArbol a, NodoArbol b)
{
    if (a == NULL && b == NULL)
    {
        return true;
    }

    if (a == NULL || b == NULL)
    {
        return false;
    }

    return mismaEstructura(n_hijoizquierdo(a), n_hijoizquierdo(b)) && mismaEstructura(n_hijoderecho(a), n_hijoderecho(b));
}

///////////////////////// d

NodoArbol narioPadre(NodoArbol raiz, NodoArbol nodoBuscado)
{
    if (raiz == NULL || raiz == nodoBuscado)
    {
        return NULL;
    }

    NodoArbol hijoDirecto = n_hijoizquierdo(raiz);
    while (hijoDirecto != NULL)
    {
        if (hijoDirecto == nodoBuscado)
        {
            return raiz;
        }
        hijoDirecto = n_hijoderecho(hijoDirecto);
    }

    NodoArbol hijo = n_hijoizquierdo(raiz);
    while (hijo != NULL)
    {
        NodoArbol padre = narioPadre(hijo, nodoBuscado);
        if (padre != NULL)
        {
            return padre;
        }
        hijo = n_hijoderecho(hijo);
    }

    return NULL;
}

///////////////////////// e

Lista hermanosNodoNario(NodoArbol raiz, NodoArbol nodo)
{
    Lista resultado = l_crear();
    NodoArbol actual = raiz;
    while (actual != nodo)
    {
        actual = n_hijoizquierdo(raiz);
    }

    NodoArbol agregar = actual;
    while (!a_es_rama_nula(agregar))
    {
        agregar = n_hijoderecho(agregar);
        l_agregar(resultado, n_recuperar(agregar));
    }

    return resultado;
}

/////////////////////////////////////////////////// punto 7

bool EsIgual(TipoElemento dato1, TipoElemento dato2)
{
    return (dato1 == dato2);
}

bool SonEquivalentes(NodoArbol n1, NodoArbol n2)
{
    if (n1 == NULL && n2 == NULL)
    {
        return true;
    }
    else
    {
        TipoElemento dato1 = n_recuperar(n1);
        TipoElemento dato2 = n_recuperar(n2);
        if (EsIgual(dato1, dato2))
        {
            NodoArbol hijo1Izq = n_hijoizquierdo(n1);
            NodoArbol hijo2Izq = n_hijoizquierdo(n2);
            NodoArbol hijo1Der = n_hijoderecho(n1);
            NodoArbol hijo2Der = n_hijoderecho(n2);
            return SonEquivalentes(hijo1Izq, hijo2Izq) && SonEquivalentes(hijo1Der, hijo2Der);
        }
        else
        {
            return false;
        }
    }
}

bool ArbolesEquivalentes(ArbolBinario a1, ArbolBinario a2)
{
    NodoArbol raiz1 = a_raiz(a1);
    NodoArbol raiz2 = a_raiz(a2);
    return SonEquivalentes(raiz1, raiz2);
}

/////////////////////////////////////////////////// punto 8

///////////////////////// a

int alturaArbolNario(NodoArbol raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    int altura_max = 0;

    NodoArbol hijo = n_hijoizquierdo(raiz);
    while (hijo != NULL)
    {
        int altura_hijo = alturaArbolNario(hijo);
        if (altura_hijo > altura_max)
        {
            altura_max = altura_hijo;
        }
        hijo = n_hermanoderecho(hijo);
    }

    return altura_max + 1;
}

///////////////////////// b

int nivelNodoNario(NodoArbol raiz, NodoArbol nodo, int nivel_actual)
{
    if (raiz == NULL || nodo == NULL)
    {
        return -1;
    }

    if (raiz == nodo)
    {
        return nivel_actual;
    }

    NodoArbol hijo = n_hijoizquierdo(raiz);
    while (hijo != NULL)
    {
        int nivel = nivelNodoNario(hijo, nodo, nivel_actual + 1);
        if (nivel != -1)
        {
            return nivel;
        }
        hijo = n_hermanoderecho(hijo);
    }

    return -1;
}

///////////////////////// c

/////////////////////////////////////////////////// punto 9

void convertir(ArbolAVL aAVL, NodoArbol Q)
{
    if (!a_es_rama_nula(Q))
    {
        TipoElemento X = n_recuperar(Q);
        avl_insertar(aAVL, X);
        convertir(aAVL, n_hijoizquierdo(Q));
        convertir(aAVL, n_hijoderecho(Q));
    }
}

void convertirRecursivo(ArbolBinario aA)
{
    ArbolAVL aAVL = avl_crear();
    convertir(aAVL, a_raiz(aA));
}

/////////////////////////////////////////////////// punto 10

void cargarRandom(int rango, int cantidad, ArbolAVL arAvl, ArbolBinarioBusqueda arAbb)
{
    for (int i = 0; i < cantidad; i++)
    {
        int numero = rand() % rango;
        TipoElemento X = te_crear(numero);
        avl_insertar(arAvl, X);
        abb_insertar(arAbb, X);
    }
}

/*int altura(NodoArbol raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }
    else
    {
        int alturaIzq = altura(n_hijoizquierdo(raiz));
        int alturaDer = altura(n_hijoderecho(raiz));
        int altura = 1;
        if (alturaIzq > alturaDer)
        {
            altura += alturaIzq;
        }
        else
        {
            altura += alturaDer;
        }
        return altura;
    }
}*/

void main()
{
    bool salir = false;
    while (!(salir))
    {
        srand(time(NULL));
        int opcion;
        printf("Por favor ingrese un numero entero para acceder a un punto (del 2 al 10) o pulse 0 para salir: \n");
        scanf("%d", &opcion);
        if (opcion == 0)
        {
            salir = true;
        }
        else
        {
            switch (opcion)
            {
            case 2:
            {
                ArbolBinario arbolPunto2 = a_crear();
                int sub;
                printf("acceder a un subpunto (del 1 al 3): \n");
                scanf("%d", &sub);
                switch (sub)
                {
                case 1:
                {
                    printf("arbol: \n");
                    in_orden(a_raiz(arbolPunto2));
                    Lista listaPunto2 = l_crear();
                    nodosTerminales(a_raiz(arbolPunto2), listaPunto2);
                    printf("lista: \n");
                    l_mostrarLista(listaPunto2);
                    break;
                }
                case 2:
                {
                    printf("arbol: \n");
                    in_orden(a_raiz(arbolPunto2));
                    nodosInteriores(arbolPunto2);
                    break;
                }
                case 3:
                {
                    int numeroBuscar;
                    printf("escribir numero a buscar ocurrencias \n");
                    scanf("%d", &numeroBuscar);
                    buscar_clave(arbolPunto2, numeroBuscar);
                    break;
                }
                }
            }
            case 3:
            {
                ArbolBinario arbolPunto3 = a_crear();
                NodoArbol nodoPunto3;
                int sub;
                printf("acceder a un subpunto (del 1 al 3): \n");
                scanf("%d", &sub);
                int numNodo;
                printf("escribir clave del nodo \n");
                scanf("%d", &numNodo);
                TipoElemento x = te_crear(numNodo);
                nodoPunto3 = n_crear(x);
                switch (sub)
                {
                case 1:
                {
                    buscarNodoPadre(arbolPunto3, nodoPunto3);
                    break;
                }
                case 2:
                {
                }
                case 3:
                {
                }
                case 4:
                {
                }
                case 5:
                {
                }
                case 6:
                {
                }
                }
            }
            case 4:
            {

                break;
            }
            case 7:
            {
            }
            case 8:
            {
            }
            case 9:
            {
            }
            case 10:
            {
            }
            }
        }
    }
}