#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cTab '\t'    // Tabulador
#define cCR '\r'     // Retorno de carro
#define cCRLF "\r\n" // Retorno de Carro + Fin de Linea
#define cLF '\n'     // Fin de Linea solamente

typedef enum
{
    OK,
    CError,
    LLena,
    Vacia,
    PosicionInvalida,
    Otro,
    ClaveIncompatible,
    ClaveDuplicada
} Resultado;

typedef enum
{
    Numero,
    Cadena,
    Fecha,
    Otros,
    Desconocido
} TipoDatosClave;

typedef enum
{
    Modulo,
    Plegamiento,
    MitadDelCuadrado
} TipoFuncionesHash;

typedef struct
{
    void *Clave;  // Cualquier valor soportado por el TipoDatosClave
    void *Valor1; // Cualquier valor soportado por un void pointer
    void *Valor2; // Puntero Generico a Cualquier cosa (dato primitivo, otra estructura, un objeto, etc.)
} TipoElemento;

// Comportamiento basico del TipoElemento
char *ArmarString(TipoElemento *te);
char *ArmarStringConSeparador(TipoElemento *te, char *separador);
TipoDatosClave TipoDatoClave(void *avClave);
TipoElemento *TipoElementoVacio();
bool EsTEVacio(TipoElemento *te);
void Inicializar(TipoElemento *te, TipoDatosClave aTDC, void *aValor1Inicial);

// Implementacion de las operaciones del TipoElemento

// Arma un String de la clave. Convierte el void pointer a un string
char *ArmarStringConSeparador(TipoElemento *te, char *separador)
{
    char *SV = (char *)malloc(sizeof(char) * 256);
    if (SV != NULL)
    {
        strcpy(SV, (char *)(te->Clave)); // Se convierte a string el campo void pointer sin importar lo que tenga
        strcat(SV, separador);           // Agrega el separador especificado como separador
        strcat(SV, (char *)te->Valor1);  // Convierte en string el Valor 1
    }
    return SV;
}

// Arma un String de la clave con un separador especificado. Convierte el void pointer a un string
char *ArmarStringConSeparador(TipoElemento *te, char *separador)
{
    char *SV = (char *)malloc(sizeof(char) * 256);
    if (SV != NULL)
    {
        strcpy(SV, (char *)(te->Clave)); // Se convierte a string el campo void pointer sin importar lo que tenga
        strcat(SV, separador);           // Agrega el separador especificado como separador
        strcat(SV, (char *)te->Valor1);  // Convierte en string el Valor 1
    }
    return SV;
}

// Función que evalúa el valor de la clave y retorna el Tipo de Datos del Variant
TipoDatosClave TipoDatoClave(void *avClave)
{
    int iTipo = *((int *)avClave);
    TipoDatosClave tipoDatoClave;

    switch (iTipo)
    {
    case 0:
        tipoDatoClave = Otros;
        break;
    case 1:
        tipoDatoClave = Otros;
        break;
    case 2:
        tipoDatoClave = Otros;
        break;
    case 3:
        tipoDatoClave = Otros;
        break;
    case 4:
        tipoDatoClave = Numero;
        break;
    case 5:
        tipoDatoClave = Numero;
        break;
    case 6:
        tipoDatoClave = Numero;
        break;
    case 7:
        tipoDatoClave = Numero;
        break;
    case 8:
        tipoDatoClave = Numero;
        break;
    case 9:
        tipoDatoClave = Fecha;
        break;
    case 10:
        tipoDatoClave = Otros;
        break;
    case 11:
        tipoDatoClave = Otros;
        break;
    case 12:
        tipoDatoClave = Otros;
        break;
    case 13:
        tipoDatoClave = Otros;
        break;
    case 14:
        tipoDatoClave = Otros;
        break;
    case 15:
        tipoDatoClave = Otros;
        break;
    case 16:
        tipoDatoClave = Otros;
        break;
    case 17:
        tipoDatoClave = Otros;
        break;
    case 18:
        tipoDatoClave = Otros;
        break;
    case 19:
        tipoDatoClave = Otros;
        break;
    case 20:
        tipoDatoClave = Numero;
        break;
    case 21:
        tipoDatoClave = Numero;
        break;
    case 22:
        tipoDatoClave = Numero;
        break;
    case 23:
        tipoDatoClave = Numero;
        break;
    case 24:
        tipoDatoClave = Numero;
        break;
    case 25:
        tipoDatoClave = Cadena;
        break;
    case 27:
        tipoDatoClave = Cadena;
        break;
    case 28:
        tipoDatoClave = Otros;
        break;
    case 29:
        tipoDatoClave = Cadena;
        break;
    default:
        tipoDatoClave = Otros;
        break;
    }

    return tipoDatoClave;
}

// Procedimiento que asigna vacío a la clave y valor1, NULL al puntero genérico
void TipoElementoVacio(TipoElemento *x)
{
    memset(x->Clave, 0, sizeof((x->Clave)));   // Llena con '\0' el bloque de memoria apuntado por Clave
    memset(x->Valor1, 0, sizeof((x->Valor1))); // Llena con '\0' el bloque de memoria apuntado por Valor1
    x->Valor2 = NULL;
}

// Función que retorna verdadero si el TE está vacío
bool EsTEVacio(TipoElemento *te)
{
    if (te->Clave == NULL && strcmp((char *)te->Valor1, "") == 0 && te->Valor2 == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Procedimiento para inicializar el TE según el Tipo de Dato Clave
// Solo para números, strings y fechas
void Inicializar(TipoElemento *te, int aTDC, void *aValor1Inicial)
{
    switch (aTDC)
    {
    case 1: // Número
        te->Clave = 0;
        break;
    case 2: // Cadena (string)
        te->Clave = '\0';
        break;
    case 3: // Fecha (asumiendo que Date es una función previamente definida)
        // te->Clave = Date();
        break;
    default: // Otros casos
    {
        int num = -1;
        te->Clave = &num;
    } // Valor por defecto para otros tipos de datos de clave
    }
    strcpy((char *)te->Valor1, (char *)aValor1Inicial); // Se copia el valor1 inicial en el arreglo de caracteres
    te->Valor2 = NULL;                                  // Se asigna NULL al puntero valor2
}