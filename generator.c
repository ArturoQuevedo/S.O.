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
	int prev;
	int next;
};

int write(void* ap){
    struct Pet* data;
    data=ap;

    FILE* outfile;
    if ( (outfile = fopen("datadogs.dat", "wb")) == NULL )
    {
        printf("Error opening file\n");
        return 1;   
    }
    fwrite(data, sizeof(struct Pet)*5, 1, outfile);
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
	    printf("\nPeso: %f",pet.weight);
	    printf("\nSexo: %c",pet.gender);
	    printf("\nNext: %i",pet.prev);
	    printf("\nPrev: %i \n",pet.next);
    }
    fclose(infile);

    return 0;
}

int change(void* ap,long pos){
    struct Pet* data;
    data=ap;

    FILE* outfile;
    if ( (outfile = fopen("datadogs.dat", "r+")) == NULL )
    {
        printf("Error opening file\n");
        return 1;   
    }
    fseek(outfile,sizeof(struct Pet) *pos,SEEK_SET);
    fwrite(data, sizeof(struct Pet), 1, outfile);
    fclose(outfile);
    printf("\n write: %li \n",pos);
    return 0;
}

int readpos(long pos){
    FILE* file;
    file = fopen("datadogs.dat", "r+");
    
    fseek(file,sizeof(struct Pet)*pos,SEEK_SET);
    struct Pet pet;
    fread(&pet,sizeof(struct Pet),1,file);
    printf("\n/////// readpos ///////\n");
    printf("Nombre: %s",pet.name);	
	    printf("\nTipo: %s",pet.type);
	    printf("\nEdad: %i",pet.age);	
	    printf("\nRaza: %s",pet.race);
	    printf("\nAltura: %i",pet.height);	
	    printf("\nPeso: %f",pet.weight);
	    printf("\nSexo: %c",pet.gender);
	    printf("\nNext: %i",pet.prev);
	    printf("\nPrev: %i \n",pet.next);
    fclose(file);
    return 0;
}

//-----------MAIN---------------//
int main(int argc, char* argv[])
{
    struct Pet* pets = malloc(sizeof(struct Pet)*5);  
    struct Pet pet;

    for (int n = 0; n<5; n++)
    {
        sprintf(pets[n].name,"Perla");
        sprintf(pets[n].type,"Perro");
        pets[n].age = n;
        sprintf(pets[n].race, "Schanauzer");
	    pets[n].height = n; 
	    pets[n].weight = n;
	    pets[n].gender='F';
	    pets[n].prev = n;
	    pets[n].next = n;
    }
    write(pets);

    read();

        printf("\n/////// test ///////\n");
        sprintf(pet.name,"Perla");
        sprintf(pet.type,"Perro");
        pet.age = 321;
        sprintf(pet.race, "Schanauzer");
	    pet.height = 321; 
	    pet.weight = 321;
	    pet.gender='F';
	    pet.prev = 321;
	    pet.next = 321;
        change(&pet,1);
    readpos(1);

    printf("\n/////// after change ///////\n");
    read();

    free(pets);
    return 0;
}
