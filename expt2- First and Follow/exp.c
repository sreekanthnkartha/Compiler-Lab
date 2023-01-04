
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include<string.h>
void first()
{
 FILE *ft;
 //fseek(fp,0,SEEK_SET);
 
 
}
void follow()
{FILE *fl;
 
}

void main()
{
	FILE *fp,*fp2;
	int n,len;
	char s[10],st[10],new[10],pre,next;
	fp=fopen("grammer.txt","w+");
	fp2=fopen("grammer2.txt","w+");
	printf("\nEnter number of productions\n");
	scanf("%d",&n);
	fprintf(fp,"\n");
	for(int i=0;i<n;i++)
	{
		scanf("%s",s);
		fprintf(fp,"%s\n",s);
	}
	fseek(fp,0,SEEK_SET);
	while(!feof(fp))
   	{
    	fscanf(fp,"%s",st);
    	int f=0;
    	len=strlen(st);
    	for(int i=0;i<len;i++)
    	{	
			if(st[i]=='=' || st[i]=='|')
    		{	
				if(st[0]==st[i+1])
				{	
					i++;
					f=1;
					fprintf(fp2,"%c'=",st[0]);
					i++;
					while((st[i]!='|'&& i<len))
					{	
						
						fprintf(fp2,"%c",st[i]);
						i++;
					}
					//fprintf(fp2,"\nlata\n");
					fprintf(fp2,"%c'|#\n",st[0]);
					i--;
					continue;
			
				}
				else
				{	i++;
					if(f==1)
					{	fprintf(fp2,"%c=",st[0]);
						while((st[i]!='|' && i<len))
						{	
							fprintf(fp2,"%c",st[i]);
							i++;
						}
						fprintf(fp2,"%c'\n",st[0]);
						i--;
						continue;
					}
					else
					{
						fprintf(fp2,"%s\n",st);
						continue;
					}
				}	    		
    		}
    	}
    }
}