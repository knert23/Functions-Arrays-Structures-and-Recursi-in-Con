#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define size 55

struct stack{
    char elem[size];
    int count;
};

void push(struct stack *stk, char value){
    if (stk->count < size){
        stk->elem[stk->count] = value;
        stk->count++;
    }
    else{
        printf("STACK_OVERFLOW_PUSH\n");
         exit(EXIT_FAILURE); 
    }
}

char pop(struct stack *stk){
    char value;
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
char top(struct stack *stk){
    if((stk->count) > 0){
        return stk->elem[stk->count-1];
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

int isOperator_Priority(char operator){
	if(isdigit(operator)){
    	return 4;
    }
    switch(operator){
        case '*':
        case '/':
            return 3;
            break;          
        case '+':
        case '-':
            return 2;
            break;
        case '(':
        	return 0;
        	break;
        case ')':
        	return 1;
        	break;
        default:
        	return -1;
        	break;	
    }
}  


int main(void){
    printf("Введите выражение в инфиксном виде:\n");
    struct stack *stk = (struct stack*) (malloc(sizeof(struct stack)));
    char buffer[64];// массив для считывания ввода
    char outputString[64];// массив для записи постфиксного выражения
    scanf("%s", buffer);

    int oBrace = 0;
    int eBrace = 0;
    for(int i = 0; i < 64; i++){
    	if(buffer[i] == '('){
    		oBrace++;// считаем количество открывающихся скобок
    		if(isOperator_Priority(buffer[i + 1]) == 2 || isOperator_Priority(buffer[i + 1]) == 3){
    			printf("Syntax error: there should be no operators after the opening brace\n");
    			exit(EXIT_FAILURE);//не должно быть операторов после открывающейся скобки
    		}
    	}
    	if(buffer[i] == ')'){
    		eBrace++;// считаем количество закрывающихся скобок
    		if(isOperator_Priority(buffer[i - 1]) == 2 || isOperator_Priority(buffer[i - 1]) == 3){
    			printf("Syntax error: there should be no operators before the closing brace\n");
    			exit(EXIT_FAILURE);//не должно быть операторов перед закрывающейся скобкой
    		}
    	}
    	if(isOperator_Priority(buffer[0]) == 2 || isOperator_Priority(buffer[0]) == 3){
    		printf("Syntax error: the first character should not be the operator\n");
    		exit(EXIT_FAILURE);//первый символ не должен быть оператором
    	}
    	if(isdigit(buffer[i])){
    		if(isOperator_Priority(buffer[i+1]) == 4){
    			printf("Syntax error: the digit must not be followed by a digit\n");
    			exit(EXIT_FAILURE);//число не должно стоять после числа
    		}
    	}
    	if(isOperator_Priority(buffer[i]) == 2 || isOperator_Priority(buffer[i]) == 3){
    		if(isOperator_Priority(buffer[i + 1]) == 2 || isOperator_Priority(buffer[i + 1]) == 3){
    			printf("Syntax error: there should be no operator after the operator\n");
    			exit(EXIT_FAILURE);// не должно быть оператора после оператора
    		}
    	}
    	if(buffer[i] == '\0'){// последний символ не должен быть оператором
    		if(isOperator_Priority(buffer[i - 1]) == 3 || isOperator_Priority(buffer[i + 1]) == 2){
    			printf("Syntax error: the last character must not be an operator\n");
    			exit(EXIT_FAILURE);
    		}
    	}
    }
    if(oBrace != eBrace){ // проверяем, чтобы количество скобок было одинаковым
    	printf("Syntax error: the number of opening and closing brace is not equal.\n");
    	exit(EXIT_FAILURE);
    }

    int j = 0;
    int i = 0;
    int k;
    while(buffer[i] != '\0'){
    	//printf("in1\n");
    	int priority = isOperator_Priority(buffer[i]);
        //printf("priority:%d\n", priority);
        //printf("in2\n");
        switch(priority){
        	case 2:
        	case 3:
        		//printf("case23\n");
        		//printf("%c\n", buffer[i]);
        		//printf("priority_top:%d\n",isOperator_Priority(top(stk), i));
        		//printf("top:%c\n", top(stk));
        		if(isempty(stk)){
        			push(stk, buffer[i]);
        		}
	            else{
	            	//printf("priority_while:%d\n", priority);
	            	while(isOperator_Priority(top(stk)) >= priority){
	                outputString[i + j] = pop(stk);
	                j++;
	            	}
	            	push(stk, buffer[i]);
	            }
	            break;
	        case 0:
	        	//printf("case0\n");
                push(stk, buffer[i]);
                break;
            case 1:
            	//printf("case1\n");
                while(top(stk) != '('){
                    outputString[i + j] = pop(stk);
                    j++;
                }
                pop(stk);
                break;
            case 4:
            	//printf("case4\n");
            	outputString[i + j] = buffer[i];
            	break;	 
            case -1:
            	printf("Unknown syntax\n");
            	exit(EXIT_FAILURE);	          	      
        }
        //printf("%c\n", outputString[i + j]);
        i++;
        k = i + j;
    }
    while(!isempty(stk)){
        outputString[k] = pop(stk);
        k++;
    }

    for (int i = 0; i <= k; i++){
        printf("%c", outputString[i]);
    }
    printf("\n");

}