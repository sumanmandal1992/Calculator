#include<stdio.h>
#define MAX 100

int isvalidexp(char*);
void eatspace(char*);
int isoperator(char);

int main()
{
	char a[MAX];
	fgets(a, MAX, stdin);
	eatspace(a);
	if(!isvalidexp(a))
		printf("Error found\n");
	else
		printf("No error found\n");
	puts(a);
	return 0;
}

int isvalidexp(char *a)
{
	int bracket=0, i=0;

	if(isoperator(a[i])==1)
		return 0;

	while(a[i]!='\0'){

		switch(a[i]) {

			case '(':
				bracket++;
				break;

			case ')':
				bracket--;
				break;

			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
			case '%':
				break;

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				break;

			default:
				return 0;
		}
		//Check if two operators are encounterd one by one..
		if(isoperator(a[i])==1 && isoperator(a[i+1])==1)
			return 0;

		if(isoperator(a[i])==2 && isoperator(a[i+1])==2 && isoperator(a[i+2])==2)
			return 0;

		i++;
	}

	if(bracket==0)
		return 1;
	else
		return 0;
}

//Remove space/s within expression.////
void eatspace(char *a)
{
	int i=0, j;
	while(a[i]!='\0'){
		if(a[i]==' ' || a[i]=='\t' || a[i]=='\n'){
			j=i;
			for(;a[j]!='\0';j++){
				a[j]=a[j+1];
			}
		}
		i++;
	}
}

int isoperator(char a)
{
	switch(a){
		case '*':
		case '/':
		case '^':
		case '%':
			return 1;
	}

	switch(a){
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case '%':
			return 2;
	}

	return 0;
}
