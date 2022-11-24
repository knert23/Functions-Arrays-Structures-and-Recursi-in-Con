#include <stdio.h>

struct goods{
	char name[128];
	float cost;
};

int shakerSorting(struct goods *mas, int countString){
	int left = 0;
	int right = countString - 1;
	int k = 1;
	while((left < right) & (k > 0)){
		k = 0;
		for (int i = left; i < right; i++){
			if (mas[i].cost >= mas[i + 1].cost){
				struct goods tempCost1 = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = tempCost1;
				k = 1;
			}
		}
		right--;
		for(int j = right; j > left; j--){
			if(mas[j - 1].cost >= mas[j].cost){
				struct goods tempCost2 = mas[j];
				mas[j] = mas[j - 1];
				mas[j - 1] = tempCost2;
				k = 1;
			}
		}
		left++;
	}
}

int main(int argc, char *argv[])
{
	FILE *inputFile;
	FILE *outputFile;
	inputFile = fopen(argv[1], "r");

	int countString;
	while(!feof(inputFile)){
		if(fgetc(inputFile) == '\n'){
			countString++;
		}
	}

	struct goods shop[countString];
	int i = 0;
	fseek(inputFile, 0, SEEK_SET);
	while(!feof(inputFile)){
		fscanf(inputFile, "%s%f", shop[i].name, &shop[i].cost);
		i++;
	}
	fclose(inputFile);

	shakerSorting(shop, countString);

	outputFile = fopen(argv[2], "w");
	for(int c = 0; c < countString; c++){
		fprintf(outputFile, "%s %.2f\n", shop[c].name, shop[c].cost);
	}
	fclose(outputFile);

	printf("Программа успешно выполнена!\n");

	return 0;
}