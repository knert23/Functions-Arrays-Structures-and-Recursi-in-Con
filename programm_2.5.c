#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define size 55

struct stack{
    int elem[size];
	int count;
};

void push(struct stack *stk, int value){
	if (stk->count < size){
		stk->elem[stk->count] = value;
		stk->count++;
	}
	else{
		printf("STACK_OVERFLOW_PUSH\n");
		 exit(EXIT_FAILURE); 
	}
}

int pop(struct stack *stk){
	int value;
	if (stk->count > 0){
		stk->count--;
		value = stk->elem[stk->count];
		return value;
	}
	else{
		printf("STACK_UNDERFLOW_POP\n");
		exit(EXIT_FAILURE); 
	}
}

int top(struct stack *stk){
	if((stk->count) > 0){
		return stk->elem[stk->count-1];
	}
    else{
    	return 0;
    	printf("STACK_UNDERFLOW_TOP\n");
    }
}  

bool isempty(struct stack *stk){
	if (stk->count == 0){
		return true;
	}
	else {
		return false;
	}
}

//вычисление выражения в стеке
int operation(struct stack *stk, char operator, int i){
	int secondValue;
	int firstValue;

	secondValue = pop(stk);
	firstValue = pop(stk);

	switch (operator){
		case '+':
			push(stk, firstValue + secondValue);
			break;
		case '-':
			push(stk, firstValue - secondValue);
			break;
		case '*':
			push(stk, firstValue * secondValue);
			break;
		case '/':
			push(stk, firstValue / secondValue);
			break;
    }
}

bool isOperator(char operator){  
	if(operator == '+' || operator == '-' || operator == '*' || operator == '/'){
		return true;  
	}
	else{
		return false;
	}
}  

//вычисление выражения в постфиксной записи
int calculating(char *array, int row, struct stack *stk){
	if (!isempty(stk)){
		while(!isempty(stk)){
			pop(stk);
		}
	}

	for (int i = 0; i < row; i++){
		if (array[i] == '\n' || array[i] == '\0'){
			printf(" = %d\n", pop(stk)); //для вывода
			continue;
		}
		else{
			if (isdigit(array[i])){
				push(stk, array[i] - '0'); // array[i] - число, пушим в стек
			}
			if (isOperator(array[i])){
				operation(stk, array[i], i); // array[i] - операнд, выполняем операцию
			}
		}
		printf("%c", array[i]); //для вывода
	}
}

int main(int argc, char *argv[]){
	FILE *file;
	file = fopen(argv[1], "r");

	//определение количества символов в тексте = размер массива (последний элемент в массиве: '\0')
	int col = 0;
	for (char c = fgetc(file); c != EOF; c = fgetc(file)){
		col++;
	}
	char array[col];

	//чтение и запись
	fseek(file, 0, SEEK_SET);
	int i = 0;
	while (!feof(file)){
		array[i] = fgetc(file);
		i++;
	}
	fclose(file);

	struct stack *stk;
	stk = (struct stack*) malloc(sizeof(struct stack)); //выделяем память под стек

	char *p_a = &array[0];
	calculating(p_a, col, stk);
	free(stk);
}