#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include<string.h>
char input[10],gram[10],stack[10];
int top=-1,ptr,in=0,a=0;

void shift(int index)
{	stack[++top]=input[index];
 	in++;
}
int reduce(int index)
{ 
	int f=0,i;
  	ptr=top;
  
	for(i=strlen(gram)-1;i>1;i--)
	{		
		if(stack[ptr--]!=gram[i])
		{
			f=1;
			//printf("%c %c noteq\n",stack[ptr+1],gram[i]);
			break;
		}
		else
		{
			//printf("%c %c eq\n",stack[ptr+1],gram[i]);
		}
	}
	if(f==0 && i==1)
	{
		//printf("eq\n");
		return 0;
	}
	else{
		//printf("noteq\n");
		return 1;
	}
}
void main()
{
 	FILE *fp,*fp2;
 	int n,len;
 	char s[10],st[10],new[10],pre,next;
 	fp=fopen("grammer.txt","w+");
	printf("\nEnter number of productions\n");
 	scanf("%d",&n);
 	for(int i=0;i<n;i++)
 	{
  		scanf("%s",s);
  		fprintf(fp,"%s\n",s);
  	}
  	fseek(fp,0,SEEK_SET);
  	printf("\nEnter input string\n");
  	scanf("%s",input);
  	printf("$\t%s$\n",input); 
  	shift(in);
  	printf("$");    
  	for(int i=0;i<=top;i++)
    {	
		printf("%c",stack[i]);
    }
    printf("\t");
    for(int i=in;i<strlen(input);i++)
    {	
		printf("%c",input[i]);
    }
    printf("$\tSHIFT\n");
  	while(in!=strlen(input)+1)
  	{	
		if(stack[top]=='S')
			break;
			int c=0;
			while(!feof(fp))
			{ 
				fscanf(fp,"%s",gram);
				a=reduce(1);
				if(a==0)
				{	
					//printf("%s\n",gram);
					top=top-(strlen(gram)-2);
					stack[++top]=gram[0];
					printf("$");    
					for(int i=0;i<=top;i++)
					{	
						printf("%c",stack[i]);
					}
					printf("\t");
					for(int i=in;i<strlen(input);i++)
					{	
						printf("%c",input[in]);
					}
					printf("$\t");
					printf("REDUCE by %s\n",gram);
					c=1;
					break;
				}
			
			}
			fseek(fp,0,SEEK_SET);
		if(c==0)
		{
			shift(in); 
			printf("$");    
			for(int i=0;i<=top;i++)
			{	
				printf("%c",stack[i]);
			}
			printf("\t");
			for(int i=in;i<strlen(input);i++)
			{	
				printf("%c",input[i]);
			}
			printf("$\t");
			printf("SHIFT\n");
		}
	}
	if(stack[top]=='S')
		printf("\nAccepted\n");
	else
		printf("\nNot Accepted\n");
}