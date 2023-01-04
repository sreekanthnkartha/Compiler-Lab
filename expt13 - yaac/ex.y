%{
#include<stdio.h>
int flag=0;
%}
%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%%
ArithmeticExpression: E{printf("\nResult = %d\n",$$);return 0;};
E:E'+'E {$$=$1+$3;}
|E'-'E {$$=$1-$3;}
|E'*'E {$$=$1*$3;}
|E'/'E {$$=$1/$3;}
|E'%'E {$$=$1%$3;}
|'('E')' {$$=$2;}
| NUMBER {$$=$1;}
;
%%
void main()
{
printf("\nInput an arithmetic expression:-\n");
yyparse();
if(flag==0)
printf("\nThe given arithmetic expression is valid.\n\n");
}
void yyerror()
{
printf("\nThe given arithmetic expression is invalid\n\n");
flag=1;
}
//yacc -d Pg13.y
//lex Pg13.l
//gcc lex.yy.c y.tab.c -w
//./a.out

