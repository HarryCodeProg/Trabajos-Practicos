#include "tipo_elemento.h"
#include <stdlib.h>

#ifndef TIPO_ELEMENTO_C
#define TIPO_ELEMENTO_C

TipoElemento te_crear(int clave)
{
    TipoElemento te = (TipoElemento)malloc(sizeof(struct TipoElementoRep));
    te->clave = clave;
    te->valor = NULL;
    return te;
}

TipoElemento te_crear_con_valor(int clave, void *valor)
{
    TipoElemento te = (TipoElemento)malloc(sizeof(struct TipoElementoRep));
    te->clave = clave;
    te->valor = valor;
    return te;
}

#endif /* TIPO_ELEMENTO_C */