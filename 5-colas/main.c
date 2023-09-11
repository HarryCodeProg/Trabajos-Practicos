#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "tipo_elemento.h"
#include "tipo_elemento.c"
#include "pilas.h"
#include "colas.h"
#include "listas.h"
#include "lista_arreglos.c"
#include "cola_punteros.c"
#include "pilas_apuntadores.c"

void cambiarCola(Cola c, Cola cAux)
{
    while (!c_es_vacia(cAux))
    {
        TipoElemento X = c_desencolar(cAux);
        c_encolar(c, X);
    }
    free(cAux);
}

int contar(Cola c)
{
    int cont = 0;
    Cola cAux = c_crear();
    while (!(c_es_vacia))
    {
        TipoElemento X = c_desencolar(c);
        c_encolar(cAux, X);
        cont++;
    }
    cambiarCola(c, cAux);
    free(cAux);
    return cont;
}

void cargarColaManualCantidad(Cola c, int cantidad)
{
    int numeroAgregar;
    for (int i = 0; i < cantidad; i++)
    {
        printf("ingresar numero a agregar \n");
        scanf("%d", &numeroAgregar);
        TipoElemento X = te_crear(numeroAgregar);
        c_encolar(c, X);
    }
}

void cargarAleatorio(Cola c, int cantidad)
{
    int num_aleatorio;
    for (int i = 0; i < cantidad; i++)
    {
        num_aleatorio = rand() % 100 + 1;
        TipoElemento X = te_crear(num_aleatorio);
        c_encolar(c, X);
    }
}

////////////////////////////////////////////////// punto 2

///////////////////// a

bool buscarElemento(Cola c, int num)
{
    bool esta = false;
    Cola cAux = c_crear();
    while ((!c_es_vacia) && (!esta))
    {
        TipoElemento X = c_desencolar(c);
        c_encolar(cAux, X);
        if (X->clave == num)
        {
            esta = true;
        }
    }
    cambiarCola(c, cAux);
    free(cAux);
    return esta;
}

///////////////////// b

Cola agregarElemento(Cola c, int num, int pos)
{
    int cont = 0;
    Cola cAux = c_crear();
    while (!(c_es_vacia))
    {
        TipoElemento X = c_desencolar(c);
        c_encolar(cAux, X);
        if (cont == pos)
        {
            c_encolar(c, X);
            break;
        }
        cont++;
    }
    cambiarCola(c, cAux);
    return c;
}

///////////////////// c

Cola sacarElementos(Cola c, int num)
{
    Cola cAux = c_crear();
    Cola res = c_crear();
    while (!c_es_vacia(c))
    {
        TipoElemento X = c_desencolar(c);
        c_encolar(cAux, X);
        if (X->clave != num)
        {
            c_encolar(res, X);
        }
    }
    cambiarCola(c, cAux);
    return res;
}

///////////////////// d (longitud ya hecho)

///////////////////// e

Cola copiar(Cola c)
{
    Cola copia = c_crear();
    Cola cAux = c_crear();
    while (!c_es_vacia(c))
    {
        TipoElemento X = c_desencolar(c);
        c_encolar(copia, X);
        c_encolar(cAux, X);
    }
    cambiarCola(c, cAux);
    return copia;
}

///////////////////// f

Cola invertir(Cola c)
{
    Cola invertida = c_crear();
    Cola cAux = c_crear();
    while (!c_es_vacia(c))
    {
        TipoElemento X = c_desencolar(c);
        c_encolar(cAux, X);
        c_encolar_al_frente(invertida, X);
    }
    cambiarCola(c, cAux);
    return invertida;
}

////////////////////////////////////////////////// punto 3

bool colasIguales(Cola cola1, Cola cola2)
{
    Cola cAux = c_crear();
    bool iguales = true;
    while ((!(c_es_vacia(cola1))) || iguales)
    {
        TipoElemento X1 = c_desencolar(cola1);
        TipoElemento X2 = c_desencolar(cola2);
        c_encolar(cAux, X1);
        if (X1->clave != X2->clave)
        {
            iguales = false;
        }
    }
    cambiarCola(cola1, cAux);
    return iguales;
}

////////////////////////////////////////////////// punto 4

Cola eliminarRepetidos(Cola cola)
{
    Cola colaResultante = c_crear(); // Creamos una nueva cola para almacenar los elementos no repetidos
    Cola colaAuxiliar = c_crear();   // Creamos una cola auxiliar para realizar las comparaciones

    while (!c_es_vacia(cola))
    {
        TipoElemento elemento = c_desencolar(cola); // Desencolamos un elemento de la cola original

        // Verificamos si el elemento ya está en la cola auxiliar
        bool repetido = false;
        while (!c_es_vacia(cola))
        {
            TipoElemento elementoAux = c_desencolar(cola);
            c_encolar(colaAuxiliar, elementoAux);

            if (elemento == elementoAux)
            {
                repetido = true;
                break;
            }
        }

        // Si no está repetido, lo encolamos en la cola resultante
        if (!repetido)
        {
            c_encolar(colaResultante, elemento);
        }

        // Devolvemos los elementos a la cola original desde la cola auxiliar
        while (!c_es_vacia(colaAuxiliar))
        {
            TipoElemento elementoAux = c_desencolar(colaAuxiliar);
            c_encolar(cola, elementoAux);
        }
    }

    return colaResultante;
}

////////////////////////////////////////////////// punto 5

bool esDivisorTotal(int divisor, Cola cola)
{
    Cola colaAuxiliar = c_crear();
    bool esDivisorTotal = true;

    while (!c_es_vacia(cola))
    {
        int elemento = c_desencolar(cola);

        if (elemento != divisor && elemento % divisor != 0)
        {
            esDivisorTotal = false;
        }

        c_encolar(colaAuxiliar, elemento);
    }

    while (!c_es_vacia(colaAuxiliar))
    {
        int elementoAux = c_desencolar(colaAuxiliar);
        c_encolar(cola, elementoAux);
    }

    return esDivisorTotal;
}

bool esDivisorParcial(int divisor, Cola cola)
{
    Cola colaAuxiliar = c_crear();
    int cantidadElementos = 0;
    int cantidadDivisibles = 0;

    while (!c_es_vacia(cola))
    {
        int elemento = c_desencolar(cola);

        if (elemento != divisor && elemento % divisor == 0)
        {
            cantidadDivisibles++;
        }

        cantidadElementos++;
        c_encolar(colaAuxiliar, elemento);
    }

    while (!c_es_vacia(colaAuxiliar))
    {
        int elementoAux = c_desencolar(colaAuxiliar);
        c_encolar(cola, elementoAux);
    }

    return cantidadDivisibles >= cantidadElementos / 2;
}

void obtenerDivisores(Cola cola)
{
    Cola colaAuxiliar = c_crear();

    while (!c_es_vacia(cola))
    {
        int elemento = c_desencolar(cola);

        if (esDivisorTotal(elemento, cola) || esDivisorParcial(elemento, cola))
        {
            c_encolar(colaAuxiliar, elemento);
        }
    }

    printf("Divisores totales y parciales encontrados:\n");
    c_mostrar(colaAuxiliar);
}

////////////////////////////////////////////////// punto 6

void cambiarPila(Pila p1, Pila p2)
{
    while (!p_es_vacia(p2))
    {
        TipoElemento x = p_desapilar(p2);
        p_apilar(p1, x);
    }
    free(p2);
}

bool buscarElementoPila(Pila p, int num)
{
    bool esta = false;
    Pila pAux = p_crear();
    while ((!p_es_vacia(p)) && (!esta))
    {
        TipoElemento X = p_desapilar(p);
        p_apilar(pAux, X);
        if (X->clave == num)
        {
            esta = true;
        }
    }
    cambiarPila(p, pAux);
    free(pAux);
    return esta;
}

void cargarPilaAleatorio(Pila pila, int cantidad, int rango)
{
    int num_aleatorio;
    for (int i = 0; i < cantidad; i++)
    {
        num_aleatorio = rand() % rango + 1;
        while (num_aleatorio > rango)
        {
            num_aleatorio = rand() % rango + 1;
        }

        while (buscarElementoPila(pila, num_aleatorio))
        {
            num_aleatorio = rand() % 100 + 1;
        }
        TipoElemento X = te_crear(num_aleatorio);
        p_apilar(pila, X);
    }
}

void cargarColaAleatorio(Cola cola, int cantidad, int rango)
{
    int num_aleatorio;
    for (int i = 0; i < cantidad; i++)
    {
        num_aleatorio = rand() % rango + 1;
        while (num_aleatorio > rango)
        {
            num_aleatorio = rand() % rango + 1;
        }

        while (buscarElemento(cola, num_aleatorio))
        {
            num_aleatorio = rand() % 100 + 1;
        }
        TipoElemento X = te_crear(num_aleatorio);
        c_encolar(cola, X);
    }
}

int pila_longitud(Pila pila)
{
    int longitud = 0;
    Pila auxiliar = p_crear();

    while (!p_es_vacia(pila))
    {
        p_apilar(auxiliar, p_desapilar(pila));
        longitud++;
    }
    cambiarPila(pila, auxiliar);
    return longitud;
}

Lista valoresComunes(Pila p, Cola c)
{
    Lista l = l_crear();
    Pila pAux = p_crear();
    Cola cAux = c_crear();
    char *cadena = malloc(10 * sizeof(char));
    int posCola = contar(c);
    int posPila = pila_longitud(p);
    while (!p_es_vacia(p))
    {
        TipoElemento xp = p_desapilar(p);
        p_apilar(pAux, xp);
        posPila--;
        while (!c_es_vacia(c))
        {
            TipoElemento xc = c_desencolar(c);
            c_encolar(cAux, xc);
            posCola--;
            if (xp->clave == xc->clave)
            {
                sprintf(cadena, ":%d:%d", posPila, posCola);
                TipoElemento xl = te_crear_con_valor(xp->clave, cadena);
                l_agregar(l, xl);
            }
        }
    }
    cambiarPila(p, pAux);
    cambiarCola(c, cAux);
    free(pAux);
    free(cAux);
    return l;
}

void mostrarListaValor(Lista lista)
{
    int i = 1;
    while (!l_es_vacia(lista))
    {
        TipoElemento X = l_recuperar(lista, i);
        printf("(%d : %c)", X->clave, X->valor);
        l_eliminar(lista, X);
        i++;
    }
}

////////////////////////////////////////////////// punto 7

void atenderClientes(int tiempoAtencion, Cola cola1, Cola cola2, Cola cola3)
{
    int cliente = 1;
    bool hayClientes = true;

    while (hayClientes)
    {
        hayClientes = false;

        // Atender clientes en cola1
        while (!c_es_vacia(cola1))
        {
            int tiempoCliente = c_desencolar(cola1);
            printf("Cliente %d Cola 1\n", cliente++);
            if (tiempoCliente > tiempoAtencion)
            {
                tiempoCliente -= tiempoAtencion;
                c_encolar(cola1, tiempoCliente);
                hayClientes = true;
            }
        }

        // Atender clientes en cola2
        while (!c_es_vacia(cola2))
        {
            int tiempoCliente = c_desencolar(cola2);
            printf("Cliente %d Cola 2\n", cliente++);
            if (tiempoCliente > tiempoAtencion)
            {
                tiempoCliente -= tiempoAtencion;
                c_encolar(cola2, tiempoCliente);
                hayClientes = true;
            }
        }

        // Atender clientes en cola3
        while (!c_es_vacia(cola3))
        {
            int tiempoCliente = c_desencolar(cola3);
            printf("Cliente %d Cola 3\n", cliente++);
            if (tiempoCliente > tiempoAtencion)
            {
                tiempoCliente -= tiempoAtencion;
                c_encolar(cola3, tiempoCliente);
                hayClientes = true;
            }
        }
    }
}

void main()
{
    bool salir = false;
    while (!(salir))
    {
        srand(time(NULL));
        int opcion;
        printf("Por favor ingrese un numero entero para acceder a un punto (del 2 al 7) o pulse 0 para salir: \n");
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
                Cola c2 = c_crear();
                int cantidad;
                printf("ingresar cantidad de numeros a agregar \n");
                scanf("%d", &cantidad);
                cargarAleatorio(c2, cantidad);

                printf("cola original:");
                c_mostrar(c2);
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
                    if (buscarElemento(c2, numBuscar))
                    {
                        printf("el numero Si esta en la pila \n");
                    }
                    else
                    {
                        printf("el numero No esta en la pila \n");
                    }
                    printf("\n");
                    printf("cola original:");
                    c_mostrar(c2);
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
                Cola c = c_crear();
                Pila p = p_crear();
                int cantidad;
                printf("ingresar cantidad de numeros a agregar \n");
                scanf("%d", &cantidad);
                int rango;
                printf("ingresar rango de numeros a agregar \n");
                scanf("%d", &rango);

                cargarPilaAleatorio(p, cantidad, rango);
                cargarColaAleatorio(c, cantidad, rango);

                printf("cola original:");
                c_mostrar(c);
                printf("\n");

                printf("pila original:");
                p_mostrar(p);
                printf("\n");

                printf("lista resultado:");
                mostrarListaValor(valoresComunes(p, c));
                printf("\n");
                break;
            }
            case 7:
            {
                printf("punto 7");
                int tiempoAtencion = 10;
                Cola cola1 = c_crear();
                Cola cola2 = c_crear();
                Cola cola3 = c_crear();

                // Agregar clientes a las colas
                TipoElemento X = te_crear(40);
                c_encolar(cola1, X);
                X->valor = 20;
                c_encolar(cola1, X);
                X->valor = 30;
                c_encolar(cola1, X);
                X->valor = 20;
                c_encolar(cola2, X);
                X->valor = 10;
                c_encolar(cola2, X);
                X->valor = 10;
                c_encolar(cola3, X);
                X->valor = 10;
                c_encolar(cola3, X);
                X->valor = 10;
                c_encolar(cola3, X);

                // Atender los clientes
                atenderClientes(tiempoAtencion, cola1, cola2, cola3);
                break;
            }
            }
        }
    }
}