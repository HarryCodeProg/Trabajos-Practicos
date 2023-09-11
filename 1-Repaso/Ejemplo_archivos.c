#include <string.h>
#include <stdio.h>

struct Empleado
{
    char nombre[20];
    int edad;
    float sueldo;
};

// retornar una cadena
const char *myName()
{
    return "Prueba de Retorno de String en C";
}

// retornar un array de string
const char **myNames()
{
    char **names = NULL;
    names = (char **)malloc(3 * sizeof(char *));
    names[1] = (char *)malloc(10);
    names[1] = "NOMBRE 1";
    names[2] = (char *)malloc(20);
    names[2] = "SEGUNDO NOMBRE";
    names[3] = (char *)malloc(10);
    names[3] = "APELLIDO";

    return names;
}

// Funcion Principal
int main()
{
    // llamar a la funcion que retorna un string
    const char *name = myName();
    printf("%s \n", name);

    // Llamar a la funcion que retorna un array de string
    const char **names = myNames();
    printf("%s \n", names[1]);
    printf("%s \n", names[2]);
    printf("%s \n", names[3]);

    // Manejo de Archivos
    FILE *femp;
    const char *rta;

    struct Empleado *emp;
    emp = malloc(sizeof(struct Empleado));

    strcpy(emp->nombre, "juan perez");
    emp->edad = 100;
    emp->sueldo = 10000.25;

    femp = fopen("empleados.bin", "wb");

    if (femp == NULL)
    {
        printf("Error al abrir el archivo \n");
        return -1;
    };

    fwrite(emp, sizeof(struct Empleado), 1, femp);
    fwrite(emp, sizeof(struct Empleado), 1, femp);
    fwrite(emp, sizeof(struct Empleado), 1, femp);

    fclose(femp);

    printf("---------------------------------------------------------------- \n");
    printf("Se ha generado el archivo Binario \n");
    printf("---------------------------------------------------------------- \n");

    lectura();

    printf("---------------------------------------------------------------- \n");

    pos();

    printf("---------------------------------------------------------------- \n");

    split();

    printf("---------------------------------------------------------------- \n");

    return 0;
}

// lee el archivo binario
int lectura()
{
    FILE *femp;

    struct Empleado *emp;
    emp = malloc(sizeof(struct Empleado));

    femp = fopen("empleados.bin", "rb");

    if (femp == NULL)
    {
        printf("Error al abrir el archivo \n");
        return -1;
    };

    fread(emp, sizeof(struct Empleado), 1, femp);
    while (!feof(femp))
    {
        printf("Se ha leido el archivo Binario \n");
        printf("Nombre: %s %d %f \n", emp->nombre, emp->edad, emp->sueldo);
        fread(emp, sizeof(struct Empleado), 1, femp);
    }

    fclose(femp);

    printf("Se ha leido el archivo Binario \n");
    printf("Nombre: %s %d %f \n", emp->nombre, emp->edad, emp->sueldo);

    return 1;
}

int pos()
{
    char url[] = "table=peliculas/&name=lo_que_sea.pdf";
    char *nombre_fichero;
    char *pos_igual;

    printf("Tomando de un string la ultima parte \n");
    printf("String usado <%s> \n", url);

    pos_igual = strrchr(url, '=');
    if (pos_igual == 0)
    {
        printf("La URL no tiene el formato esperado\n");
    }
    else
    {
        nombre_fichero = strdup(pos_igual + 1);
        printf("Nombre del fichero: %s\n", nombre_fichero);
    }
    return 1;
}

// Ejemplo de como realizar un split o parsing
int split()
{
    char cadena[] = "Hola,mundo,soy,una,cadena,separa,por,comas";
    char delimitador[] = ",";

    printf("Cadena a Separar: <%s> \n", cadena);

    char *token = strtok(cadena, delimitador);
    if (token != NULL)
    {
        while (token != NULL)
        {
            // S�lo en la primera pasamos la cadena; en las siguientes pasamos NULL
            printf("Token: %s\n", token);
            token = strtok(NULL, delimitador);
        }
    }
}
