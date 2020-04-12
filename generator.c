#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Pet
{
    char name[32];
    char type[32];
    int age;
    char race[16];
    int height;
    float weight;
    char gender;
    long next;
};

int write(void *ap)
{
    struct Pet *data;
    data = ap;

    FILE *outfile;
    if ((outfile = fopen("datadogs.dat", "a+")) == NULL)
    {
        printf("Error opening file in write\n");
        return 1;
    }
    fwrite(data, sizeof(struct Pet), 1, outfile);
    fclose(outfile);
}

int read()
{
    FILE *infile;
    if ((infile = fopen("datadogs.dat", "rb")) == NULL)
    {
        printf("Error opening file in read\n");
        return 1;
    }

    rewind(infile);
    struct Pet pet;

    while (fread(&pet, sizeof(struct Pet), 1, infile))
    {
        printf("Nombre: %s", pet.name);
        printf("\nTipo: %s", pet.type);
        printf("\nEdad: %i", pet.age);
        printf("\nRaza: %s", pet.race);
        printf("\nAltura: %i", pet.height);
        printf("\nPeso: %0.2f", pet.weight);
        printf("\nSexo: %c", pet.gender);
        printf("\nNext: %li \n\n", pet.next);
    }
    fclose(infile);

    return 0;
}

int change(void *ap, long pos)
{
    struct Pet *data;
    data = ap;

    FILE *outfile;
    if ((outfile = fopen("datadogs.dat", "r+")) == NULL)
    {
        printf("Error opening file in change\n");
        return 1;
    }
    fseek(outfile, sizeof(struct Pet) * pos, SEEK_SET);
    fwrite(data, sizeof(struct Pet), 1, outfile);
    fclose(outfile);
    //printf("\n write: %li \n", pos);
    return 0;
}

int changenextNode(long value, long pos)
{
    struct Pet pet;

    FILE *infile;
    if ((infile = fopen("datadogs.dat", "r+")) == NULL)
    {
        printf("Error opening file in change next node\n");
        return 1;
    }
    fseek(infile, sizeof(struct Pet) * pos, SEEK_SET);
    fread(&pet, sizeof(struct Pet), 1, infile);
    pet.next = value;
    fclose(infile);
    change(&pet, pos);
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

    free(race);
    return (race);
}

long longpow(long x, int n)
{
    long i;
    long number = 1;

    for (int i = 0; i < n; i++)
    {
        number *= x;
    }
    
    return number;
}

//actualmente sin uso
int readpos(long pos)
{

    FILE *file;
    file = fopen("datadogs.dat", "r+");

    fseek(file, sizeof(struct Pet) * pos, SEEK_SET);
    struct Pet pet;
    fread(&pet, sizeof(struct Pet), 1, file);
    printf("\n/////// readpos ///////\n");
    printf("Nombre: %s", pet.name);
    printf("\nTipo: %s", pet.type);
    printf("\nEdad: %i", pet.age);
    printf("\nRaza: %s", pet.race);
    printf("\nAltura: %i", pet.height);
    printf("\nPeso: %0.2f", pet.weight);
    printf("\nSexo: %c", pet.gender);
    printf("\nNext: %li \n", pet.next);
    fclose(file);
    return 0;
}

long getnextNode(long pos)
{
    FILE *file;
    file = fopen("datadogs.dat", "r+");

    fseek(file, sizeof(struct Pet) * pos, SEEK_SET);
    struct Pet pet;

    fread(&pet, sizeof(struct Pet), 1, file);
    //printf("\nnext node: %li \n", pet.next);
    fclose(file);
    return pet.next;
}

//----funciones para la tabla HASH----

//calcula el resultado de la funcion hash y lo retorna
long hashfunction(char name[32])
{
    long result = 0;
    long i = 0;
    while (name[i] != '\0')
    {
        if ((long)name[i] != 10)
        {
            result = result + (((long)name[i])*longpow(167,i));
        }        
        i++;
    }
    result = result % 1801;
    //printf("\nhash result: %li \n", result);
    
    return result;
}

//devuelve el id almacenado en la posicion dada
long readhash(long pos)
{
    FILE *file;
    file = fopen("hash.bin", "r+");

    fseek(file, sizeof(long) * pos, SEEK_SET);
    long id;
    fread(&id, sizeof(long), 1, file);
    //printf("\n/////// id: ///////\n");
    //printf("pos: %li", pos);
    //printf("\nid: %li \n", id);
    fclose(file);
    return id;
}

//cambia el valor almacenado en una posicion dada
int writehash(int pos, long value)
{
    FILE *ftc;
    ftc = fopen("hash.bin", "r+");
    fseek(ftc, sizeof(long) * pos, SEEK_SET);
    fwrite(&value, sizeof(long), 1, ftc);
    fclose(ftc);
    //printf("\nwritehash de value: %li \n", value);
    return 0;
}

//------------------------------MAIN----------------------------------//
int main(int argc, char *argv[])
{
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    long line_count = 0;
    ssize_t line_size;
    long temp = -1;
    long current_node = -1;

    FILE *fp = fopen("nombresMascotas.txt", "r+");
    if (!fp)
    {
        fprintf(stderr, "Error opening file 'names.txt'");
        return EXIT_FAILURE;
    }
    line_size = getline(&line_buf, &line_buf_size, fp);

    //GENERADOR DE TABLA HASH EN HASH.BIN
    FILE *file;
    file = fopen("hash.bin", "w+");

    for (int i = 0; i < 1801; i++)
    {
        fwrite(&temp, sizeof(long), 1, file);
    }
    fclose(file);

    //TRUNCATE datadogs.dat
    file = fopen("datadogs.dat", "w+");
    fclose(file);
    struct Pet pet;

    //GENERADOR RANDOM DE MASCOTAS EN DATADOGS.DAT
    for (long i = 0; i < 10000000; i++)
    {
        line_count++;
        strcpy(pet.name, line_buf);
        
        //sprintf(pet.name, "ABCD"); //Dato quemado para pruebasssssssss
        line_size = getline(&line_buf, &line_buf_size, fp);
        if (line_count >= 1716)
        {
            rewind(fp);
            line_count = 0;
        }

        //EL NOMBRE SE LEE DEL TXT DE NOMBRES
        sprintf(pet.type, "Perro");

        pet.age = rand() % 14;
        pet.height = rand() % 110;
        pet.weight = (rand() % 101) + ((rand() % 100) / 100.0);

        strcpy(pet.race, setRace());

        switch (rand() % 2)
        {
        case 0:
            pet.gender = 'F';
            break;
        case 1:
            pet.gender = 'M';
            break;
        default:
            break;
        }
        printf("\n %li \n",i);
        printf("Nombre: %s", pet.name);
        //printf("\t %s", pet.type);
        //printf("\t%i años", pet.age);
        //printf("\n%s", pet.race);
        //printf("\t%i cm", pet.height);
        //printf("\t %0.2f kg", pet.weight);
        //printf("\nSexo: %c \n", pet.gender);

        //consulta con funcion hash en busca de estructuras con el mismo resultado
        temp = hashfunction(pet.name);
        current_node = readhash(temp);

        //si es -1 el valor hash no tiene estructura asignada
        if (current_node == -1)
        {
            //pet actual se convierte en head y tail de la lista
            pet.next = -1;

        }
        else
        {
            pet.next = current_node;
            //while (1 == 1)
            //{
            //    //temp toma el valor del next node que se tiene guardado
            //    temp = getnextNode(current_node);
            //    if (temp == -1)
            //    {
            //        pet.prev = current_node;
            //        pet.next = -1;
            //        changenextNode(i, current_node);
            //        break;
            //    }
            //    current_node = temp;
            //}
        }

        //se actualiza la hash table con pet como cabeza del nodo
        writehash(temp, i);
        
        //se escribe la estructura en el archivo .dat
        write(&pet);
    }
    fclose(fp);
    readpos(1716);

    return 0;
}
