//Experiment No: 1
//Experiment Name: Lexical Analyzer
//Author: Vidya V
//Date: 15/09/2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

char keyword[32][10] = {
	"break", "case", "auto", "const", "continue", "default", "do", "double", "else",
	"enum", "extern", "float", "for", "goto", "if", "int", "log", "register", "return",
	"short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
	"unsigned", "void", "volatile", "while", "char"
};

int flag,i;

int isKeyword(char buffer[])
{
	flag = 0;
	for(i = 0; i<32; i++)
	{
		if(strcmp(keyword[i],buffer) == 0)
		{
			flag=1;
			break;
		}
	}
	return flag;
}

void main()
{
	char ch, ch1, buffer[50], operator[]="+-*/%";
	FILE *fp,*st;
	int j = 0, l = 1,sl=1;
	fp = fopen("program.txt","r");
	st = fopen("symbol_table.txt","w+");
	if(fp == NULL)
	{
		printf("Error in opening file.\n");
		exit(0);
	}
	else
	{
		printf("\nLexeme\tLine\tToken\t\tsymbol table");
		while((ch = fgetc(fp)) != EOF)
		{
			for(i=0; i<5; i++)
			{
				if(ch == operator[i])
				{
					printf("\n%c\t%d\tArithmetic Operator",ch,l);
					break;
				}
			}
			if(i==5)
			{
				if(isalnum(ch))
				{
					if(isdigit(ch) && j==0) {}
					else
					{
						buffer[j++] = ch;
						ch1 = fgetc(fp);
						if(isalnum(ch1))
							fseek(fp,-1,SEEK_CUR);
						else
						{
							fseek(fp,-1,SEEK_CUR);
							buffer[j] = '\0';
							if(isKeyword(buffer) == 1)
							{
								printf("\n%s\t%d\tKeyword",buffer,l);
								j=0;
							}
							else
							{
								if(strcmp(buffer,"main")!=0)
								{
									if(strcmp(buffer,"printf")==0)
									{	
										ch = fgetc(fp);
									 	while(ch!=')')
									 		ch = fgetc(fp);
									 	printf("\n%s\t%d\tFunction\t\t",buffer,l);
									 	continue;
									}
									 
									int flag=0;
									char s[10],s1,pre[10],index[10];
									strcpy(s,"\0");
									fseek(st,0,SEEK_SET);
									while(!feof(st))
									{
										strcpy(pre,s);
									 	fscanf(st,"%s",s);
										//del
										//printf("\n%s\n",s);
										
										if(strcmp(s,buffer)==0)
										{
											flag=1;
											strcpy(index,pre);
											//del
											//printf("j%s%sj",index,s);
										}
									 
									}
									if(flag==0)
									{
										sprintf(index,"%d",sl);
										int n=0;
										if(s1=fgetc(fp)=='=')
										{
											char k=fgetc(fp);
											fprintf(st,"\n%d\t%s\t%c%c\n",sl++,buffer,k,fgetc(fp));
											fseek(fp,-3,SEEK_CUR);
										}
										else
										{
											fprintf(st,"\n%d\t%s\t%c\n",sl++,buffer,'_');
										}
									}
									
									printf("\n%s\t%d\tIdentifier\t\t%s",buffer,l,index);
									//printf("y");
								}
								else
									printf("\n%s\t%d\tFunction\t\t",buffer,l);
									
								j=0;
							}
						}
					}
				}
				if(ch == '<' || ch == '>')
				{
					
					if(ch == '<')
					{	
						ch1 = fgetc(fp);
						if(ch1 == '=')
							printf("\n%c%c\t%d\tRelational Operator\tLE",ch,ch1,l);
						else
						{
							fseek(fp,-1,SEEK_CUR);
							printf("\n%c\t%d\tRelational Operator\tLT",ch,l);
						}
					}
					if(ch== '>')
					{
						ch1 = fgetc(fp);
						if(ch1 == '=')
							printf("\n%c%c\t%d\tRelational Operator\tGE",ch,ch1,l);
						else
						{
							fseek(fp,-1,SEEK_CUR);
							printf("\n%c\t%d\tRelational Operator\tGT",ch,l);
						}
					}
				}
				else if(ch == '=')
				{
					ch1 = fgetc(fp);
					if(ch1 == '=')
					{
						printf("\n%c%c\t%d\tRelational Operator\tEQ",ch,ch1,l);
					}
					else
					{
						fseek(fp,-1,SEEK_CUR);
						printf("\n%c\t%d\tAssignment Operator\tEQ",ch,l);
					}
				}
				if(ch=='\n')
					l++;
			}
		}
	}
	printf("\n");
}


/*
OUTPUT
Lexeme	Line	Token		symbol table
void	1	Keyword
main	1	Function		
int	3	Keyword
a	3	Identifier		1
b	3	Identifier		2
=	3	Assignment Operator	EQ
c	3	Identifier		3
=	3	Assignment Operator	EQ
char	4	Keyword
ch	4	Identifier		4
a	5	Identifier		1
=	5	Assignment Operator	EQ
b	5	Identifier		2
+	5	Arithmetic Operator
c	5	Identifier		3
b	6	Identifier		2
=	6	Assignment Operator	EQ
if	7	Keyword
a	7	Identifier		1
<=	7	Relational Operator	LE
b	7	Identifier		2
a	8	Identifier		1
=	8	Assignment Operator	EQ
b	8	Identifier		2
printf	9	Function

SYMBOL TABLE

1	a	_

2	b	10

3	c	0 

4	ch	_
*/

