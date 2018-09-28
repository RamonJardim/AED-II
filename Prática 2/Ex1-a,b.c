#include <stdio.h>
#include <stdlib.h>

int div_hash(int key, int m) {

	return key % m;

}


int main(){

	int m1 = 12, m2 = 11;
	int nChaves = 100;


	printf("Chaves na posição 3 com m = 12: \n");

	for(int i = 0; i < nChaves; i++){

		if(div_hash(i, m1) == 3) {
			printf("%d ", i);
		}

	}

	printf("\n");

	printf("Chaves na posição 3 com m = 11: \n");

	for(int i = 0; i < nChaves; i++){

		if(div_hash(i, m2) == 3) {
			printf("%d ", i);
		}

	}
	
	printf("\n");
	
	return 0;
}

/* Para m = 12, todas as chaves x com h(x) = 3 são múltiplos de 3, pois 12 = 3 * 4 e portanto,
   todas as chaves da forma 12k+3, sendo k um número natural, têm h(x) = 3.*/

/* Para m = 11, não há nenhum padrão entre as chaves, pois 11 é primo, ou seja, não tem múltiplos. */