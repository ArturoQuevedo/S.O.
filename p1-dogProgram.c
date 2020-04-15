#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#define HASH_SIZE 1000

struct dogType
{
    char name[32];
    char type[32];
    int age;
    char race[16];
    int height;
    float weight;
    char gender;
    int prev;
};

int numRegistros = 0;
int structSize = sizeof(struct dogType);

//Funcion hash tomada de:
//https://stackoverflow.com/questions/7666509/hash-function-for-string
int hashFunction(char *str)
{
    char new[32];
    snprintf(new, 32, "%s", str);
    //printf("\nnew: %s\n", new);

    int hash, i;
    int len = strlen(new);
    //printf("len: %i\n", len);

    //printf("\n original: %s", new);

    for (hash = i = 0; i < len; ++i)
    {
        if (new[i] >= 65 && str[i] <= 90)
        {
            hash += new[i] + 32;
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        else
        {
            hash += new[i];
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return (int)fabs(hash % HASH_SIZE);
}
//---------------------initHash---------------------
//1.36 min
int initHash(int *hashTable)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        hashTable[i] = -1;
    }

    FILE *outfile;
    outfile = fopen("datadogs.dat", "r+");
    if (!outfile)
    {
        fprintf(stderr, "Error opening file 'nombresMascotas.txt'");
        return EXIT_FAILURE;
    }

    struct dogType *pet;
    pet = malloc(structSize);

    int fun;

    while (fread(pet, structSize, 1, outfile))
    {

        fun = hashFunction(pet->name);
        pet->prev = hashTable[fun];
        //pet->prev =99;
        fseek(outfile, structSize * numRegistros, SEEK_SET);
        fwrite(pet, structSize, 1, outfile);
        hashTable[fun] = numRegistros;
        numRegistros++;
    }
    free(pet);
    fclose(outfile);
    return 0;
}

//---------------------searchById---------------------
int searchById()
{
    int registerToSearch;
    char openHistorial;
    char fileHistClin[64];

    printf("\nHay %i mascotas registradas", numRegistros);
    printf("\nRecuerde que el ID del primer perro es 0 y del último es %i", numRegistros - 1);
    printf("\nIngrese el número de registro de la pet que desea buscar\n");
    scanf("%i", &registerToSearch);

    if (registerToSearch < numRegistros && registerToSearch >= 0)
    {
        //Casi copypasteado tal cual de "readpos"
        FILE *file;
        file = fopen("datadogs.dat", "r+");
        if (!file)
        {
            return EXIT_FAILURE;
        }

        struct dogType *pet;
        pet = malloc(structSize);

        fseek(file, registerToSearch * structSize, SEEK_SET);
        fread(pet, structSize, 1, file);

        printf("\nSe encontró la pet:");
        printf("\nNombre: %s", pet->name);
        printf("Tipo: %s", pet->type);
        printf("\tEdad: %i", pet->age);
        printf("\nRaza: %s", pet->race);
        printf("\tAltura: %i", pet->height);
        printf("\nPeso: %0.2f", pet->weight);
        printf("\tSexo: %c", pet->gender);

        printf("\n¿Desea abrir hitoria clinica? ");

        while (true)
        {
            scanf("%c", &openHistorial);

            if (openHistorial != 'N' && openHistorial != 'S')
            {
                printf("Debe confirma con un 'S' o un 'N'\n");
            }

            else if (openHistorial == 'S')
            {
                char consoleInstruct[64];

                //Darle nombre al archivo de historia clinica: id+nombre.txt
                sprintf(fileHistClin, "%i", registerToSearch);
                strcat(fileHistClin, pet->name);

                //Por algún motivo non agrega el .txt
                //strcat(fileHistClin,".txt");

                strcat(consoleInstruct, "kate ");
                strcat(consoleInstruct, fileHistClin);

                system(consoleInstruct);
                break;
            }
            else if (openHistorial == 'N')
            {
                //Que vergas hago
                //printf("\nAh, bueno");
                break;
            }
            else
            {
                break;
            }
        }
        fclose(file);
        free(pet);
    }
    else
    {
        printf("El Numero de registro no es valido\n");
    }

    return 0;
}

//---------------------searchByName---------------------
int searchByName(int *hashTable)
{
    char nameToSearch[32];
    int hashValue;
    int position;
    int numCoincidencias = 1;
    int len;

    printf("\nIngrese el nombre que desea buscar\n");
    scanf("%s", nameToSearch);
    strcat(nameToSearch, "\n");

    FILE *file;
    file = fopen("datadogs.dat", "r");
    if (!file)
    {
        fprintf(stderr, "Error opening file 'datadogs.dat'");
        return EXIT_FAILURE;
    }

    struct dogType *pet;
    pet = malloc(structSize);

    //Los perros con el mismo nombre tienen el mismo valor hash
    hashValue = hashFunction(nameToSearch);
    position = hashTable[hashValue];
    if (position == -1)
    {
        printf("\nNo hay coincidencias con este nombre");
    }

    while (position != -1)
    {
        fseek(file, position * structSize, SEEK_SET);
        fread(pet, structSize, 1, file);

        //convertir mayúsculas a minísculas
        len = strlen(nameToSearch);
        if (len == strlen(pet->name))
        {
            for (int i = 0; i < len; i++)
            {
                nameToSearch[i] = tolower(nameToSearch[i]);
                pet->name[i] = tolower(pet->name[i]);
            }

            //El nombre de la pet que encontró coincide con el que busco?
            if (strcmp(pet->name, nameToSearch) == 0)
            {
                printf("Coincidencia #: %i", numCoincidencias);
                printf("\tPosición: %i", position);
                printf("\tNombre: %s", pet->name);
                //printf("Tipo: %s", pet->type);
                //printf("\tEdad: %i", pet->age);
                //printf("\nRaza: %s", pet->race);
                //printf("\tAltura: %i", pet->height);
                //printf("\nPeso: %0.2f", pet->weight);
                //printf("\tSexo: %c", pet->gender);
                numCoincidencias++;
            }
        }

        position = pet->prev;
    }
    free(pet);
    fclose(file);
    printf("\nTerminó la búsqueda");

    return 0;
}

//---------------------enterRegister---------------------
void enterRegister(int *hashTable)
{
    char nombre[32];
    char tipo[32];
    int edad;
    char raza[32];
    int estatura;
    double peso;
    char sexo;

    printf("Ingrese el nombre de su mascota:");
    scanf("%s", nombre);
    strcat(nombre, "\n");
    printf("Ingrese el tipo de mascota:");
    scanf("%s", tipo);
    printf("Ingrese la edad de su mascota:");

    while (true)
    {
        scanf("%d", &edad);
        if (edad < 0)
        {
            printf("Edad invalida.");
            printf("La edad debe ser mayor o igual que 0\n");
        }
        else
        {
            break;
        }
    }

    printf("Ingrese la raza de su pet:");
    scanf("%s", raza);
    printf("Ingrese la estatura de su pet:");

    while (true)
    {
        scanf("%d", &estatura);
        if (estatura < 0)
        {
            printf("Estatura invalida.");
            printf("La estatura debe ser positiva\n");
        }
        else
        {
            break;
        }
    }

    printf("Ingrese el peso de su pet:");

    while (true)
    {
        scanf("%lf", &peso);
        if (peso < 0)
        {
            printf("Peso invalido. ");
            printf("El peso debe ser positivo\n");
        }
        else
        {
            break;
        }
    }

    printf("Ingrese el sexo de su pet:");

    while (true)
    {
        scanf(" %c", &sexo);
        if (sexo == 'M' || sexo == 'H')
        {
            break;
        }
        else
        {
            printf("Sexo invalido. ");
            printf("El sexo de debe ser M o H\n");
        }
    }

    struct dogType *pet;
    pet = malloc(structSize);

    strcpy(pet->name, nombre);
    strcpy(pet->type, tipo);
    pet->age = edad;
    strcpy(pet->race, raza);
    pet->height = estatura;
    pet->weight = peso;
    pet->gender = sexo;

    //Modificar tabla hash y prev
    int hashvalue = hashFunction(nombre);
    pet->prev = hashTable[hashvalue];
    hashTable[hashvalue] = numRegistros;
    //Sobreescribir
    FILE *file;
    file = fopen("datadogs.dat", "r+");

    fseek(file, numRegistros * structSize, SEEK_SET);
    fwrite(pet, structSize, 1, file);
    numRegistros++;

    free(pet);
    fclose(file);
}

//---------------------deleteFromFile---------------------
int deleteFromFile(int *hashTable)
{
    FILE *file;
    int currentNode, hashValue, originalprev,position;

    printf("\nHay %i mascotas registradas", numRegistros);
    printf("\nRecuerde que el ID del primer perro es 0 y del último es %i", numRegistros - 1);
    printf("\nIngrese el número de registro de la mascota que desea eliminar\n");
    scanf("%i", &position);

    if(position>=numRegistros||position<0)
    {
        printf("valor de id invalido");
        return 1;
    }

    file = fopen("datadogs.dat", "r+");

    if (!file)
    {
        fprintf(stderr, "Error opening file 'datadogs.dat'");
        return EXIT_FAILURE;
    }

    struct dogType *pet;
    pet = malloc(structSize);

    fseek(file, position * structSize, SEEK_SET);
    fread(pet, structSize, 1, file);

    //valor del nodo anterior almacenado en el nodo que se quiere eliminar
    originalprev = pet->prev;

    hashValue = hashFunction(pet->name);
    currentNode = hashTable[hashValue];

    //eliminar referencias al nodo en cuestion
    if(currentNode == position)
    {
        hashTable[hashValue] = originalprev;
    }
    else
    {
        while(1==1)
        {
            fseek(file, currentNode * structSize, SEEK_SET);
            fread(pet, structSize, 1, file);
            if(pet->prev==position)
            {
                pet->prev = originalprev;
                fseek(file, currentNode * structSize, SEEK_SET);
                fwrite(pet, structSize, 1, file);
                break;
            }

            currentNode = pet->prev;
        }
    }

    //tras haber eliminado las referencias se traslada ahora el úlitmo nodo a la posición dada
    if(position == numRegistros-1)
    {
        numRegistros--;
        free(pet);
        fclose(file);
        return 0;
    }
    else
    {
    fseek(file,(numRegistros-1) * structSize, SEEK_SET);
    fread(pet, structSize, 1, file);

    hashValue = hashFunction(pet->name);
    hashTable[hashValue] = position;

    fseek(file, position * structSize, SEEK_SET);
    fwrite(pet, structSize, 1, file);

    numRegistros--;
    free(pet);
    fclose(file);
    return 0;
    }
}

//---------------------readAllDogs---------------------
int readAllDogs() //NO usar con 10M perros
{
    FILE *outfile;
    outfile = fopen("datadogs.dat", "rb");
    if (!outfile)
    {
        fprintf(stderr, "Error opening file 'datadogs.dat'");
        return EXIT_FAILURE;
    }

    struct dogType *pet;
    pet = malloc(structSize);

    while (fread(pet, structSize, 1, outfile))
    {
        printf("\nNombre: %s", pet->name);
        printf("\tTipo: %s", pet->type);
        printf("\nEdad: %i", pet->age);
        printf("\tRaza: %s", pet->race);
        printf("\nAltura: %i", pet->height);
        printf("\tPeso: %0.2f", pet->weight);
        printf("\nSexo: %c", pet->gender);
        printf("\nprev: %i \n", pet->prev);
    }
    free(pet);
    fclose(outfile);
    return 0;
}

//---------------------readSomeDogs---------------------
int readSomeDogs() //Lee uno de cada 2M perros
{
    int i = 0;

    FILE *outfile;
    outfile = fopen("datadogs.dat", "rb");
    if (!outfile)
    {
        fprintf(stderr, "Error opening file 'datadogs.dat'");
        return EXIT_FAILURE;
    }

    struct dogType *pet;
    pet = malloc(structSize);

    while (fread(pet, structSize, 1, outfile))
    {
        if (i % 2000000 == 0)
        {
            printf("\n %i", i);
            printf("\nNombre: %s", pet->name);
            printf("\nTipo: %s", pet->type);
            printf("\tEdad: %i", pet->age);
            printf("\nRaza: %s", pet->race);
            printf("\nAltura: %i", pet->height);
            printf("\tPeso: %0.2f", pet->weight);
            printf("\nSexo: %c", pet->gender);
            printf("\nprev: %i \n", pet->prev);
        }
        i++;
    }
    free(pet);
    fclose(outfile);
    return 0;
}

//--------------------- MAIN ---------------------
int main(int argc, char *argv[])
{

    int hashTable[HASH_SIZE];
    initHash(hashTable);

    int menu;
    bool flag = true;
    char esto_es_un_char[1];

    while (flag)
    {

        printf("\nMenuº:\n1. Ingresar registro");
        printf("\n2. Ver registro");
        printf("\n3. Borrar registro");
        printf("\n4. Buscar registro \n5. Salir \n");
        scanf("%i", &menu);

        switch (menu)
        {
        case 1:
            enterRegister(hashTable);
            printf("\nPresione cualquier tecla y oprima enter para continuar \n");
            scanf("%s", esto_es_un_char);
            break;
        case 2:
            searchById();
            printf("\nPresione cualquier tecla y oprima enter para continuar \n");
            scanf("%s", esto_es_un_char);
            break;
        case 3:
            deleteFromFile(hashTable);
            printf("\nPresione cualquier tecla y oprima enter para continuar \n");
            scanf("%s", esto_es_un_char);
            break;
        case 4:
            searchByName(hashTable);
            printf("\nPresione cualquier tecla y oprima enter para continuar \n");
            scanf("%s", esto_es_un_char);
            break;
        case 5:
            flag = false;
            break;
        default:
            break;
        }
    }

    return 0;
}
