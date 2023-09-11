#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaracion de una variable global
int global;

int matriz[100][100];

int main()
{
    int i;
    int j;

    // Limpio la matriz global
    for(i=0;i++;i<100){
        for(j=0;j++;j<100) {
            matriz[i][j] = 0;
        }
    }

    // mando a procesar el archivo
    global = lectura();

    printf("Lineas Totales Leidas: %d \n", global);
    printf("\n\n");

    // Muestro la matriz
    j = 1;
    printf("Años:             ");
    while (matriz[0][j] != 0) {
        printf(" %d ", matriz[0][j]);
        j++;
    }

    printf("\n");

    i = 1;
    j = 1;
    while ((i<100) && (matriz[i][0] != 0)) {
        j = 1;
        printf("Cliente: %d  |  ", matriz[i][0]);
        while ((j<10)) {
            printf(" %d ", matriz[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }

    return 0;
}

//--------------------------------------------------------------------
// lectura del archivo del TP0 - Ejercicio 6
//--------------------------------------------------------------------
int lectura() {
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

    if (txt == NULL) {
        printf("Error de Apertura !!! \n");
        return -1;
    }

    // salteo la primera linea
    char *file_contents = malloc(100);
    fscanf(txt, "%[^\n] ", file_contents);
    printf("%s \n",file_contents);

    // leo la primera linea
    fscanf(txt, "%d %d %d %d", &cliente, &anio, &mes, &hs);
    columna = (anio - 2014);
    matriz[fila][0] = cliente;
    matriz[0][columna] = anio;
    matriz[fila][columna] = hs;
    cliente_old = cliente;

    while (fscanf(txt, "%d %d %d %d", &cliente, &anio, &mes, &hs) != EOF) {
        printf("Linea[ %d ]: %d %d %d %d \n", lineas, cliente, anio, mes, hs);

        // Corte de un nivel por cliente (el resto lo maneja la matriz)
        if (cliente == cliente_old) {
            columna = (anio - 2014);
            matriz[fila][columna] = matriz[fila][columna] + hs;
        }
        else {
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

    return lineas;
}
