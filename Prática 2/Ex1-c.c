#include <stdio.h>
#include <stdlib.h>
#include "arrayGenerator.c"

int div_hash(int key, int m) {

	return key % m;

}


int main(){

    int nChaves = 10000;
    int m = 97;
    int arraySize = m+1;
    int* array = largeArrayGenerator(arraySize);    

    FILE* f = fopen("colisoesEx1c.csv", "w");
	
    for(int i = 1 ; i <= nChaves ; i++){

        array[div_hash(i, m)]++;

    }

    for(int i = 1 ; i < arraySize ; i++){
        
        fprintf(f, "%d;%d\n", i, array[i]);

    }

    fclose(f);

	return 0;
}