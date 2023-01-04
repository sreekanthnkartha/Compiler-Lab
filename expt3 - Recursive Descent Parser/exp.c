#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include<string.h>
char stack[10];
int top=-1,res,fin=0;
char in[10];
void dis()
{ for(int a=top;a>=0;a--)
  {printf("\n%c",stack[a]);
  }printf("\n");
  
}
int recur(char t,int i)
{ if(i==strlen(in))
	   fin=1;
  printf("%d\n" ,i);
 if((t=='X' && isalpha(in[i]))||(t==in[i]))
	{ 
	 i++;
	 res=res+recur(stack[top--],i);
	 dis();
	 return 0;
	}
  switch(t)
  {case 'E':stack[++top]='Z';
  	    stack[++top]='T';
  	  dis();
  	    res=res+recur(stack[top--],i);
  	      dis();
  	    return 0;
   case 'Z':if(in[i]=='+'){
   	    stack[++top]='Z';
   	    stack[++top]='T';
   	    stack[++top]='+';
   	    dis();
   	    res=res+recur(stack[top--],i);
   	    dis();
   	    }
   	    else
   	    {res=0;
   	     res=res+recur(stack[--top],i);
   	       dis();
   	    }
   	    return 0;
  case 'T':stack[++top]='Y';
   	    stack[++top]='F';dis();
   	    res=res+recur(stack[top--],i);  
   	    dis();
   	    return 0;
  case 'Y': if(in[i]=='*'){
  	    stack[++top]='Y';
   	    stack[++top]='F';
   	    stack[++top]='*';dis();
   	    res=res+recur(stack[top--],i);
   	      dis();
   	      }
   	    else
   	    {res=0;
   	     res=res+recur(stack[--top],i);
   	       dis();
   	    }
   	    return 0;
  case 'F': stack[++top]='X';dis();
   	    res=res+recur(stack[top--],i);
   	      dis();
   	     res=res+recur(stack[top--],i);
   	    if(in[i]==')'){
   	    stack[++top]='(';
   	    stack[++top]='E';
   	    stack[++top]=')';dis();
   	    res=res+recur(stack[top--],i);
   	      dis();
   	     }  	    
   	    return 0;	    
  	    
  }
  return 1;
}
void main()
{
  printf("Enter the input string\n");
  scanf("%s",in);
  top++;
  stack[top]='E';
  dis();
  res=res+recur(stack[top--],0);  
  dis();
  printf("%d %d %d",res,top,fin);
  if(res==0 &&top==-1 && fin==1)
  printf("accepted");
  else
  printf("Unacceptable");                                   
  
}
