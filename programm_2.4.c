#include <stdio.h>
#include <stdlib.h>
#define size 5

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
		printf("STACK_OVERFLOW\n");
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
	}
}

int top(struct stack *stk){
	if((stk->count) > 0){
		return stk->elem[stk->count-1];
	}
    else{
    	printf("STACK_UNDERFLOW_TOP\n");
    }
}  

int main(void){
	struct stack *stk;
	stk = (struct stack*) malloc(sizeof(struct stack));
	printf("Размер стека: %d\n", size);
	printf("Пытаемся взять значение со стека, когда он еще пуст\n");
	pop(stk); // Для вывода ошибки STACK_UNDERFLOW_POP
	printf("\nПытаемся взять верхнее значение со стека, когда он еще пуст\n");
	top(stk); // Для вывода ошибки STACK_UNDERFLOW_TOP
	int arr[5] = {1, 2, 3, 4, 5};
	for (int i = 0; i < 5; i++){
		push(stk, arr[i]);
	}
	printf("\nЗапушили массив в стек:\n");
	for (int i = 0; i < 5; i++){
		printf("arr[%d]=%d\n", i, arr[i]);
	}
	printf("\nПытаемся запушить еще один элемент в стек, на которого нет места\n");
	push(stk, 6); //для вывода ошибки STACK_OVERFLOW
	printf("\nПроверим верхнее значение стека: %d\n", top(stk));
	printf("\nВозьмем это значение: %d\n", pop(stk));
	printf("\nПроверим количество элементов в стекек: %d\n", stk->count);

	return 0;
}