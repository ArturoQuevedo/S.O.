#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <ncurses.h>
#include <curses.h>
#include <termios.h>
#include <unistd.h>
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
        //fprintf(stderr, "Error opening file 'nombresMascotas.txt'");
        //return EXIT_FAILURE;
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

    printw("\nHay %i mascotas registradas", numRegistros);
    printw("\nRecuerde que el ID del primer perro es 0 y del último es %i", numRegistros - 1);
    printw("\nIngrese el número de registro de la pet que desea buscar\n");
    scanw("%i", &registerToSearch);

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

        printw("\nSe encontró la pet:");
        printw("\nNombre: %s", pet->name);
        printw("Tipo: %s", pet->type);
        printw("\tEdad: %i", pet->age);
        printw("\nRaza: %s", pet->race);
        printw("\tAltura: %i", pet->height);
        printw("\nPeso: %0.2f", pet->weight);
        printw("\tSexo: %c", pet->gender);

        printw("\n¿Desea abrir hitoria clinica? [S/N]");

        while (true)
        {
            scanw("%c", &openHistorial);

            if (openHistorial != 'N' && openHistorial != 'S')
            {
                printw("Debe confirma con un 'S' o un 'N'\n");
            }

            else if (openHistorial == 'S')
            {
                char consoleInstruct[64];

                //Darle nombre al archivo de historia clinica: id+nombre.txt
                sprintf(fileHistClin, "%i", registerToSearch);
                strcat(fileHistClin, pet->name);

                //Por algún motivo non agrega el .txt
                //strcat(fileHistClin,".txt");

                consoleInstruct[0] = 'k';
                consoleInstruct[1] = 'a';
                consoleInstruct[2] = 't';
                consoleInstruct[3] = 'e';
                consoleInstruct[4] = ' ';
                for (int i = 0; i < strlen(fileHistClin); i++)
                {
                    consoleInstruct[5+i]=fileHistClin[i];
                }
                printw("\n instruct: %s \n",consoleInstruct);                

                system(consoleInstruct);
                break;
            }
            else if (openHistorial == 'N')
            {
                //Que vergas hago
                //printw("\nAh, bueno");
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
        printw("El Numero de registro no es valido\n");
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

    printw("\nIngrese el nombre que desea buscar\n");
    scanw("%s", nameToSearch);
    strcat(nameToSearch, "\n");

    FILE *file;
    file = fopen("datadogs.dat", "r");
    if (!file)
    {
        printw("Error opening file 'datadogs.dat'");
        return EXIT_FAILURE;
    }

    struct dogType *pet;
    pet = malloc(structSize);

    //Los perros con el mismo nombre tienen el mismo valor hash
    hashValue = hashFunction(nameToSearch);
    position = hashTable[hashValue];
    if (position == -1)
    {
        printw("\nNo hay coincidencias con este nombre");
    }

    clear();

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
                printw("Coincidencia #: %i", numCoincidencias);
                printw("\tPosición: %i", position);
                printw("\tNombre: %s", pet->name);
                //printf("Tipo: %s", pet->type);
                //printf("\tEdad: %i", pet->age);
                //printf("\nRaza: %s", pet->race);
                //printf("\tAltura: %i", pet->height);
                //printf("\nPeso: %0.2f", pet->weight);
                //printf("\tSexo: %c", pet->gender);
                numCoincidencias++;
                refresh();
                if(numCoincidencias % 37 == 0){
                    getch();
                    clear();
                }
            }
        }

        position = pet->prev;
    }
    getch();
    clear();
    free(pet);
    fclose(file);
    printw("\nTerminó la búsqueda");

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

    printw("Ingrese el nombre de su mascota:");
    scanw("%s", nombre);
    strcat(nombre, "\n");
    printw("Ingrese el tipo de mascota:");
    scanw("%s", tipo);
    printw("Ingrese la edad de su mascota:");

    while (true)
    {
        scanw("%d", &edad);
        if (edad < 0)
        {
            printw("Edad invalida.");
            printw("La edad debe ser mayor o igual que 0\n");
        }
        else
        {
            break;
        }
    }

    printw("Ingrese la raza de su pet:");
    scanw("%s", raza);
    printw("Ingrese la estatura de su pet:");

    while (true)
    {
        scanw("%d", &estatura);
        if (estatura < 0)
        {
            printw("Estatura invalida.");
            printw("La estatura debe ser positiva\n");
        }
        else
        {
            break;
        }
    }

    printw("Ingrese el peso de su pet:");

    while (true)
    {
        scanw("%lf", &peso);
        if (peso < 0)
        {
            printw("Peso invalido. ");
            printw("El peso debe ser positivo\n");
        }
        else
        {
            break;
        }
    }

    printw("Ingrese el sexo de su mascota:");

    while (true)
    {
        scanw(" %c", &sexo);
        if (sexo == 'M' || sexo == 'H')
        {
            break;
        }
        else
        {
            printw("Sexo invalido. ");
            printw("El sexo de debe ser M o H\n");
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
    numRegistros++;
    //Sobreescribir
    FILE *file;
    file = fopen("datadogs.dat", "a+");

    fwrite(pet, structSize, 1, file);

    free(pet);
    fclose(file);
}

//---------------------deleteFromFile---------------------
int deleteFromFile(int *hashTable)
{
    FILE *file;
    int currentNode, hashValue, originalprev,position;

    printw("\nHay %i mascotas registradas", numRegistros);
    printw("\nRecuerde que el ID del primer perro es 0 y del último es %i", numRegistros - 1);
    printw("\nIngrese el número de registro de la mascota que desea eliminar\n");
    scanw("%i", &position);

    if(position>=numRegistros||position<0)
    {
        printw("valor de id invalido");
        return 1;
    }

    file = fopen("datadogs.dat", "r+");

    if (!file)
    {
        printw("Error opening file 'datadogs.dat'");
        return EXIT_FAILURE;
    }

    struct dogType *pet;
    pet = malloc(structSize);

    fseek(file, position * structSize, SEEK_SET);
    fread(pet, structSize, 1, file);

    printw("Se ha borrado el perro de ID %i, %s", position, pet->name);
    
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

//---------------------readSomeDogs---------------------
int readSomeDogs() //Lee uno de cada 2M perros
{
    int i = 0;

    FILE *outfile;
    outfile = fopen("datadogs.dat", "rb");
    if (!outfile)
    {
        printw("Error opening file 'datadogs.dat'");
        return EXIT_FAILURE;
    }

    struct dogType *pet;
    pet = malloc(structSize);

    while (fread(pet, structSize, 1, outfile))
    {
        if (i % 2000000 == 0)
        {
            printw("\n %i", i);
            printw("\nNombre: %s", pet->name);
            printw("\nTipo: %s", pet->type);
            printw("\tEdad: %i", pet->age);
            printw("\nRaza: %s", pet->race);
            printw("\nAltura: %i", pet->height);
            printw("\tPeso: %0.2f", pet->weight);
            printw("\nSexo: %c", pet->gender);
            printw("\nprev: %i \n", pet->prev);
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

    initscr();

    while (flag)
    {
        clear();
        refresh();

        printw("\nMenuº:\n1. Ingresar registro");
        printw("\n2. Ver registro");
        printw("\n3. Borrar registro");
        printw("\n4. Buscar registro \n5. Salir \n");

        scanw("%i", &menu);

        switch (menu)
        {
        case 1:
            enterRegister(hashTable);
            printw("\nPresione cualquier tecla para continuar\n");
            getch();
            break;
        case 2:
            searchById();
            printw("\nPresione cualquier tecla para continuar\n");
            getch();
            break;
        case 3:
            deleteFromFile(hashTable);
            printw("\nPresione cualquier tecla para continuar\n");
            getch();
            break;
        case 4:
            searchByName(hashTable);
            printw("\nPresione cualquier tecla para continuar\n");
            getch();
            break;
        case 5:
            flag = false;
            break;
        default:
            break;
        }
    }

    endwin();
    return 0;
}
