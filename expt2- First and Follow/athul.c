#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>


char firsts[10][100];
char grams[10];
int fcount[10]={0,0,0,0,0,0,0,0,0,0};
int dcount=0;
/*
void removeLR(){

FILE *fp,*inm;
char buffer[100];
fp = fopen( "grammer.txt","r");
inm = fopen( "intermediate.txt","w");
if(fp==NULL)
{
  	printf("File could not be opened!\n");
  	exit(0);
}	
if(inm==NULL)
{
  	printf("File could not be opened!\n");
  	exit(0);
}
fscanf(fp,"%s",buffer);
	
while(!feof(fp))
{
	char rhs[10][10],adRhs[10][10],aRhs[10][10];
	
	char lhs=buffer[0];
	int count=0,ind=0,lrCount=0,aCount=0;;
	for(int i=3;i<strlen(buffer);i++)
	{
	
		if(buffer[i]=='|')
		{
			rhs[count][ind]='\0';
			count++;
			ind=0;
			
		}
		else
		{
			rhs[count][ind]=buffer[i];
			ind++;
		}
		
	}
	rhs[count][ind]='\0';
	count++;
	char aDash[2];
	aDash[0]=(char)('Z'-(buffer[0]-'A'));
	aDash[1]='\0';
	for(int i=0;i<count;i++)
	{
		if(rhs[i][0]==buffer[0])
		{
			strncpy(adRhs[lrCount],rhs[i]+1,strlen(rhs[i])-1);
			strcat(adRhs[lrCount],aDash);
			lrCount++;
		}
		else
		{
			strcpy(aRhs[aCount],rhs[i]);
			strcat(aRhs[aCount],aDash);
			aCount++;
		}
	}
	char aDer[100],adDer[100];
	aDer[0]=buffer[0];
	aDer[1]='\0';
	strcat(aDer,"->");
	for(int i=0;i<aCount;i++)
	{
		strcat(aDer,aRhs[i]);
		if(i!=aCount-1)
			strcat(aDer,"|");
	}
	if(lrCount>0)
	{
		adDer[0]='\0';
		strcat(adDer,aDash);
		strcat(adDer,"->");
		for(int i=0;i<lrCount;i++)
		{
			strcat(adDer,adRhs[i]);
			strcat(adDer,"|");
		}
		strcat(adDer,"$");
		fprintf(inm,"%s\n",aDer);
		fprintf(inm,"%s\n",adDer);
	
	}
	else
		fprintf(inm,"%s\n",buffer);
	fscanf(fp,"%s",buffer);
	
}

fclose(inm);
fclose(fp);
}

*/
void findFirst(){

FILE *fp,*inm;
char buffer[100];
inm = fopen( "grammer.txt","r");
fp = fopen( "first.txt","w");
if(fp==NULL)
{
  	printf("File could not be opened!\n");
  	exit(0);
}	
if(inm==NULL)
{
  	printf("File could not be opened!\n");
  	exit(0);
}

fscanf(inm,"%s",buffer);
	
while(!feof(inm))
{
	char rhs[10][10];
	int fc=0;
	char lhs=buffer[0];
	int count=0,ind=0,lrCount=0,aCount=0;
	//iteration starts from 3 to iterate through RHS, excluding the LHS and '->'
	// Assuming the LHS contains only one character
	for(int i=3;i<strlen(buffer);i++)
	{
	
		if(buffer[i]=='|')
		{
			// IF the grammer is finished, it is ended with '/0'
			rhs[count][ind]='\0';
			count++;
			ind=0;
			
		}
		else
		{
			//Each grammer is stored to seperate variables.
			//count: index of current grammer
			//ind: index of current character in the current grammer
			rhs[count][ind]=buffer[i];
			ind++;
		}
		
	}

	// IF the grammer is finished, it is ended with '/0'		
	rhs[count][ind]='\0';
	count++;

	// LHS is stored to the grams variable
	// dcount is the index of each derivation 
	grams[dcount]=buffer[0];
	


    /*
	For example, consider:
	A->bCD|aCb

	rhs[0] = "bCD"
	rhs[1] = "aCb"
	grams[0]= 'A'
	*/

	// for each grammer
	for(int i=0;i<count;i++)
	{
		//fcount is the first count, i.e. the number of firsts for the non terminal
		// the first character of each grammer in rhs is assigned as a first, even if it is a nonterminal
		firsts[dcount][fcount[dcount]]=rhs[i][0];
		fcount[dcount]++;
	}

	// for each derivation, till now
	for(int i=0;i<dcount;i++)
	{
		// for each first of that non terminal
		for(int j=0;j<fcount[i];j++)
		{
			//We have added non terminals also to the first.
			// If the current non terminal (LHS) is in the first of i th non terminal, then
			if(firsts[i][j]==lhs)
			{
				//we have found the first of current non terminal.
				// Thus add its first to the first of ith no terminal
			
				for(int k=0;k<fcount[dcount];k++)
				{
					firsts[i][fcount[i]]=firsts[dcount][k];
					fcount[i]++;
				}
				break;
			}
		}
	}
	
	
	
	dcount++;
	
	fscanf(inm,"%s",buffer);



	//(RHS is not stored and is reseted while reading the next derivation, as that is no longer needed)
}


// Earlier, non terminals present in the first were replaced only if its derivation occured after.
// Below loop does the same for the opposite case.

for(int i=0;i<dcount;i++)
	{
	for(int m=i+1;m<dcount;m++)
	{
		for(int j=0;j<fcount[m];j++)
		{
			if(firsts[m][j]==grams[i])
			{
				for(int k=0;k<fcount[i];k++)
				{
					firsts[m][fcount[m]]=firsts[i][k];
					fcount[m]++;
				}
				break;
			}
		}
	}
}
printf("The firsts are:");
for(int i=0;i<dcount;i++)
	{
		printf("\nFIRST(%c): ",grams[i]);
	
		for(int j=0;j<fcount[i];j++)
		{
			//Still, non terminals are present in the first, so they are just ignored
		if(firsts[i][j]<'A'||firsts[i][j]>'Z')
		{
			if(firsts[i][j]=='$') // epsilon was denoted by $
			printf("e,");
			printf("%c,",firsts[i][j]);
			}
		}
	}
fclose(inm);
fclose(fp);
}



void findFollow(){

FILE *fp,*inm;
char buffer[100];
inm = fopen( "grammer.txt","r");
fp = fopen( "first.txt","w");
if(fp==NULL)
{
  	printf("File could not be opened!\n");
  	exit(0);
}	
if(inm==NULL)
{
  	printf("File could not be opened!\n");
  	exit(0);
}

char follow[10][100];
char fgrams[10];
int focount[10]={0,0,0,0,0,0,0,0,0,0};
int fodcount=0;
fscanf(inm,"%s",buffer);
	
while(!feof(inm))
{
	char rhs[10][10];
	int fc=0;
	char lhs=buffer[0];
	int count=0,ind=0,lrCount=0,aCount=0;
	//RHS found in the same way as of first
	for(int i=3;i<strlen(buffer);i++)
	{
	
		if(buffer[i]=='|')
		{
			rhs[count][ind]='\0';
			count++;
			ind=0;
			
		}
		else
		{
			rhs[count][ind]=buffer[i];
			ind++;
		}
		
	}
	rhs[count][ind]='\0';
	count++;
	fgrams[dcount]=buffer[0];

    // for each grammer
	for(int i=0;i<count;i++)
	{
		// for each character in the grammer
		for(int j=0;j<strlen(rhs[i]);j++)
		{
			// if non terminal
			if(rhs[i][j]>='A'&&rhs[i][j]<='Z')
			{
				//tind: target ind
				//stores the index of non terminal rhs[i][j] in fgrams
				//fodcount : the number of nonterminals in fgrams
			int tind=fodcount; 
			for(int k=0;k<fodcount;k++)
			{
				
				if(fgrams[k]==rhs[i][j])
				{	
					tind=k;
					break;
				}
			}
			// if rhs[i][j] is not present in the fgrams, then add it
			if(tind==fodcount)fodcount++;
			fgrams[tind]=rhs[i][j];

            // finding the next terminal to rhs[i][j] 
			int inc=0;
			repeat:
			if(j+inc<strlen(rhs[i])-1)
			{	
				follow[tind][focount[tind]]=rhs[i][j+inc+1];
				focount[tind]++;
				// if the next character is a terminal, then the below if is skipped
				// else, if its first is '$', then the next character is checked
				if(rhs[i][j+inc+1]>='A' && rhs[i][j+inc+1]<='Z')
				for(int k=0;k<dcount;k++)
				{
					if(grams[k]==rhs[i][j+inc+1])
					for(int m=0;m<fcount[k];m++)
					{
						if(firsts[k][m]=='$')
						{
							inc++;
							goto repeat;
						}
					}
				}
			
			}
			else if(grams[tind]!=buffer[0])
			{

				// if the end of the grammer is reached and not able to find follow, then the non terminal in the LHS is added
				// but it cannot be simply added, because we need to identify it is an lhs
				// so 0-lhs is added, so we are able to identify if is lhs, and also retrieve the value back
				follow[tind][focount[tind]]=0-buffer[0];
				focount[tind]++;
			
			}
			}
		}
		
	}
	

	fscanf(inm,"%s",buffer);
}
for(int i=0;i<fodcount;i++)
	{
		//if start state, then '@' is added to the follow
		if(fgrams[i]==grams[0])
			{follow[i][focount[i]]='@';
			focount[i]++;}
	}

// fodcount: the number of derivations, or the number of non terminals
// focount, the number of follows for a non terminal
for(int i=0;i<fodcount;i++)
	{
		for(int j=0;j<focount[i];j++)
		{  	
			// if the follow needs to be found out through lhs
			if(follow[i][j]<0)
			{
			follow[i][j]=0-follow[i][j];
			        if(follow[i][j]<'A'||follow[i][j]>'Z')
				 continue;
			    // follow[i][j] 's follow should be added to the follow of i
				//finding the index of the follow[i][j] 
				for(int k=0;k<fodcount;k++)
				{
					if(fgrams[k]==follow[i][j])
					{
						//for each character in the follow of follow[i][j]
						for(int m=0;m<focount[k];m++)
						{
							int found=0;
							for(int n=0;n<focount[i];n++)
							{
								if(follow[k][m]==follow[i][n])
								{ //printf("                             Checking %c and %c.,,,,\n",follow[k][m],follow[i][n]);
									found=1;
									break;
								}
							}
							if(!found)
							{
								//if the character is not present in the follow of i, then add it
							follow[i][focount[i]]=follow[k][m];
							focount[i]++;}
						}
					}
					
				}
			}
			
		}
	}
	
	printf("The follow are:");
for(int i=0;i<fodcount;i++)
	{
		printf("\nFOLLOW(%c): ",fgrams[i]);
	
		for(int j=0;j<focount[i];j++)
		{
		if(follow[i][j]<'A'||follow[i][j]>'Z')
			{
				if(follow[i][j]=='@')
					printf("$,");
				else
					printf("%c,",follow[i][j]);
			}
			
		}
	}
	printf("\n");
fclose(inm);
fclose(fp);
}


int main()
{
	printf("FIRST AND FOLLOW\n\n");
	
	printf("\nFinding First...\n\n");
	findFirst();
	printf("\n\nFinding Follow...\n\n");
	findFollow();

}
