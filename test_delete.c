int deletebyid(int *hashTable)
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
