#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

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

int main(int argc, char* argv[])
{   
    
    for(int i=0;i<10;i++){

        struct Pet pet;

        //EL NOMBRE SE LEE DEL TXT DE NOMBRES
        sprintf(pet.name,"ASQUEROSO NOMBRE");
        
        sprintf(pet.type,"Perro");
        pet.age=rand()%14;
        pet.height=rand()%110;
        pet.weight=(rand()%101) + ((rand()%100)/100.0);

        switch (rand()%16) {
            case 0:
                sprintf(pet.race, "Schanauzer");
                break;
            case 1:
                sprintf(pet.race, "Doberman");
                break;
            case 2:
                sprintf(pet.race, "Chihuahua");
                break;
            case 3:
                sprintf(pet.race, "Bulldog");
                break;
            case 4:
                sprintf(pet.race, "Poodle");
                break;
            case 5:
                sprintf(pet.race, "Beagle");
                break;
            case 6:
                sprintf(pet.race, "Pug");
                break;
            case 7:
                sprintf(pet.race, "Husky");
                break;
            case 8:
                sprintf(pet.race, "Rottweiler");
                break;
            case 9:
                sprintf(pet.race, "Corgi");
                break;
            case 10:
                sprintf(pet.race, "ShihTzu");
                break;
            case 11:
                sprintf(pet.race, "BorderCollie");
                break;
            case 12:
                sprintf(pet.race, "GranDanes");
                break;
            case 13:
                sprintf(pet.race, "Doberman");
                break;
            case 14:
                sprintf(pet.race, "ChowChow");
                break;
            case 15:
                sprintf(pet.race, "Dalmata");
                break;

            default:
                break;
        }
        switch (rand()%2) {
            case 0:
                pet.gender='F';
                break;
            case 1:
                pet.gender='M';
                break;
            default:
                break;
        }

        printf("Nombre: %s",pet.name);	
	    printf("\t %s",pet.type);
	    printf("\t%i años",pet.age);	
	    printf("\n%s",pet.race);
	    printf("\t%i cm",pet.height);	
	    printf("\t %0.2f kg",pet.weight);
	    printf("\nSexo: %c \n",pet.gender);
    }
    
       
    return 0;
}