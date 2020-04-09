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
};

int write(void* ap){
    struct Pet* data;
    data=ap;

    FILE* outfile;
    if ( (outfile = fopen("data.bin", "wb")) == NULL )
    {
        printf("Error opening file\n");
        return 1;   
    }
    fwrite(data, sizeof(struct Pet)*5, 1, outfile);
    fclose(outfile);
}

int read(){
    FILE* infile;
    if ((infile = fopen("data.bin", "rb")) == NULL)
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
	    printf("\nPeso: %f",pet.weight);
	    printf("\nSexo: %c \n",pet.gender);
    }
    fclose(infile);

    return 0;
}

int main(int argc, char* argv[])
{
    struct Pet* pets = malloc(sizeof(struct Pet)*5);  

    for (int n = 0; n<5; n++)
    {
        sprintf(pets[n].name,"Perla");
        sprintf(pets[n].type,"Perro");
        pets[n].age = n;
        sprintf(pets[n].race, "Schanauzer");
	    pets[n].height = n; 
	    pets[n].weight = n;
	    pets[n].gender='F';
    }

    write(pets);
    read();
    free(pets);
    return 0;
}