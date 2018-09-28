#include <stdlib.h>
#include <stdio.h>

int* array;
int* largeArrayGenerator(int size) {
	array = malloc(sizeof(int)*size);
	
	for(int i = 0 ; i < size ; i++) {
		array[i] = 0;
	}

	return array;
}