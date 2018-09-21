#include "search.h"
#include "arrayGenerator.c"

int seq_search(int array[], int array_size, int key) {

	if(array_size == 0 || !array) {
		return -1;
	}

	int i;

	for(i = array_size-1 ; i >= 0 ; i--) {
		if(array[i] == key){
			return i;
		}
	}

	return i;

}

int binary_search(int array[], int array_size, int key) {

	if(array_size == 0 || !array) {
		return -1;
	}

	int low = 0, high = array_size, mid = array_size/2;

	while (low <= high) {

		if(array[mid] == key) {
			return mid;
		}

		else if(array[mid] > key) {
			high = mid - 1;
			mid = (low+high)/2;
		}

		else if(array[mid] < key) {
			low = mid + 1;
			mid = (low+high)/2;
		}

	}

	return -1;

}

int main() {

	clock_t t_inicio, t_fim;

	clock_t delta;
	
	int size = 1000000;					// Tamanho da array a ser gerada
	int *a = largeArrayGenerator(size); // Gera uma array ordenada de 0 a size
	int seqRes, binRes;

	/*-------------------*/

	printf("Tamanho do vetor: %d\n\n", size);

	/*-------BINARIA-----*/

	t_inicio = clock();
	binRes = binary_search(a, size, 0);
	t_fim = clock();
	delta = 1e6*(double)(t_fim - t_inicio)/CLOCKS_PER_SEC;

	printf("Busca binaria: %d\n", binRes);
	printf("Tempo (ns): %ld\n", delta);

	printf("\n");

	/*----SEQUENCIAL----*/

	t_inicio = clock();
	seqRes = seq_search(a, size, 0);
	t_fim = clock();
	delta = 1e6*(double)(t_fim - t_inicio)/CLOCKS_PER_SEC;
	
	printf("Busca sequencial: %d\n", seqRes);	
	printf("Tempo (ns): %ld\n", delta);

	return 0;
}

/* 		A busca binária tem complexidade O(log(n)), e para checar se o vetor está ordenado obriga que todo	*/
/* o vetor seja percorrido, portanto tem complexidade O(n). Dessa forma, verificar se o vetor está ordenado	*/
/* antes de fazer a busca binária aumentaria sua complexidade para O(n), tornando-a ineficiente			  	*/