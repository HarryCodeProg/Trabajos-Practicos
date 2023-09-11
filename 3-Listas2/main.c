#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "listas.h"
#include "tipo_elemento.h"
#include <ctype.h>
#include <time.h>
#include <string.h>
// #include "lista_point.c"
// #include "lista_cursor.c"
#include "list_arreglos.c"
#include "tipo_elemento.c"

///////////////////////////////////// punto 2
////////////////// a
int obtener_menor(Lista lista, int *posicion_ordinal)
{
    if (l_es_vacia(lista))
    {
        return 0; // o cualquier otro valor para indicar error
    }

    TipoElemento minimo = l_recuperar(lista, 1);
    int posicion_minimo = 1;

    for (int i = 2; i <= l_longitud(lista); i++)
    {
        TipoElemento actual = l_recuperar(lista, i);
        if (actual.clave < minimo.clave)
        {
            minimo = actual;
            posicion_minimo = i;
        }
    }

    *posicion_ordinal = posicion_minimo;
    return minimo.clave;
}

////////////////// b
int obtener_maximo(Lista lista, int *repeticiones)
{
    if (l_es_vacia(lista))
    {
        return 0; // o cualquier otro valor para indicar error
    }

    TipoElemento maximo = l_recuperar(lista, 1);
    int cantidad_repeticiones = 1;

    for (int i = 2; i <= l_longitud(lista); i++)
    {
        TipoElemento actual = l_recuperar(lista, i);
        if (actual.clave > maximo.clave)
        {
            maximo = actual;
            cantidad_repeticiones = 1;
        }
        else if (actual.clave == maximo.clave)
        {
            cantidad_repeticiones++;
        }
    }

    *repeticiones = cantidad_repeticiones;
    return maximo->clave;
}

////////////////// c

float promedio_recursivo(Lista lista)
{
    int suma = 0;
    int cantidad = 0;

    if (l_es_vacia(lista))
    {
        return 0.0; // o cualquier otro valor para indicar error
    }

    // Función auxiliar para calcular la suma y la cantidad de elementos
    void suma_y_cantidad(Lista lista, int *suma, int *cantidad)
    {
        if (!l_es_vacia(lista))
        {
            *suma += l_recuperar(lista, 1);
            *cantidad += 1;
            suma_y_cantidad(l_resto(lista), suma, cantidad);
        }
    }

    suma_y_cantidad(lista, &suma, &cantidad);

    return (float)suma / cantidad;
}

///////////////////////////////////// punto 3

bool esMultiplo(Lista L1, Lista L2)
{
    if (l_longitud(L1) != l_longitud(L2))
    {
        return false; // si las listas no tienen la misma longitud, no pueden ser múltiplos
    }

    Iterador iter1 = iterador(L1);
    Iterador iter2 = iterador(L2);
    int escalar = -1;

    while (hay_siguiente(iter1) && hay_siguiente(iter2))
    {
        TipoElemento num1 = siguiente(iter1);
        TipoElemento num2 = siguiente(iter1);

        if (num2.clave % num1.clave != 0)
        {
            return false; // si alguno de los elementos no se divide de manera exacta, no son múltiplos
        }
        else
        {
            int tmp_escalar = num2.clave / num1.clave;
            if (escalar == -1)
            {
                escalar = tmp_escalar; // si es el primer elemento, se guarda el escalar
            }
            else if (escalar != tmp_escalar)
            {
                return false; // si los escalares no coinciden, no son múltiplos
            }
        }
    }

    return true;
}

///////////////////////////////////// punto 4

int comparar_listas(Lista l1, Lista l2)
{
    int contador_l1 = 0, contador_l2 = 0;
    Iterador iterador_l1 = iterador(l1);
    Iterador iterador_l2 = iterador(l2);

    while (hay_siguiente(iterador_l1) && hay_siguiente(iterador_l2))
    {
        TipoElemento elem_l1 = siguiente(iterador_l1);
        TipoElemento elem_l2 = siguiente(iterador_l2);

        if (elem_l1.clave > elem_l2.clave)
        {
            contador_l1++;
        }
        else if (elem_l1.clave < elem_l2.clave)
        {
            contador_l2++;
        }
    }

    while (hay_siguiente(iterador_l1))
    {
        contador_l1++;
        siguiente(iterador_l1);
    }

    while (hay_siguiente(iterador_l2))
    {
        contador_l2++;
        siguiente(iterador_l2);
    }

    if (contador_l1 > contador_l2)
    {
        return 1;
    }
    else if (contador_l1 < contador_l2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

///////////////////////////////////// punto 5

typedef struct
{
    double valor;
    int potencia;
} Coeficiente;

typedef Coeficiente TipoElemento;

Lista crear_lista_coeficientes()
{
    Lista coeficientes = l_crear();
    // Agregar coeficientes al polinomio
    Coeficiente c1 = {2.0, 1};
    Coeficiente c2 = {1.0, 0};
    l_agregar(coeficientes, c1);
    l_agregar(coeficientes, c2);
    return coeficientes;
}

double calcular_polinomio(Lista coeficientes, double x)
{
    double resultado = 0.0;
    Iterador it = iterador(coeficientes);
    while (hay_siguiente(it))
    {
        Coeficiente c = siguiente(it);
        resultado += c.valor * pow(x, c.potencia);
    }
    return resultado;
}

Lista calcular_valores_polinomio(Lista coeficientes, double inicio, double fin, double intervalo)
{
    Lista valores = l_crear();
    for (double x = inicio; x <= fin; x += intervalo)
    {
        double y = calcular_polinomio(coeficientes, x);
        TipoElemento elemento;
        elemento.valor = y;
        l_agregar(valores, elemento);
    }
    return valores;
}

///////////////////////////////////// punto 6
void cargarLista(Lista auxL, char *ed)
{
    TipoElemento X;
    X.clave = ed;
    l_agregar(auxL, X);
}

bool sublista(Lista primerL, Lista segunL)
{
    int i = 1;
    TipoElemento Q = l_recuperar(segunL, i);
    TipoElemento X;
    while (hay_siguiente(primerL))
    {
        X = l_recuperar(segunL, i);
        if (l_buscar(primerL, X->clave) != X)
        {
            return false;
            break;
        }
        Q = l_siguiente(segunL, i++);
    }
    return true;
}

void main()
{
}
