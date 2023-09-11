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
// #include "tabla_hash_zona_overflow.c"
#include "arbol-avl.h"
#include "arbol-avl.c"
#include "listas.h"
// #include "list_arreglos.c"

///////////////////////////////////////////////////////////////////// punto 2

/////////////////////////////// a

int funcionHash2(int x)
{
    return x % 10;
}

void encadenamiento()
{
    TablaHash tabla = th_crear(10, funcionHash2);

    int entrada[] = {631, 130, 611, 417, 534, 965, 394};
    int tamanoEntrada = sizeof(entrada) / sizeof(entrada[0]);

    for (int i = 0; i < tamanoEntrada; i++)
    {
        TipoElemento te = te_crear(entrada[i]);
        th_insertar(tabla, te);
    }

    th_mostrar(tabla);
}

/////////////////////////////// b
/*
void thInsertarRecolocaciónLineal(TablaHash th, TipoElemento te)
{
    int posicion = th->hash_function(te->clave);

    while (th->tabla[posicion].ocupado)
    {
        posicion = (posicion + 1) % th->capacidad; // Recolocación lineal (a=1)
    }

    th->tabla[posicion].tipo_elemento = te;
    th->tabla[posicion].ocupado = true;
}

void recolocaciónLineal()
{
    TablaHash tabla = th_crear(10, funcionHash2);

    int entrada[] = {631, 130, 611, 417, 534, 965, 394};
    int tamanoEntrada = sizeof(entrada) / sizeof(entrada[0]);

    // Tabla hash por recolocación lineal (a=1)
    printf("Tabla hash por recolocación lineal (a=1):\n");
    for (int i = 0; i < tamanoEntrada; i++)
    {
        TipoElemento te = te_crear(entrada[i]);
        th_insertar(tabla, te);
    }
    th_mostrar(tabla);
}
*/
/////////////////////////////// c

///////////////////////////////////////////////////////////////////// punto 3

/////////////////////////////// a

int funcionHash3(int k)
{
    return (4 + 3 * k) % 10;
}

void clavesTEncadenamiento()
{
    int claves[] = {22, 23, 25, 15, 32, 18, 12, 19, 41, 31};
    int tamano = 10;
    TablaHash th = th_crear(tamano, funcionHash3);

    for (int i = 0; i < sizeof(claves) / sizeof(claves[0]); i++)
    {
        TipoElemento te = te_crear(claves[i]);
        th_insertar(th, te);
    }

    th_mostrar(th);
}

/////////////////////////////// b

/*void clavesTLineal()
{
    int claves[] = {22, 23, 25, 15, 32, 18, 12, 19, 41, 31};
    int tamano = 10;
    TablaHash th = th_crear(tamano, funcionHash3);

    for (int i = 0; i < sizeof(claves) / sizeof(claves[0]); i++)
    {
        TipoElemento te = te_crear(claves[i]);
        int posicion = funcionHash3(claves[i]);
        while (th->tabla[posicion] != NULL)
        {
            posicion = (posicion + 1) % tamano; // Avanzar a la siguiente posición
        }
        th->tabla[posicion] = te;
    }

    mostrar_tabla_hash(th);
}*/

///////////////////////////////////////////////////////////////////// punto 5

int generarClaveRandom(int rangoDesde, int rangoHasta)
{
    int num = rand() % (rangoHasta - rangoDesde + 1) + rangoDesde;
    return num;
}

void comparacionTiempos(int numClaves, int rangoDesde, int rangoHasta, ArbolAVL avl, TablaHash th)
{
    int claves[numClaves];

    for (int j = 0; j < numClaves; j++)
    {
        claves[j] = generarClaveRandom(rangoDesde, rangoHasta);
        TipoElemento te = te_crear(claves[j]);
        avl_insertar(avl, te);
        th_insertar(th, te);
    }

    clock_t inicio_avl = clock();
    for (int j = 0; j < numClaves; j++)
    {
        avl_buscar(avl, claves[j]);
    }
    clock_t fin_avl = clock();
    double tiempo_avl = (double)(fin_avl - inicio_avl) / CLOCKS_PER_SEC;

    clock_t inicio_hash = clock();
    for (int j = 0; j < numClaves; j++)
    {
        th_recuperar(th, claves[j]);
    }
    clock_t fin_hash = clock();
    double tiempo_hash = (double)(fin_hash - inicio_hash) / CLOCKS_PER_SEC;

    printf("Tiempo de acceso en el AVL: %.6f segundos\n", tiempo_avl);
    printf("Tiempo de acceso en la tabla hash: %.6f segundos\n", tiempo_hash);
    printf("\n");

    /*avl_vaciar(avl);

    th_vaciar(th);*/
    // crear estas funciones
}

int funcionHash5(int num)
{
    return num % 10;
}

void punto5()
{
    printf("punto 5: \n");
    int numClaves, repeticiones, rangoDesde, rangoHasta;

    ArbolAVL avl = avl_crear();

    printf("Ingrese el número de claves a generar (entre 1 y 2000): \n");
    scanf("%d", &numClaves);
    while (numClaves < 1 || numClaves > 2000)
    {
        printf("Número de claves inválido.\n");
        printf("Ingrese el número de claves a generar (entre 1 y 2000): \n");
        scanf("%d", &numClaves);
    }

    TablaHash th = th_crear(numClaves, &funcionHash5);

    printf("Ingrese el número de repeticiones: \n");
    scanf("%d", &repeticiones);

    printf("Ingrese el rango desde: \n");
    scanf("%d", &rangoDesde);
    printf("Ingrese el rango desde: \n");
    scanf("%d", &rangoHasta);

    srand(time(NULL));

    for (int i = 0; i < repeticiones; i++)
    {
        printf("Repeticion %d:\n", i + 1);
        comparacionTiempos(numClaves, rangoDesde, rangoHasta, avl, th);
    }
    printf("\n");
}

///////////////////////////////////////////////////////////////////// punto 6

typedef struct
{
    int dni;
    char apellido[50];
    char nombre[50];
} Persona;

int hash_fecha(const char *fecha)
{
    // Se asume que la fecha tiene el formato "dd/MM/yyyy"

    int dia, mes, anio;
    sscanf(fecha, "%d/%d/%d", &dia, &mes, &anio);

    int clave = anio * 10000 + mes * 100 + dia;
    return clave;
}

int intcmp(int a)
{
    return a % 10;
}

void opcion1(TablaHash tabla)
{
    // Cargar datos de personas vacunadas en una fecha
    char fecha[11]; // Cadena para almacenar la fecha en formato "dd/MM/yyyy"
    int dni;
    char apellido[50];
    char nombre[50];

    Lista lista;

    // Obtener los datos de la persona (DNI, apellido, nombre) y la fecha

    printf("Ingrese la fecha (dd/MM/yyyy): ");
    scanf("%s", fecha);
    if (th_recuperar(tabla, hash_fecha(fecha)) == NULL)
    {
        lista = l_crear();
    }
    else
    {
        lista = th_recuperar(tabla, hash_fecha(fecha))->valor;
    }

    bool salir = false;
    while (!salir)
    {
        printf("Ingrese el DNI: ");
        scanf("%d", &dni);

        printf("Ingrese el apellido: ");
        scanf("%s", apellido);

        printf("Ingrese el nombre: ");
        scanf("%s", nombre);

        int clave = hash_fecha(fecha);
        Persona *persona = malloc(sizeof(Persona));
        persona->dni = dni;
        strcpy(persona->apellido, apellido);
        strcpy(persona->nombre, nombre);

        TipoElemento x = te_crear_con_valor(clave, persona);
        l_agregar(lista, x);

        int numO;
        printf("quieres seguir agregando personas al mismo dia (cualquier cosa = si -- 0 = no): \n");
        scanf("%d", &numO);
        if (numO == 0)
        {
            salir = true;
        }
    }

    int clave = hash_fecha(fecha);
    th_insertar(tabla, te_crear_con_valor(clave, lista));
}

void mostrarListaValor(Lista lista)
{
    for (int i = 1; i <= l_longitud(lista); i++)
    {
        Persona *persona = malloc(sizeof(Persona));
        persona = l_recuperar(lista, i)->valor;
        printf("DNI: %d\n", persona->dni);
        printf("Apellido: %s\n", persona->apellido);
        printf("Nombre: %s\n", persona->nombre);
        printf("\n");
    }
    printf("\n");
}

void opcion2(TablaHash tabla)
{
    // Buscar personas vacunadas en una fecha
    char fecha_busqueda[11]; // Cadena para almacenar la fecha en formato "dd/MM/yyyy"
    printf("Ingrese la fecha de búsqueda (dd/MM/yyyy): ");
    scanf("%s", fecha_busqueda);
    int clave_busqueda = hash_fecha(fecha_busqueda);
    TipoElemento elemento = th_recuperar(tabla, clave_busqueda);

    if (elemento != NULL)
    {
        Persona *persona = elemento->valor;
        printf("\n");
        printf("Personas vacunadas en la fecha %s:\n", fecha_busqueda);
        mostrarListaValor(elemento->valor);
    }
    else
    {
        printf("No se encontraron personas vacunadas en la fecha %s\n", fecha_busqueda);
    }
}

void mai6()
{
    TablaHash tabla = th_crear(100, intcmp);
    int opcion;
    do
    {
        printf("\n");
        printf("1. Cargar datos de personas vacunadas\n");
        printf("2. Buscar personas vacunadas en una fecha\n");
        printf("3. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
        {
            opcion1(tabla);
            break;
        }

        case 2:
        {
            opcion2(tabla);
            break;
        }

        case 3:
        {
            break;
        }

        default:
            printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcion != 3);
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
            }
            case 3:
            {
            }
            case 4:
            {
            }
            case 5:
            {
                punto5();
                break;
            }
            case 6:
            {
                mai6();
                break;
            }
            }
        }
    }
}
