#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<time.h>

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
int structSize = sizeof(struct dogType);

int readSomeDogs() //Lee uno de cada 1M perros
{
    int i = 0;

    FILE *outfile;
    outfile = fopen("datadogs.dat", "rb");
    if (!outfile)
    {
        fprintf(stderr, "Error opening file 'nombresMascotas.txt'");
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
            printf("\nPrev: %i \n", pet->prev);            

            
        }
        i++;
    }
    free(pet);
    fclose(outfile);
    return 0;

}

char *setRace()
{
    char *race;
    race = malloc(sizeof(char) * 16);
    switch (rand() % 16)
    {
    case 0:
        strcpy(race, "Schanauzer");
        break;
    case 1:
        strcpy(race, "Doberman");
        break;
    case 2:
        strcpy(race, "Chihuahua");
        break;
    case 3:
        strcpy(race, "Bulldog");
        break;
    case 4:
        strcpy(race, "Poodle");
        break;
    case 5:
        strcpy(race, "Beagle");
        break;
    case 6:
        strcpy(race, "Pug");
        break;
    case 7:
        strcpy(race, "Husky");
        break;
    case 8:
        strcpy(race, "Rottweiler");
        break;
    case 9:
        strcpy(race, "Corgi");
        break;
    case 10:
        strcpy(race, "ShihTzu");
        break;
    case 11:
        strcpy(race, "BorderCollie");
        break;
    case 12:
        strcpy(race, "GranDanes");
        break;
    case 13:
        strcpy(race, "PastorAleman");
        break;
    case 14:
        strcpy(race, "ChowChow");
        break;
    case 15:
        strcpy(race, "Dalmata");
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{

    //Para los numeros aleatorios
    time_t t;
    srand((unsigned)time(&t));

    //Variables para leer los nombres
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;

    FILE *namesfile = fopen("nombresMascotas.txt", "r+");
    if (!namesfile)
    {
        fprintf(stderr, "Error opening file 'nombresMascotas.txt'");
        return EXIT_FAILURE;
    }
    line_size = getline(&line_buf, &line_buf_size, namesfile);

    //Crear datadogs
    FILE *dogsfile = fopen("datadogs.dat", "w+");
    if (!dogsfile)
    {
        fprintf(stderr, "Error opening file 'datadogs.dat'");
        return EXIT_FAILURE;
    }

    struct dogType *pet;
    pet = malloc(structSize);

    //GENERADOR RANDOM DE MASCOTAS EN DATADOGS.DAT
    for (int i = 0; i < 8; i++)
    {
        line_count++;

        strcpy(pet->name, line_buf);
        //AGREGAR UN TOLOWER CASE!!!!

        if(i>=3 && i<6){
            strcpy(pet->name, "Abanero\n");
        }
        if(i==7){
            strcpy(pet->name, "Aarón\n");
        }
        line_size = getline(&line_buf, &line_buf_size, namesfile);

        //Si se acaban los nombres, vuelva a leer nombresMascotas.txt
        if (line_count >= 1716)
        {
            rewind(namesfile);
            line_count = 0;
        }

        sprintf(pet->type, "Perro");
        pet->age = rand() % 14;
        pet->height = (rand() % 110) + 1;
        pet->weight = ((rand() % 100) + 1) + ((rand() % 100) / 100.0);
        strcpy(pet->race, setRace());

        switch (rand() % 2)
        {
        case 0:
            pet->gender = 'H';
            break;
        case 1:
            pet->gender = 'M';
            break;
        default:
            break;
        }
        pet->prev=-1;

        fwrite(pet, structSize, 1, dogsfile);
    }
    free(pet);
    fclose(namesfile);
    fclose(dogsfile);

    //readSomeDogs();



    return 0;
}
