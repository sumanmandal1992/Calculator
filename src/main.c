#include<stdio.h>
#include "calculation.h"
#define MAX 100

//Function prototype.///
void eatspace(char*);
//The main function.//////////////////////////////////////////////////
int main()
{
	char a[MAX];
	long double ans;
	printf("Enter your expression:\n");
	fgets(a, MAX, stdin);
	eatspace(a);
	ans = calculate(a);
	printf("\nResult: %Lf\n\n", ans);
	return 0;
}

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
