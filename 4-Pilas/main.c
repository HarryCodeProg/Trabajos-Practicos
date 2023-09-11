#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "tipo_elemento.h"
#include "tipo_elemento.c"
#include "pilas.h"
#include "pilas_arreglos.c"

Pila p_intercambiar(Pila p_aux)
{
    TipoElemento x;

    Pila pila = p_crear();

    while (!p_es_vacia(p_aux))
    {
        x = p_desapilar(p_aux);
        p_apilar(pila, x);
    }

    return pila;
}

void cambiar(Pila p1, Pila p2)
{

    while (!p_es_vacia(p2))
    {
        TipoElemento x = p_desapilar(p2);
        p_apilar(p1, x);
    }
}

int p_longitud(Pila pila)
{
    int longitud = 0;
    Pila auxiliar = p_crear();

    while (!p_es_vacia(pila))
    {
        p_apilar(auxiliar, p_desapilar(pila));
        longitud++;
    }

    while (!p_es_vacia(auxiliar))
    {
        p_apilar(pila, p_desapilar(auxiliar));
    }

    return longitud;
}

void cargarPilaManual(Pila pila, int num)
{
    TipoElemento X = te_crear(num);
    p_apilar(pila, X);
}

void cargarPilaManualCantidad(Pila pila, int cantidad)
{
    int numeroAgregar;
    for (int i = 0; i < cantidad; i++)
    {
        printf("ingresar numero a agregar \n");
        scanf("%d", &numeroAgregar);
        TipoElemento X = te_crear(numeroAgregar);
        p_apilar(pila, X);
    }
}

//////////////// punto 2

void cargarAleatorio(Pila pilaPunt1, int cantidad)
{

    int num_aleatorio;

    srand(time(NULL));
    for (int i = 0; i < cantidad; i++)
    {
        num_aleatorio = rand() % 100 + 1;
        TipoElemento X = te_crear(num_aleatorio);
        p_apilar(pilaPunt1, X);
    }
}

/////////// a

bool buscarClave(Pila P, int num)
{
    Pila pilaAux = p_crear();
    while (!(p_es_vacia(P)))
    {
        TipoElemento X = p_desapilar(P);
        p_apilar(pilaAux, X);
        if (X->clave == num)
        {
            cambiar(P, pilaAux);

            return true;
        }
    }
    cambiar(P, pilaAux);
    return false;
}

/////////// b

Pila insertarNuevo(Pila P, int pos, int num)
{
    Pila pilaN = p_crear();
    int i = p_longitud(P);
    while (!(p_es_vacia(P)) || i != pos)
    {
        TipoElemento X = p_desapilar(P);
        p_apilar(pilaN, X);
        i--;
    }
    TipoElemento X = te_crear(num);
    p_apilar(P, X);
    while (!(p_es_vacia(pilaN)))
    {
        TipoElemento X = p_desapilar(pilaN);
        p_apilar(P, X);
    }
    return P;
}

/////////// c

void eliminarElemento(Pila pila, int num)
{
    Pila pilaAux = p_crear();
    bool encontrado = false;

    while (!p_es_vacia(pila))
    {
        TipoElemento elementoActual = p_desapilar(pila);
        if (elementoActual->clave == num && !encontrado)
        {
            encontrado = true;
        }
        else
        {
            p_apilar(pilaAux, elementoActual);
        }
    }

    while (!p_es_vacia(pilaAux))
    {
        TipoElemento elementoAux = p_desapilar(pilaAux);
        p_apilar(pila, elementoAux);
    }
}

/////////// e

Pila duplicar(Pila P)
{
    Pila pAux = p_crear();
    Pila res = p_crear();

    while (!(p_es_vacia(P)))
    {
        TipoElemento X = p_desapilar(P);
        p_apilar(res, X);
        p_apilar(pAux, X);
    }
    cambiar(P, pAux);
    cambiar(pAux, res);
    return pAux;
}

//////////////// punto 3

bool sonPilasIguales(Pila pila1, Pila pila2)
{
    Pila pilaAux = p_crear();
    bool sonIguales = true;

    while (!p_es_vacia(pila1) && !p_es_vacia(pila2) && sonIguales)
    {
        TipoElemento elemento1 = p_desapilar(pila1);
        TipoElemento elemento2 = p_desapilar(pila2);

        if ((elemento1->clave != elemento2->clave) || (((p_es_vacia(pila1) && !p_es_vacia(pila2))) || (!p_es_vacia(pila1) && p_es_vacia(pila2))))
        {
            p_apilar(pila1, elemento1);
            p_apilar(pila2, elemento2);
            sonIguales = false;
            break;
        }

        p_apilar(pilaAux, elemento1);
    }

    while (!p_es_vacia(pilaAux))
    {
        TipoElemento elemento = p_desapilar(pilaAux);
        p_apilar(pila1, elemento);
        p_apilar(pila2, elemento);
    }

    return sonIguales;
}

//////////////// punto 4

/*int chartonum(char c)
{
    switch (c)
    {
    case 'A':
        return 10;
        break;
    case 'B':
        return 11;
        break;
    case 'C':
        return 12;
        break;
    case 'D':
        return 13;
        break;
    case 'E':
        return 14;
        break;
    case 'F':
        return 15;
        break;
    default:
        return 0;
        break;
    }
}

char numtochar(int c)
{
    switch (c)
    {
    case 10:
        return 'A';
        break;
    case 11:
        return 'B';
        break;
    case 12:
        return 'C';
        break;
    case 13:
        return 'D';
        break;
    case 14:
        return 'E';
        break;
    case 15:
        return 'F';
        break;
    default:
        return '?';
        break;
    }
}

int NumtoDec(char *numero, int BaseO)
{
    int exp = strlen(numero) - 1;
    int count = 0;
    for (int i = 0; i < strlen(numero); i++)
    {
        int aux;
        if ((numero[i] >= 65) && (numero[i] <= 70))
        {
            aux = chartonum(numero[i]);
        }
        else
        {
            char temp[2] = {numero[i], '\0'};
            strNum(temp, (void *)&aux, false, false);
        }
        count += (aux * (int)pow(BaseO, exp));
        exp--;
    }
    return count;
}

char *DectoBase(int numero, int Base)
{
    Pila aux = p_crear();
    TipoElemento X;
    bool flag = true;
    int cant = 0;
    while (flag)
    {
        if (numero < Base)
        {
            X = te_crear(numero);
            flag = false;
        }
        else
        {
            X = te_crear(numero % Base);
        }
        p_apilar(aux, X);
        numero = numero / Base;
        cant++;
    }

    char *resultado = (char *)malloc(sizeof(char) * cant);
    int index = 0;
    char *str = (char *)malloc(sizeof(char));

    while (!(p_es_vacia(aux)))
    {
        X = p_desapilar(aux);
        if ((X->clave >= 10) && (X->clave <= 15))
        {
            resultado[index] = numtochar(X->clave);
        }
        else
        {
            sprintf(str, "%d", X->clave);
            resultado[index] = str[0];
        }
        index++;
    }
    return resultado;
}

char *NumToBase(char *Numero, int BaseOriginal, int BasePasar)
{
    int numero = NumtoDec(Numero, BaseOriginal);
    return DectoBase(numero, BasePasar);
}*/

//////////////// punto 5

Pila invertir(Pila P)
{
    Pila pAux = p_crear();
    Pila resultado = p_crear();
    while (!(p_es_vacia(P)))
    {
        TipoElemento X = p_desapilar(P);
        p_apilar(pAux, X);
        p_apilar(resultado, X);
    }
    cambiar(P, pAux);
    return resultado;
}

//////////////// punto 6

Pila eliminarIterativa(Pila pilaOriginal, TipoElemento eliminar)
{
    Pila pNueva = p_crear();
    Pila pAux = p_crear();
    while (!p_es_vacia(pilaOriginal))
    {
        TipoElemento X = p_desapilar(pilaOriginal);
        p_apilar(pAux, X);
        if (X->clave != eliminar)
        {
            p_apilar(pNueva, X);
        }
    }
    // Invertir la nueva pila para que quede en el orden correcto
    Pila pila_invertida = p_crear();
    while (!p_es_vacia(pNueva))
    {
        p_apilar(pila_invertida, p_desapilar(pNueva));
    }

    cambiar(pilaOriginal, pAux);

    return pila_invertida;
}

void eliminarRecursivaAux(Pila pilaOriginal, TipoElemento eliminar, Pila pNueva)
{
    if (!p_es_vacia(pilaOriginal))
    {
        TipoElemento elemento = p_desapilar(pilaOriginal);
        if (elemento->clave != eliminar)
        {
            p_apilar(pNueva, elemento);
        }

        eliminarRecursivaAux(pilaOriginal, eliminar, pNueva);
    }
}

Pila eliminarRecursiva(Pila pilaOriginal, TipoElemento eliminar)
{
    Pila pNueva = p_crear();
    eliminarRecursivaAux(pilaOriginal, eliminar, pNueva);
    Pila pila_invertida = p_crear();
    while (!p_es_vacia(pNueva))
    {
        p_apilar(pila_invertida, p_desapilar(pNueva));
    }

    return pila_invertida;
}

//////////////// punto 7

Pila elementosComunes(Pila pila1, Pila pila2)
{
    Pila pilaAuxiliar = p_crear();
    Pila pilaResultado = p_crear();
    Pila pila1Copia = p_crear();

    while (!p_es_vacia(pila1))
    {
        TipoElemento elemento1 = p_desapilar(pila1);
        p_apilar(pila1Copia, elemento1);
        bool encontrado = false;
        Pila pila2Copia = p_crear();

        while (!p_es_vacia(pila2))
        {
            TipoElemento elemento2 = p_desapilar(pila2);
            if (elemento2->clave == elemento1->clave)
            {
                encontrado = true;
            }
            p_apilar(pila2Copia, elemento2);
        }

        while (!p_es_vacia(pila2Copia))
        {
            TipoElemento elemento2 = p_desapilar(pila2Copia);
            p_apilar(pila2, elemento2);
        }

        if (encontrado)
        {
            p_apilar(pilaAuxiliar, elemento1);
        }
    }

    while (!p_es_vacia(pilaAuxiliar))
    {
        TipoElemento elementoAux = p_desapilar(pilaAuxiliar);
        p_apilar(pilaResultado, elementoAux);
    }

    cambiar(pila1, pila1Copia);

    return pilaResultado;
}

//////////////// punto 8

Pila Repeticiones(Pila pila)
{
    Pila valoresUnicos = p_crear();
    Pila repeticiones = p_crear();

    while (!p_es_vacia(pila))
    {
        TipoElemento valorActual = p_desapilar(pila);
        TipoElemento tope = p_tope(valoresUnicos);

        if (p_es_vacia(valoresUnicos) || tope->clave != valorActual->clave)
        {
            p_apilar(valoresUnicos, te_crear(valorActual->clave));
            p_apilar(repeticiones, te_crear(1));
        }
        else
        {
            TipoElemento repTope = p_desapilar(repeticiones);
            repTope->clave++;
            p_apilar(repeticiones, repTope);
        }
    }

    Pila repNueva = p_crear();

    while (!p_es_vacia(valoresUnicos) && !p_es_vacia(repNueva))
    {
        TipoElemento valor = p_desapilar(valoresUnicos);
        TipoElemento cantidad = p_desapilar(repNueva);
        TipoElemento par = te_crear_con_valor(valor->clave, cantidad->valor);
        p_apilar(repNueva, par);
    }

    return repNueva;
}

void main()
{
    bool salir = false;
    while (!(salir))
    {
        int opcion;
        printf("Por favor ingrese un numero entero para acceder a un punto (del 2 al 8) o pulse 0 para salir: \n");
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
                Pila p1 = p_crear();
                int cantidad;
                printf("ingresar cantidad de numeros a agregar \n");
                scanf("%d", &cantidad);
                cargarAleatorio(p1, cantidad);

                printf("pila original:");
                p_mostrar(p1);
                printf("\n");

                int sub;
                printf("acceder a un subpunto (del 1 al 6): \n");
                scanf("%d", &sub);

                switch (sub)
                {
                case 1:
                {
                    int numBuscar;
                    printf("ingresar numero a buscar: \n");
                    scanf("%d", &numBuscar);
                    if (buscarClave(p1, numBuscar))
                    {
                        printf("el numero Si esta en la pila \n");
                    }
                    else
                    {
                        printf("el numero No esta en la pila \n");
                    }
                    printf("pila original:");
                    p_mostrar(p1);
                    break;
                }
                case 2:
                {
                    int num;
                    int pos;
                    printf("ingresar numero a insertar: \n");
                    scanf("%d", &num);
                    printf("ingresar posicion: \n");
                    scanf("%d", &pos);

                    printf("pila original: \n");
                    p_mostrar(p1);
                    printf("pila nueva: \n");
                    p_mostrar(insertarNuevo(p1, num, pos));
                    break;
                }
                case 3:
                {
                    int num;
                    printf("ingresar numero a eliminar: \n");
                    scanf("%d", &num);
                    eliminarElemento(p1, num);
                    printf("pila original: \n");
                    p_mostrar(p1);
                    break;
                }
                case 4:
                {
                }
                case 5:
                {
                    printf("pila original:");
                    p_mostrar(p1);
                    printf("\n");

                    printf("pila duplicada:");
                    p_mostrar(duplicar(p1));
                    printf("\n");

                    printf("pila original:");
                    p_mostrar(p1);
                    printf("\n");
                    break;
                }
                case 6:
                {
                }
                }
                break;
            }
            case 3:
            {
                Pila p3 = p_crear();
                Pila p3Segunda = p_crear();
                int cantidad;
                printf("ingresar cantidad de numeros a agregar \n");
                scanf("%d", &cantidad);
                printf("cargar pila 1 \n");
                cargarPilaManualCantidad(p3, cantidad);

                printf("cargar pila 2 \n");
                cargarPilaManualCantidad(p3Segunda, cantidad);

                printf("pila 1:");
                p_mostrar(p3);
                printf("\n");

                printf("pila 2:");
                p_mostrar(p3Segunda);
                printf("\n");

                if (sonPilasIguales(p3, p3Segunda))
                {
                    printf("-----son iguales----- \n");
                }
                else
                {
                    printf("-----no son iguales----- \n");
                }
                printf("\n");

                printf("pila 1:");
                p_mostrar(p3);
                printf("\n");

                printf("pila 2:");
                p_mostrar(p3Segunda);
                printf("\n");

                break;
            }
            case 4:
            {
                /* printf("%s", NumToBase("12AB", 16, 2));
                 break;*/
            }
            case 5:
            {
                Pila p5 = p_crear();
                int cantidad;
                printf("ingresar cantidad de numeros a agregar \n");
                scanf("%d", &cantidad);
                int numeroAgregar;
                for (int i = 0; i < cantidad; i++)
                {
                    printf("ingresar numero a agregar \n");
                    scanf("%d", &numeroAgregar);
                    cargarPilaManual(p5, numeroAgregar);
                }
                printf("pila original:");
                p_mostrar(p5);
                printf("\n");

                printf("pila invertida:");
                p_mostrar(invertir(p5));
                printf("\n");

                printf("pila original:");
                p_mostrar(p5);
                printf("\n");
                break;
            }
            case 6:
            {
                Pila p6 = p_crear();
                int cantidad;
                printf("ingresar cantidad de numeros a agregar \n");
                scanf("%d", &cantidad);
                cargarAleatorio(p6, cantidad);

                printf("pila original:");
                p_mostrar(p6);
                printf("\n");

                int numeroEliminar;
                printf("ingresar numero a eliminar \n");
                scanf("%d", &numeroEliminar);
                printf("iterativo: \n");
                p_mostrar(eliminarIterativa(p6, numeroEliminar));
                printf("recursivo: \n");
                p_mostrar(eliminarRecursiva(p6, numeroEliminar));
                break;
            }
            case 7:
            {
                Pila p7 = p_crear();
                Pila p7Segunda = p_crear();
                int cantidad;
                printf("ingresar cantidad de numeros a agregar \n");
                scanf("%d", &cantidad);
                printf("cargar pila 1 \n");
                cargarPilaManualCantidad(p7, cantidad);
                p_mostrar(p7);
                printf("cargar pila 2 \n");
                cargarPilaManualCantidad(p7Segunda, cantidad);
                printf("pila 1:");
                p_mostrar(p7);
                printf("\n");

                printf("pila 2:");
                p_mostrar(p7Segunda);
                printf("\n");

                printf("elementos comunes:");
                p_mostrar(elementosComunes(p7, p7Segunda));
                printf("\n");

                printf("pila 1:");
                p_mostrar(p7);
                printf("\n");

                printf("pila 2:");
                p_mostrar(p7Segunda);
                printf("\n");
                break;
            }
            case 8:
            {
                Pila p8 = p_crear();
                int cantidad;
                printf("ingresar cantidad de numeros a agregar \n");
                scanf("%d", &cantidad);
                cargarPilaManualCantidad(p8, cantidad);
                p_mostrar(p8);
                p_mostrar(Repeticiones(p8));
                break;
            }
            }
        }
    }
}