#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int shakerSorting(double *mas, int sizeMas){
	int left = 0;
	int right = sizeMas - 1;
	int k = 1;
	while((left < right) & (k > 0)){
		k = 0;
		for (int i = left; i < right; i++){
			if (mas[i] >= mas[i + 1]){
				double auxiliaryMas1 = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = auxiliaryMas1;
				k = 1;
			}
		}
		right--;
		for(int j = right; j > left; j--){
			if(mas[j - 1] >= mas[j]){
				double auxiliaryMas2 = mas[j];
				mas[j] = mas[j - 1];
				mas[j - 1] = auxiliaryMas2;
				k = 1;
			}
		}
		left++;
	}
}

int main(int argc, char *argv[]){
	printf("Введите размер массива:\n");
	int sizeMas;
	scanf("%d", &sizeMas);
	double mas[sizeMas];

	printf("Массив со случайными числами:\n");
	srand(time(NULL));
	for (int i = 0; i < sizeMas; i++){
		mas[i] = (float)rand() / (float)RAND_MAX;
		printf("mas[%d]=%f\n", i, mas[i]);
	}

	shakerSorting(mas, sizeMas);

	FILE *file;
	file = fopen(argv[1], "w");
	for(int i = 0; i < sizeMas; i++){
		fprintf(file, "mas[%d]=%f\n", i, mas[i]);
	}
	fclose(file);

	return 0;
}