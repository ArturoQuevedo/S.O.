#include <stdio.h>
  
struct MyStruct{
	char name[32];
	char type[32];
	int age;
	char race[16];
	int height;
	float weight;
	char gender;
};

int printStruct(void* ap){
	struct MyStruct* data;
	data = ap;
	printf("Nombre: %s",data->name);	
	printf("Tipo: %s",data->type);
	printf("Edad: %i",data->age);	
	printf("Raza: %s",data->race);
	printf("Altura: %i",data->height);	
	printf("Peso: %f",data->weight);
	printf("sexo: %c",data->gender);
	return(1);
}

int loadStruct(void* ap){
	struct MyStruct* data;
	data = ap;
	
	/*cout<<"Nombre"<<endl;
	cin>>data->name;	
	cout<<"Tipo"<<endl;
	cin>>data->type;
	cout<<"Edad"<<endl;
	cin>>data->age;	
	cout<<"Raza"<<endl;
	cin>>data->race;
	cout<<"Altura"<<endl;
	cin>>data->height;
	cout<<"Peso"<<endl;
	cin>>data->weight;
	cout<<"Sexo"<<endl;
	cin>>data->gender;*/
		
	sprintf(data->name,"Perla");
	sprintf(data->type, "perro");	;
	data->age = 2;
	sprintf(data->race, "schnauzer");
	data->height = 1;
	data->weight = 1.5;
	data->gender='F';
	
	
	return(1);
}

int writeInFile(void* ap){
	struct MyStruct* data;
	

	FILE *fp;
    fp = fopen("struct.bin","w");

	if (fp){
        fwrite((char*)ap,sizeof(ap),1,fp);
	}
	else{
	    printf("\n unable to open file \n");
	}
    fclose(fp);
	return 0;

}

int readFile(void* ap){
	struct MyStruct* data;
	data=ap;

    FILE *fp;
	fp = fopen("struct.bin","r");
	if (fp){
        fread((char*)data, sizeof(data),1,fp);
		printStruct(data);
	}
	else{
		printf("\n unable to open file \n");	
	}
	fclose(fp);
	return 0;


}

int main() 
{
	
	struct MyStruct pet;
	struct MyStruct* pointer=&pet;
	
	loadStruct(pointer);
	//printStruct(pointer);
	writeInFile(pointer);
	readFile(pointer);


			
      
    return 0; 
}