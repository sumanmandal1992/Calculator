int isvalidexp(char*);
int isoperator(char);

//////////////////////////
//Check valid Expression//
//////////////////////////
int isvalidexp(char *a)
{
int bracket=0, i=0;

if(a[0]=='*' || a[0]=='/' || a[0]=='^')
return 0;

while(a[i]!='\0'){

switch(a[i]){

case '(':
++bracket;
break;

case ')':
--bracket;
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

i++;
}

if(bracket==0)
return 1;
else
return 0;
}

/////////////////////////
//Check valid operators//
/////////////////////////
int isoperator(char a)
{
	switch(a){
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			return 1;
	}
	return 0;
}
