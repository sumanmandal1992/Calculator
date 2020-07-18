#include<stdio.h>
#include "Calculation.h"
#define MAX 100

//Function prototype.///
void eatspace(char*);
//The main function.//////////////////////////////////////////////////
void main()
{
char a[MAX];
printf("Enter your expression:\n");
fgets(a, MAX, stdin);
eatspace(a);
calculate(a);
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
