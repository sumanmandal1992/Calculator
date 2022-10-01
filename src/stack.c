#include "stack.h"


/*
 * Prototype declaration.
 */
static bool isEmpty(Stack *top);
static Stack *create();


Stack *newStack(void)
{
	return NULL;
}

static Stack *create()
{
	Stack *temp = (Stack *)malloc(sizeof(Stack));
	if(temp == NULL) {
		printf("Failed to create stack\n");
		return NULL;
	}

	temp->info = (Info *)malloc(sizeof(Info));
	if(temp->info == NULL) {
		printf("Failed to create element\n");
		return NULL;
	}
	temp->isOperator = false;
	temp->next = NULL;
	return temp;
}


void push(Stack **top, Info *info, bool isOperator)
{
	Stack *temp = create();

	if(temp == NULL) {
		printf("Unable to push element...\n");
		return;
	}

	if(isOperator)
	{
		temp->info->operator = info->operator;
		temp->isOperator = isOperator;
	}
	else
	{
		temp->info->number = info->number;
		temp->isOperator = isOperator;
	}

	if(*top != NULL)
		temp->next = *top;
	*top = temp;
	temp = NULL;
}

void pop(Stack **top)
{
	Stack *temp = *top;

	if(!isEmpty(*top)) {
		*top = (*top)->next;
		free(temp->info);
		free(temp);
	} else {
		printf("Stack is empty...\n");
	}
}

static bool isEmpty(Stack *top)
{
	if(top == NULL)
		return true;
	else
		return false;
}

void display(Stack *top)
{
	Stack *temp = top;
	while(temp != NULL)
	{
		if(temp->isOperator)
			printf("%c\n", temp->info->operator);
		else
			printf("%lf\n", temp->info->number);
		temp = temp->next;
	}
}
