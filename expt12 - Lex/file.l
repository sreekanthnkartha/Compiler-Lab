%{
#include <stdio.h>
#include<string.h>
int no=0,lno=0,cno=0,sno=0;
%}

ident [a-zA-Z][a-zA-Z0-9]*

%%
"\n" {lno++;}
{ident} {no++;cno+=strlen(yytext);}
" " {sno++;}


%%
int main()
{
	yyin=fopen("input.txt","r");
	yylex();
	printf("\nLine count : %i\n",lno);
	printf("Word count : %i\n",no);
	printf("char count : %i\n",cno+sno);
}

