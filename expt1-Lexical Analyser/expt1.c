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
	int j = 0, l = 1;
	fp = fopen("program.txt","r");
	st = fopen("symbol_table.txt","r");
	if(fp == NULL)
	{
		printf("Error in opening file.\n");
		exit(0);
	}
	else
	{
		printf("\nLexeme\tLine\tToken");
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
									printf("\n%s\t%d\tIdentifier",buffer,l);
									
								j=0;
							}
						}
					}
				}
				if(ch == '<' || ch == '>')
				{
					ch1 = fgetc(fp);
					if(ch1 == '=')
						printf("\n%c%c\t%d\tRelational Operator",ch,ch1,l);
					else
					{
						fseek(fp,-1,SEEK_CUR);
						printf("\n%c\t%d\tRelational Operator",ch,l);
					}
				}
				else if(ch == '=')
				{
					ch1 = fgetc(fp);
					if(ch1 == '=')
					{
						printf("\n%c%c\t%d\tRelational Operator",ch,ch1,l);
					}
					else
					{
						fseek(fp,-1,SEEK_CUR);
						printf("\n%c\t%d\tAssignment Operator",ch,l);
					}
				}
				if(ch=='\n')
					l++;
			}
		}
	}
	printf("\n");
}

