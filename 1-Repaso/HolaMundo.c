#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool digitoEnNumero(long n, short d)
{
    char numS[3];
    sprintf(numS, "%ld", n);
    for (int i = 0; i <= strlen(numS); i++)
    {
        if ((numS[i] - '0') == d)
        {
            return true;
        }
    }
    return false;
};

// ejercicio 4
#define TAMANO_STRING 50
#define CANT_JUGADORES 11

struct Jugador
{
    char nombre[TAMANO_STRING];
    int edad, partidosJugados;
};

struct Jugador *jugadoresOrdenadosPorCantDePartidos(struct Jugador equipo[])
{
    struct Jugador aux;
    for (int i = 0; i <= CANT_JUGADORES; i++)
    {
        for (int f = 0; f <= CANT_JUGADORES; f++)
        {
            if (equipo[i].partidosJugados > equipo[f].partidosJugados)
            {
                aux = equipo[i];
                equipo[i] = equipo[f];
                equipo[f] = aux;
            }
        }
    }
    return equipo;
};

struct Jugador *jugadoresOrdenadosPorEdad(struct Jugador equipo[])
{
    struct Jugador aux;
    for (int i = 0; i <= CANT_JUGADORES; i++)
    {
        for (int f = 0; f <= CANT_JUGADORES; f++)
        {
            if (equipo[i].edad > equipo[f].edad)
            {
                aux = equipo[i];
                equipo[i] = equipo[f];
                equipo[f] = aux;
            }
        }
    }
    return equipo;
};

float promedioDePartidosJugados(struct Jugador equipo[], int edad)
{
    float promedio = 0;
    int cantE = 0;
    for (int i = 0; i <= CANT_JUGADORES; i++)
    {
        if (equipo[i].edad == edad)
        {
            cantE += equipo[i].partidosJugados;
            promedio = (promedio + equipo[i].partidosJugados);
        }
    }
    return promedio = promedio / cantE;
};

void mostrar(struct Jugador equipo[])
{
    for (int i = 0; i < CANT_JUGADORES; i++)
    {
        printf("nombre: %s ,edad: %d ,partidos: %d \n", equipo[i].nombre, equipo[i].edad, equipo[i].partidosJugados);
    }
}

// ejercicio 4
int global;

int matriz[100][100];

void lectura()
{
    int cliente;
    int cliente_old;
    int anio;
    int mes;
    int hs;
    int lineas = 0;
    int fila = 1;
    int columna = 0;

    FILE *txt;

    txt = fopen("practica-0-ejercicio-6.txt", "r");

    if (txt == NULL)
    {
        printf("error al abrir");
        exit;
    }

    // salteo la primera linea
    char *file_contents = malloc(100);
    fscanf(txt, "%[^\n] ", file_contents);
    printf("%s \n", file_contents);

    // leo la primera linea
    fscanf(txt, "%d %d %d %d", &cliente, &anio, &mes, &hs);
    columna = (anio - 2014);
    matriz[fila][0] = cliente;
    matriz[0][columna] = anio;
    matriz[fila][columna] = hs;
    cliente_old = cliente;

    while (fscanf(txt, "%d %d %d %d", &cliente, &anio, &mes, &hs) != EOF)
    {
        // printf("Linea[ %d ]: %d %d %d %d \n", lineas, cliente, anio, mes, hs);

        // Corte de un nivel por cliente (el resto lo maneja la matriz)
        if (cliente == cliente_old)
        {
            columna = (anio - 2014);
            matriz[fila][columna] = matriz[fila][columna] + hs;
        }
        else
        {
            fila++;
            columna = (anio - 2014);
            matriz[0][columna] = anio;
            matriz[fila][0] = cliente;
            matriz[fila][columna] = hs;
            cliente_old = cliente;
        }
        lineas++;
    }

    fclose(txt);

    printf("\n");
}

void main()
{
    /* long num1 = 123;
     short num2 = 4;
     bool h = digitoEnNumero(num1, num2);
     printf(h ? "true" : "false");
     printf("\n");

     struct Jugador equipo[] = {
         {"Messi", 34, 800},
         {"Ronaldo", 37, 900},
         {"Neymar Jr.", 29, 500},
         {"Mbappe", 22, 200},
         {"Lewandowski", 33, 700},
         {"Salah", 29, 400},
         {"De Bruyne", 30, 600},
         {"van Dijk", 30, 400},
         {"Ramos", 35, 650},
         {"Neuer", 35, 800},
         {"Davies", 20, 100}};

     mostrar(equipo);
     printf("\n -------");
     struct Jugador *equipo2 = jugadoresOrdenadosPorCantDePartidos(equipo);
     printf("\n por cantidad de partidos: ");
     printf("\n");
     mostrar(equipo2);*/
    int i;
    int j;

    // Limpio la matriz global
    for (i = 0; i++; i < 100)
    {
        for (j = 0; j++; j < 100)
        {
            matriz[i][j] = 0;
        }
    }

    // mando a procesar el archivo
    lectura();

    printf("\n\n");

    // Muestro la matriz
    j = 1;
    printf("Años:             ");
    while (matriz[0][j] != 0)
    {
        printf(" %d ", matriz[0][j]);
        j++;
    }

    printf("\n");

    i = 1;
    j = 1;
    while ((i < 100) && (matriz[i][0] != 0))
    {
        j = 1;
        printf("Cliente: %d  |  ", matriz[i][0]);
        while ((j < 10))
        {
            printf(" %d ", matriz[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
};