#include<iostream>  
#include <fstream>
#include <stdio.h>
  
using namespace std; 
  
struct MyStruct{
	char name[32];
	char type[32];
	int age;
	char race[16];
	int height;
	float weight;
	char gender;
};

int printStruct(MyStruct* ap){
	struct MyStruct* data;
	data = ap;
	cout<<"Nombre: " << data->name <<endl;	
	cout<<"Tipo: " << data->type <<endl;
	cout<<"Edad: "<< data->age <<endl;	
	cout<<"Raza: " << data->race <<endl;	
	cout<<"Altura: " << data->height <<endl;	
	cout<<"Peso: "<< data->weight <<endl;	
	cout<<"Sexo: "<< data->gender<<endl;
	return(1);
}

int loadStruct(MyStruct* ap){
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
	

	ofstream myfile ("struct_file.txt");
	if (myfile.is_open()){
		myfile.write((char*)ap,sizeof(ap));
	}
	else{
		cout<<"Unable to open file \n";
	}
	myfile.close();
	return 0;

}

int readFile(MyStruct* ap){
	struct MyStruct* data;
	data=ap;

	ifstream myfile ("struct_file.txt");
	if (myfile.is_open()){
		myfile.read((char*)data, sizeof(data));
		printStruct(data);
	}
	else{
		cout<<"Unable to open file \n";		
	}
	myfile.close();
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
