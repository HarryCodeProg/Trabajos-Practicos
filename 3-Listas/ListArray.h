#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tipos.h"

#define MIN 1
#define MAX 2000
#define Nulo 0

typedef int PosicionLista; // Se asume que LongInt es un alias de int en Pascal

typedef struct
{
    // Definir la estructura del elemento de la lista
    // según la implementación en Pascal
} TipoElemento;

typedef int Resultado; // Se asume que Resultado es un alias de int en Pascal

typedef int TipoDatosClave; // Se asume que TipoDatosClave es un alias de int en Pascal

typedef struct
{
    TipoElemento *Elementos;
    PosicionLista Inicio;
    PosicionLista Final;
    int Q_Items;
    TipoDatosClave TDatoDeLaClave;
    long int Size;
} Lista;

// Declaración de funciones
Resultado Crear(Lista *lista, TipoDatosClave avTipoClave, long int alSize);
bool EsVacia(Lista *lista);
bool EsLLena(Lista *lista);
Resultado Agregar(Lista *lista, TipoElemento X);
Resultado Insertar(Lista *lista, TipoElemento X, PosicionLista P);
Resultado Eliminar(Lista *lista, PosicionLista P);
PosicionLista Buscar(Lista *lista, TipoElemento X);
PosicionLista Siguiente(Lista *lista, PosicionLista P);
PosicionLista Anterior(Lista *lista, PosicionLista P);
PosicionLista Ordinal(int PLogica);
TipoElemento Recuperar(Lista *lista, PosicionLista P);
Resultado Actualizar(Lista *lista, TipoElemento X, PosicionLista P);
bool ValidarPosicion(Lista *lista, PosicionLista P);
void RetornarClaves(Lista *lista, char *claves);
Resultado LlenarClavesRandom(Lista *lista, long int alSize, int RangoDesde, int RangoHasta);
PosicionLista Comienzo(Lista *lista);
PosicionLista Fin(Lista *lista);
long int CantidadElementos(Lista *lista);
TipoDatosClave DatoDeLaClave(Lista *lista);
long int SizeList(Lista *lista);
long int MaxSizeList(Lista *lista);
void Sort(Lista *lista, bool Ascendente);

Resultado Crear(Lista *lista, TipoDatosClave avTipoClave, long int alSize)
{
    if (alSize < MIN || alSize > MAX)
    {
        return CError;
    }

    if (alSize >= MIN && alSize <= MAX)
    {
        lista->Inicio = Nulo;
        lista->Final = Nulo;
        lista->Q_Items = 0;
        lista->TDatoDeLaClave = avTipoClave;
        lista->Size = alSize;
        lista->Elementos = (TipoElemento *)malloc((alSize + 1) * sizeof(TipoElemento));

        return OK;
    }
}

// Control de lista vacía
bool EsVacia(Lista *lista)
{
    return (lista->Inicio == Nulo);
}

// Control de lista llena
bool EsLLena(Lista *lista)
{
    return (lista->Final == lista->Size);
}

// Agrega un ítem al final de la lista
Resultado Agregar(Lista *lista, TipoElemento X)
{
    if (X.TipoDatoClave(X->Clave) != lista->TDatoDeLaClave)
    {
        return ClaveIncompatible;
    }

    if (EsLLena(lista))
    {
        return LLena;
    }
    else
    {
        lista->Final += 1;
        lista->Elementos[lista->Final] = X;
        lista->Q_Items++;
        if (EsVacia(lista))
        {
            lista->Inicio = lista->Final;
        }
        return OK;
    }
}

Resultado Lista_Insertar(TipoElemento X, PosicionLista P, TipoElemento Elementos[], int Final, int Q_Items)
{
    PosicionLista Q;

    Resultado Insertar = CError;

    // Controla que el Tipo de Dato de la Clave sea Homogeneo a la Lista
    if (TipoDatoClave(X.Clave) != TDatoDeLaClave)
    {
        Insertar = ClaveIncompatible;
        return Insertar;
    }

    // ahora lo Inserto
    if (EsLLena)
    {
        Insertar = LLena;
    }
    else
    {
        if (ValidarPosicion(P))
        {
            for (Q = Final; Q >= P; Q--)
            {
                Elementos[Q + 1] = Elementos[Q]; // Genera el hueco dentro de la lista
            }
            // Ahora pego el dato en la posicion recibida (P)
            Elementos[P] = X;
            Final++;
            Q_Items++;
            Insertar = OK;
        }
        else
        {
            Insertar = PosicionInvalida;
        }
    }

    return Insertar;
}

PosicionLista Lista_Ordinal(int PLogica, int Q_Items)
{
    PosicionLista Ordinal = Nulo;
    if (PLogica > 0 && PLogica <= Q_Items)
    {
        Ordinal = PLogica;
    }
    return Ordinal;
}

Resultado Lista_Eliminar(PosicionLista P, TipoElemento Elementos[], int Final, int Q_Items, int Inicio, int Size, int TDatoDeLaClave)
{
    PosicionLista Q;
    Resultado Eliminar = CError;
    if (EsVacia)
    {
        Eliminar = Vacia;
    }
    else
    {
        if (ValidarPosicion(P))
        {
            for (Q = P; Q < (Final - 1); Q++)
            {
                Elementos[Q] = Elementos[Q + 1]; // Aplasta el item a borrar
            }
            // Actualizo el final y la cantidad
            Final--;
            Q_Items--;
            if (Final < Inicio)
            {
                Crear(TDatoDeLaClave, Size); // Si borrar el unico que hay se crea vacia
            }
            Eliminar = OK;
        }
        else
        {
            Eliminar = PosicionInvalida;
        }
    }
    return Eliminar;
}

PosicionLista Lista_Buscar(TipoElemento X, TipoElemento Elementos[], int Inicio, int Final, int TDatoDeLaClave)
{
    PosicionLista Q;
    bool Encontre = false;
    PosicionLista Buscar = Nulo;

    // Controla que el Tipo de Dato de la Clave sea Homogeneo a la Lista
    if (X.TipoDatoClave(X.Clave) != TDatoDeLaClave)
    {
        return Buscar;
    }

    // Arranca por el Inicio y con Q recorre la lista
    Q = Inicio;
    while (Q != Nulo && Q <= Final && !Encontre)
    {
        if (Elementos[Q].Clave == X.Clave)
        {
            Encontre = true;
        }
        else
        {
            Q++;
        }
    }

    // Controla si lo encontro, si es asi retorno la posicion Q
    if (Encontre)
    {
        Buscar = Q;
    }

    return Buscar;
}

PosicionLista Lista_Siguiente(PosicionLista P, int Final)
{
    PosicionLista Siguiente = Nulo;
    if (ValidarPosicion(P) && P < Final)
    {
        Siguiente = P + 1;
    }
    return Siguiente;
}

PosicionLista Lista_Anterior(PosicionLista P, int Inicio)
{
    PosicionLista Anterior = Nulo;
    if (ValidarPosicion(P) && P > Inicio)
    {
        Anterior = P - 1;
    }
    return Anterior;
}

TipoElemento Lista_Recuperar(PosicionLista P, TipoElemento Elementos[], int ValidarPosicion)
{
    TipoElemento X;
    TipoElemento Recuperar = X.TipoElementoVacio;
    if (ValidarPosicion(P))
    {
        Recuperar = Elementos[P];
    }
    return Recuperar;
}

Resultado Lista_Actualizar(TipoElemento X, PosicionLista P, TipoElemento Elementos[], int TDatoDeLaClave, int ValidarPosicion)
{
    Resultado Actualizar = CError;

    // Controla que el Tipo de Dato de la Clave sea Homogeneo a la Lista
    if (X.TipoDatoClave(X.Clave) != TDatoDeLaClave)
    {
        Actualizar = ClaveIncompatible;
        return Actualizar;
    }

    // Ahora valida la posicion
    if (ValidarPosicion(P))
    {
        Elementos[P] = X;
        Actualizar = OK;
    }
    return Actualizar;
}

int Lista_ValidarPosicion(PosicionLista P, int EsVacia, int Inicio, int Final)
{
    int ValidarPosicion = 0;
    if (!EsVacia && P >= Inicio && P <= Final)
    {
        ValidarPosicion = 1;
    }
    return ValidarPosicion;
}

void Lista_Intercambio(PosicionLista P, PosicionLista Q, TipoElemento Elementos[])
{
    TipoElemento X1, X2;
    X1 = Elementos[P];
    X2 = Elementos[Q];
    Elementos[P] = X2;
    Elementos[Q] = X1;
}

void Lista_Sort(int Ascendente, PosicionLista Inicio, PosicionLista Nulo, TipoElemento Elementos[], PosicionLista (*Siguiente)(PosicionLista))
{
    PosicionLista P, Q;
    TipoElemento X1, X2;

    // Ordeno por clave por método de burbuja
    P = Inicio;
    while (P != Nulo)
    {
        Q = Inicio;
        while (Q != Nulo)
        {
            X1 = Elementos[Q];
            if (Siguiente(Q) != Nulo)
            {
                X2 = Elementos[Siguiente(Q)];
                // Si es Ascendente
                if (Ascendente)
                {
                    if (X1.Clave > X2.Clave)
                    {
                        Lista_Intercambio(Q, Siguiente(Q), Elementos);
                    }
                }
                // Si es Descendente
                else
                {
                    if (X1.Clave < X2.Clave)
                    {
                        Lista_Intercambio(Q, Siguiente(Q), Elementos);
                    }
                }
            }
            Q = Siguiente(Q);
        }
        P = Siguiente(P);
    }
}

char *Lista_RetornarClaves(PosicionLista Inicio, PosicionLista Nulo, TipoElemento Elementos[], PosicionLista (*Recuperar)(PosicionLista),
                           PosicionLista (*Siguiente)(PosicionLista), char *cCRLF)
{
    PosicionLista Q;
    TipoElemento X;
    char *S;
    char *SS = malloc(sizeof(char) * 1);
    *SS = '\0';
    Q = Inicio;
    while (Q != Nulo)
    {
        X = Recuperar(Q);
        S = ArmarString(X);                                               // Reemplazar con la función que arme el string a partir del TipoElemento X
        char *temp = malloc(sizeof(char) * (strlen(SS) + strlen(S) + 3)); // 3 para el '\r', '\n' y '\0'
        strcpy(temp, SS);
        strcat(temp, S);
        strcat(temp, cCRLF);
        free(SS);
        SS = temp;
        free(S);
        Q = Siguiente(Q);
    }
    return SS;
}

PosicionLista Lista_Comienzo(PosicionLista Inicio)
{
    return Inicio;
}

PosicionLista Lista_Fin(PosicionLista Final)
{
    return Final;
}

int Lista_CantidadElementos(int Q_Items)
{
    return Q_Items;
}

Resultado Lista_LlenarClavesRandom(int alSize, int RangoDesde, int RangoHasta, TipoElemento Elementos[], Resultado (*Crear)(TipoDatosClave, int),
                                   void (*Inicializar)(TipoElemento, TipoDatosClave), void (*Agregar)(TipoElemento),
                                   bool (*EsLLena)(), TipoDatosClave (*DatoDeLaClave)(), int (*Random)(),
                                   Resultado OK, Resultado CError)
{
    TipoElemento X;
    LlenarClavesRandom = CError;
    TDatoDeLaClave = Numero;
    // Siempre la Crea vacia como Numero
    if (Crear(TDatoDeLaClave, alSize) != OK)
    {
        LlenarClavesRandom = CError;
        return LlenarClavesRandom;
    }
    Inicializar(Numero, "");
    Randomize();
    while (!EsLLena())
    {
        X.Clave = RangoDesde + Random(RangoHasta);
        Agregar(X);
    }
    LlenarClavesRandom = OK;
    return LlenarClavesRandom;
}

TipoDatosClave Lista_DatoDeLaClave()
{
    return TDatoDeLaClave;
}

int Lista_SizeList(int Size)
{
    return Size;
}

int Lista_MaxSizeList()
{
    return MAX;
}