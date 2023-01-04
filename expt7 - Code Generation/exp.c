#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	FILE *fp, *fp2;
	char c[20], opr[5];
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	char reg[4][10] = {"AX", "BX", "CX", "DX"};
	char res[4];
	int j = 0;
	fscanf(fp, "%s", c);
	while (!feof(fp))
	{
		res[j] = c[3];
		switch (c[0])
		{
		case '+':
			strcpy(opr, "ADD ");
			break;
		case '-':
			strcpy(opr, "SUB ");
			break;
		case '*':
			strcpy(opr, "MUL ");
			break;
		case '/':
			strcpy(opr, "DIV ");
			break;
		}
		int flag1 = -1, flag2 = -1;
		for (int i = 0; i < 4; i++)
		{
			if (res[i] == c[1])
				flag1 = i;
			if (res[i] == c[2])
				flag2 = i;
		}
		if (flag1 == -1)
			fprintf(fp2, "\n\tMOV %s,%c", reg[j], c[1]);
		else
			fprintf(fp2, "\n\tMOV %s,%s", reg[j], reg[flag1]);
		if (flag2 == -1)
			fprintf(fp2, "\n\t%s%s,%c", opr, reg[j], c[2]);
		else
			fprintf(fp2, "\n\t%s%s,%s", opr, reg[j], reg[flag2]);
		fprintf(fp2, "\n\tMOV %c,%s", c[3], reg[j]);
		j++;
		fscanf(fp, "%s", c);
	}
}
