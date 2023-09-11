#include "listas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tipo_elemento.h"

void cargarLista(Lista auxL, char *ed)
{
    TipoElemento X;
    X.clave = ed;
    l_agregar(auxL, X);
}

/*char *mostrarLista(Lista auxL)
{
    TipoElemento Q = l_primera(auxL);
    TipoElemento X;
    char *S = malloc(sizeof(char) * 100);
    strcpy(S, "");
    char c[2] = "";
    while (Q != POS_NULA)
    {
        X = l_recuperar(auxL, Q);
        char *strElem = te_armar_string_con_separador(X, c);
        strcat(S, strElem);
        Q = l_siguiente(auxL, Q);
    }
    S[strlen(S) - 1] = '\0'; // eliminar la última coma
    return S;
}*/

bool sublista(Lista primerL, Lista segunL)
{
    TipoElemento Q = l_primera(segunL);
    TipoElemento X;
    while (hay_siguiente(primerL))
    {
        X = l_recuperar(segunL, Q);
        if (l_buscar(primerL, X.clave) != X)
        {
            return false;
            break;
        }
        Q = l_siguiente(segunL, Q);
    }
    return true;
}

void main()
{
}