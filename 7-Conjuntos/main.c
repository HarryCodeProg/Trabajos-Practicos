#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "listas.h"
#include "list_arreglos.c"
#include "tipo_elemento.h"
#include "tipo_elemento.c"
#include "nodo.h"
#include "nodo.c"
#include "arbol-avl.h"
#include "arbol-avl.c"
#include "conjuntos.h"
#include "conjuntos_listas.c"
// #include "conjuntos_avl.c"

void cargarAleatorio(Conjunto cj, int cantidad, int rango)
{
    int numeroAleatorio;
    for (int i = 0; i < cantidad; i++)
    {
        numeroAleatorio = rand() % rango;
        TipoElemento x = te_crear(numeroAleatorio);
        cto_agregar(cj, x);
    }
    printf("conjunto cargado de aleatorios: \n");
    cto_mostrar(cj);
    printf("\n");
}

/////////////////////////////////////////////////////// punto 2

void agregarManual(Conjunto cj, int cantidad)
{
    int numero;
    for (int i = 0; i < cantidad; i++)
    {
        printf("Ingrese un número entero: \n");
        scanf("%d", &numero);
        TipoElemento x = te_crear(numero);
        cto_agregar(cj, x);
        printf("\n");
        cto_mostrar(cj);
    }
}

void validarPer(Conjunto cj, int per, int i)
{
    if (cto_pertenece(cj, per))
    {
        printf("elemento pertenece al conjunto %d \n", i);
    }
    else
    {
        printf("elemento NO pertenece al conjunto %d \n", i);
    }
}

void punto2()
{
    printf("punto 2: \n");
    Conjunto cj1 = cto_crear();
    Conjunto cj2 = cto_crear();
    printf("ingrese la cantidad de elementos: \n");
    int cantidad;
    scanf("%d", &cantidad);
    printf("cargar conjunto 1: \n");
    agregarManual(cj1, cantidad);
    printf("cargar conjunto 2: \n");
    agregarManual(cj2, cantidad);

    printf("ingrese elemento para pertenecia: \n");
    int per;
    scanf("%d", &per);
    printf("pertenencia: \n");
    validarPer(cj1, per, 1);
    validarPer(cj2, per, 2);

    printf("union: \n");
    cto_union(cj1, cj2);

    printf("inserccion: \n");
    cto_interseccion(cj1, cj2);

    printf("diferencia: \n");
    cto_diferencia(cj1, cj2);
}

/////////////////////////////////////////////////////// punto 3

Lista coleccion(int con, int cantidad, int rango)
{
    Lista li = l_crear();
    for (int i = 1; i <= con; i++)
    {
        Conjunto cj = cto_crear();
        cargarAleatorio(cj, cantidad, rango);
        l_agregar(li, te_crear_con_valor(i, cj));
    }
    return li;
}

Conjunto coleccionUnion(Lista lista)
{
    Conjunto res = l_recuperar(lista, 1)->valor;
    for (int i = 2; i <= l_longitud(lista); i++)
    {
        res = cto_union(res, l_recuperar(lista, i)->valor);
    }
    return res;
}

Conjunto coleccionInter(Lista lista)
{
    Conjunto res = l_recuperar(lista, 1)->valor;
    for (int i = 2; i <= l_longitud(lista); i++)
    {
        res = cto_interseccion(res, l_recuperar(lista, i)->valor);
    }
    return res;
}

void punto3()
{
    printf("punto 3: \n");
    printf("ingrese la cantidad de conjuntos: \n");
    int con;
    scanf("%d", &con);

    printf("ingrese la cantidad de elementos: \n");
    int cantidad;
    scanf("%d", &cantidad);

    printf("ingrese el rango de las claves: \n");
    int rango;
    scanf("%d", &rango);

    Lista li = coleccion(con, cantidad, rango);
    printf("union de coleccion: \n");
    cto_mostrar(coleccionUnion(li));
    printf("\n");

    printf("interseccion de coleccion: \n");
    cto_mostrar(coleccionInter(li));
}

/////////////////////////////////////////////////////// punto 4

bool esSubconjunto(Conjunto conjuntoA, Conjunto conjuntoB)
{
    for (int i = 0; i < cto_cantidad_elementos(conjuntoA); i++)
    {
        bool presente = false;
        for (int j = 0; j < cto_cantidad_elementos(conjuntoB) - 1; j++)
        {
            if (cto_recuperar(conjuntoA, i)->clave == cto_recuperar(conjuntoB, i)->clave)
            {
                presente = true;
                break;
            }
        }
        if (!presente)
        {
            return false;
        }
    }
    return true;
}

void punto4()
{
    printf("punto 4: \n");
    Conjunto cj1 = cto_crear();
    Conjunto cj2 = cto_crear();
    Conjunto cj3 = cto_crear();
    printf("ingrese la cantidad de elementos: \n");
    int cantidad;
    scanf("%d", &cantidad);
    printf("cargar conjunto 1: \n");
    agregarManual(cj1, cantidad);
    printf("cargar conjunto 2: \n");
    agregarManual(cj2, cantidad);
    printf("cargar conjunto 3: \n");
    agregarManual(cj3, cantidad);

    bool esTransitivo = esSubconjunto(cj1, cj2) && esSubconjunto(cj2, cj3);

    printf("La propiedad de transitividad es : %s\n", esTransitivo ? "VERDADERA" : "FALSA");
}

/////////////////////////////////////////////////////// punto 5

bool elementoPresente(Conjunto conjunto, TipoElemento elemento)
{
    for (int i = 1; i <= cto_cantidad_elementos(conjunto); i++)
    {
        if (cto_recuperar(conjunto, i)->clave == elemento->clave)
        {
            return true;
        }
    }
    return false;
}

Conjunto diferenciaSimetrica(Conjunto conjuntoA, Conjunto conjuntoB)
{
    Conjunto resultado = cto_crear();

    for (int i = 0; i <= cto_cantidad_elementos(conjuntoA) - 1; i++)
    {
        if (!elementoPresente(conjuntoB, cto_recuperar(conjuntoA, i)))
        {
            cto_agregar(resultado, cto_recuperar(conjuntoA, i));
        }
    }

    return resultado;
}

void punto5()
{
    printf("punto 5: \n");
    Conjunto cj1 = cto_crear();
    Conjunto cj2 = cto_crear();
    printf("ingrese la cantidad de elementos: \n");
    int cantidad;
    scanf("%d", &cantidad);
    printf("cargar conjunto 1: \n");
    agregarManual(cj1, cantidad);
    printf("cargar conjunto 2: \n");
    agregarManual(cj2, cantidad);

    printf("Conjunto diferencia simetrica: \n");
    cto_mostrar(diferenciaSimetrica(cj1, cj2));
}

/////////////////////////////////////////////////////// punto 6

bool esSubconjuntoPropio(Conjunto conjuntoA, Conjunto conjuntoB)
{
    bool subconjunto = true;

    for (int i = 0; i < cto_cantidad_elementos(conjuntoA) - 1; i++)
    {
        TipoElemento elemento = cto_recuperar(conjuntoA, i);
        bool presente = false;
        for (int j = 0; j < cto_cantidad_elementos(conjuntoB) - 1; j++)
        {
            if (cto_recuperar(conjuntoB, j)->clave == elemento->clave)
            {
                presente = true;
                break;
            }
        }
        if (!presente)
        {
            subconjunto = false;
            break;
        }
    }

    return subconjunto;
}

void punto6()
{
    printf("punto 6: \n");
    Conjunto cj1 = cto_crear();
    Conjunto cj2 = cto_crear();
    printf("ingrese la cantidad de elementos del conjunto 1: \n");
    int cantidad;
    scanf("%d", &cantidad);
    printf("cargar conjunto 1: \n");
    agregarManual(cj1, cantidad);
    printf("ingrese la cantidad de elementos del conjunto 2: \n");
    int cantidad2;
    scanf("%d", &cantidad2);
    printf("cargar conjunto 2: \n");
    agregarManual(cj2, cantidad2);

    bool esSubPropio = esSubconjuntoPropio(cj1, cj2);

    printf(" %s\n", esSubPropio ? "es subconjunto propio" : "NO es subconjunto propio");
}

/////////////////////////////////////////////////////// punto 7

bool esSubconjuntoParcial(Conjunto conjuntoA, Conjunto conjuntoB)
{
    int contador = 0;
    for (int i = 0; i < cto_cantidad_elementos(conjuntoA) - 1; i++)
    {
        TipoElemento elemento = cto_recuperar(conjuntoA, i);
        for (int j = 0; j < cto_cantidad_elementos(conjuntoB) - 1; j++)
        {
            if (cto_recuperar(conjuntoB, j)->clave == elemento->clave)
            {
                contador++;
                break;
            }
        }
    }
    return contador >= cto_cantidad_elementos(conjuntoA) / 2;
}

void punto7()
{
    printf("punto 7: \n");
    Conjunto cj1 = cto_crear();
    Conjunto cj2 = cto_crear();
    Conjunto cj3 = cto_crear();
    printf("ingrese la cantidad de elementos del conjunto 1: \n");
    int cantidad;
    scanf("%d", &cantidad);
    printf("cargar conjunto 1: \n");
    agregarManual(cj1, cantidad);
    printf("ingrese la cantidad de elementos del conjunto 2: \n");
    int cantidad2;
    scanf("%d", &cantidad2);
    printf("cargar conjunto 2: \n");
    agregarManual(cj2, cantidad2);
    printf("ingrese la cantidad de elementos del conjunto 3: \n");
    int cantidad3;
    scanf("%d", &cantidad3);
    printf("cargar conjunto 3: \n");
    agregarManual(cj3, cantidad3);

    bool esSubParcial = esSubconjuntoParcial(cj1, cj3);

    printf(" %s\n", esSubParcial ? "es subconjunto " : "NO es subconjunto ");
}

/////////////////////////////////////////////////////// punto 8

bool sonConjuntosIguales(Conjunto conjuntoA, Conjunto conjuntoB)
{
    if (cto_cantidad_elementos(conjuntoA) != cto_cantidad_elementos(conjuntoB))
    {
        return false;
    }

    for (int i = 1; i < cto_cantidad_elementos(conjuntoA); i++)
    {
        TipoElemento elemento = cto_recuperar(conjuntoA, i);
        bool presente = false;
        for (int j = 1; j < cto_cantidad_elementos(conjuntoB); j++)
        {
            if (cto_recuperar(conjuntoB, j)->clave == elemento->clave)
            {
                presente = true;
                break;
            }
        }
        if (!presente)
        {
            return false;
        }
    }

    return true;
}

void main()
{
    bool salir = false;
    while (!(salir))
    {
        srand(time(NULL));
        int opcion;
        printf("Por favor ingrese un numero entero para acceder a un punto (del 2 al 6) o pulse 0 para salir: \n");
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
                punto2();
                break;
            }
            case 3:
            {
                punto3();
                break;
            }
            case 4:
            {
                punto4();
                break;
            }
            case 5:
            {
                punto5();
                break;
            }
            case 6:
            {
                punto6();
                break;
            }
            case 7:
            {
                punto7();
                break;
            }
            case 8:
            {
                // punto8();
                break;
            }
            }
        }
    }
}
