#include <stdlib.h>
#include <stdio.h>

struct Pet
{
    char name[32];
    char type[32];
    int age;
    char race[16];
    int height;
    float weight;
    char gender;
    long prev;
    long next;
};

int write(void *ap)
{
    struct Pet *data;
    data = ap;

    FILE *outfile;
    if ((outfile = fopen("datadogs.dat", "wb")) == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    fwrite(data, sizeof(struct Pet), 1, outfile);
    fclose(outfile);
}

int read(){
    FILE* infile;
    if ((infile = fopen("datadogs.dat", "rb")) == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    struct Pet pet;

    while(fread(&pet, sizeof(struct Pet), 1, infile)){
        printf("Nombre: %s",pet.name);	
	    printf("\nTipo: %s",pet.type);
	    printf("\nEdad: %i",pet.age);	
	    printf("\nRaza: %s",pet.race);
	    printf("\nAltura: %i",pet.height);	
	    printf("\nPeso: %0.2f",pet.weight);
	    printf("\nSexo: %c",pet.gender);
	    printf("\nNext: %li",pet.prev);
	    printf("\nPrev: %li \n",pet.next);
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
        printf("Error opening file\n");
        return 1;
    }
    fseek(outfile, sizeof(struct Pet) * pos, SEEK_SET);
    fwrite(data, sizeof(struct Pet), 1, outfile);
    fclose(outfile);
    printf("\n write: %li \n", pos);
    return 0;
}

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
    printf("\nNext: %li", pet.prev);
    printf("\nPrev: %li \n", pet.next);
    fclose(file);
    return 0;
}

int hashfunction(char name[32])
{
    int result = 0;
    int i = 0;
    while (name[i] != '\0')
    {
        result = result + (int)name[i];
        i++;
    }
    result = result % 1000;
    printf("\nhash result: %i \n", result);
    return result;
}

long readhash(int pos)
{
    FILE *file;
    file = fopen("hash.bin", "r+");

    fseek(file, sizeof(int) * pos, SEEK_SET);
    long id;
    fread(&id, sizeof(long), 1, file);
    printf("\n/////// id: ///////\n");
    printf("pos: %i", pos);
    printf("\nid: %li \n", id);
    fclose(file);
    return id;
}

//AQUI AGREGUÉ CODIGO
//FUNCION BIEN MAMALONA ahhahahahahahahahahahahahahhaahhahahahaha
char *setRace()
{
    char *race;
    race = malloc(sizeof(char) * 16);
    switch (rand() % 16)
    {
    case 0:
        strcpy(race, "Schanauzer");
        return (race);
        break;
    case 1:
        strcpy(race, "Doberman");
        return (race);
        break;
    case 2:
        strcpy(race, "Chihuahua");
        return (race);
        break;
    case 3:
        strcpy(race, "Bulldog");
        return (race);
        break;
    case 4:
        strcpy(race, "Poodle");
        return (race);
        break;
    case 5:
        strcpy(race, "Beagle");
        return (race);
        break;
    case 6:
        strcpy(race, "Pug");
        return (race);
        break;
    case 7:
        strcpy(race, "Husky");
        return (race);
        break;
    case 8:
        strcpy(race, "Rottweiler");
        return (race);
        break;
    case 9:
        strcpy(race, "Corgi");
        return (race);
        break;
    case 10:
        strcpy(race, "ShihTzu");
        return (race);
        break;
    case 11:
        strcpy(race, "BorderCollie");
        return (race);
        break;
    case 12:
        strcpy(race, "GranDanes");
        return (race);
        break;
    case 13:
        strcpy(race, "PastorAleman");
        return (race);
        break;
    case 14:
        strcpy(race, "ChowChow");
        return (race);
        break;
    case 15:
        strcpy(race, "Dalmata");
        return (race);
        break;

    default:
        break;
    }
}

//-----------MAIN---------------//
int main(int argc, char *argv[])
{
    //Aquí se añade código
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    FILE *fp = fopen("nombresMascotas.txt", "r");
    if (!fp)
    {
        fprintf(stderr, "Error opening file 'names.txt'");
        return EXIT_FAILURE;
    }
    line_size = getline(&line_buf, &line_buf_size, fp);
    //Aquí termina el codigo añadido

    //GENERADOR DE TABLA HASH EN HASH.BIN
    FILE *file;
    file = fopen("hash.bin", "w+");
    long temp = -1;
    long current_node;

    for (int i = 0; i < 1000; i++)
    {
        fwrite(&temp, sizeof(long), 1, file);
    }
    fclose(file);

    //GENERADOR RANDOM DE MASCOTAS EN DATADOGS.DAT
    for (int i = 0; i < 10; i++)
    {

        struct Pet pet;

        line_count++;
	//asdfghjhgfdsasdfghjhgfdsasdfghgfdsdfghgfSDFSDFFDSF
	    
	//LA LINEA DE ABAJO LA CAMBIE PARA QUE NO MANDARA ADVERTENCIAS
        strcpy(pet.name, line_buf);
        line_size = getline(&line_buf, &line_buf_size, fp);
        if (line_count >= 1716)
        {
            rewind(fp);
            line_count = 0;
        }

        //EL NOMBRE SE LEE DEL TXT DE NOMBRES
        sprintf(pet.name, "ABC");

        sprintf(pet.type, "Perro");
        pet.age = rand() % 14;
        pet.height = rand() % 110;
        pet.weight = (rand() % 101) + ((rand() % 100) / 100.0);
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$4
	//LA LINEA DE ABAJO LA CAMBIE PARA QUE NO MANDARA ADVERTENCIAS
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

        printf("Nombre: %s", pet.name);
        printf("\t %s", pet.type);
        printf("\t%i años", pet.age);
        printf("\n%s", pet.race);
        printf("\t%i cm", pet.height);
        printf("\t %0.2f kg", pet.weight);
        printf("\nSexo: %c \n", pet.gender);

        //consulta con funcion hash en busca de estructuras con el mismo resultado
        temp = hashfunction(pet.name);
        current_node = readhash(temp);
        
        //si es -1 el valor hash no tiene estructura asignada
        if (current_node==-1)
        {
            //pet actual se convierte en head y tail de la lista
            pet.next = 0;
            pet.prev = 0;

            //se actualiza la hash table con pet como cabeza del nodo
            file = fopen("hash.bin", "w+");
            fseek(file, sizeof(long) * temp, SEEK_SET);
            fwrite(&i, sizeof(long), 1, file);
            fclose(file);
        }
        else
        {
            //something
        }

        write(&pet);
    }
    read();
    return 0;
}
