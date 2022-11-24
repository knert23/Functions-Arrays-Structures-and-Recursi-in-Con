#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

 long int random(void){
	long int systemTime = time(NULL);
	long int operator = (846 + 327) % 1000;
	long int rand = systemTime * operator;
	return rand;
}

int main(int argc, char *argv[]){
	int sizeMas;
	printf("Введите размер массива\n");
	scanf("%d", &sizeMas);
	int mas[sizeMas];
	for(int i = 0; i < sizeMas; i++){
		mas[i] = random();
		mas[i] = mas[i] % (long int) (437 * (i + 59) / (i+1)) - i;
		printf("mas[%d]=%d\n", (i + 1), mas[i]);
	}

	FILE *file;
	file = fopen(argv[1], "w");
	for(int j = sizeMas - 1; j >= 0; j--){
		fprintf(file, "mas[%d]=", j + 1);
		fprintf(file, "%d", mas[j]);
		fputs("\n", file);
	}

	fclose(file);

	return 0;
}