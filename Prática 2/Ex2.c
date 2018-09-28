#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arrayGenerator.c"

int mul_hash(int key, int m, float a) {
    float s = key * a;
	return (int) (m*(s-floor(s)));
}


int main(){
    int m = 200;
    int nChaves = 500000;
    int arraySize = m+1;
    int* array1 = largeArrayGenerator(arraySize);
    int* array2 = largeArrayGenerator(arraySize);

    float a1 = 0.62;
    float a2 = 0.61803398875;

    FILE* f1 = fopen("colisoesMul0,62.csv", "w");
    FILE* f2 = fopen("colisoesMul0,618.csv", "w");
	
    for(int i = 1 ; i <= nChaves ; i++){

        array1[mul_hash(i, m, a1)]++;
        array2[mul_hash(i, m, a2)]++;

    }


    for(int i = 1 ; i < arraySize ; i++){
        
        fprintf(f1, "%d;%d\n", i, array1[i]);
        fprintf(f2, "%d;%d\n", i, array2[i]);
    }

    fclose(f1);
    fclose(f2);

	return 0;
}