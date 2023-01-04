#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char stack[100], p[100];

int top = -1, tp = -1;

void push(char x)
{
    stack[++top] = x;
}

char pop()
{
    if (top == -1)
        return -1;
    else
        return stack[top--];
}

int priority(char x)
{
    if (x == '=')
        return 0;
    if (x == '(')
        return 1;
    if (x == '+' || x == '-')
        return 2;
    if (x == '*' || x == '/')
        return 3;
    return 0;
}

int post()
{
    char exp[100];
    char *e, x;
    printf("Enter the expression : ");
    scanf("%s", exp);
    printf("Infix Expression : %s\n", exp);
    e = exp;

    while (*e != '\0')
    {
        if (isalnum(*e))
            p[++tp] = *e;
        else if (*e == '=')
            push(*e);
        else if (*e == '(')
            push(*e);
        else if (*e == ')')
        {
            while ((x = pop()) != '(')
                p[++tp] = x;
        }
        else
        {
            while (priority(stack[top]) >= priority(*e))
                p[++tp] = pop();
            push(*e);
        }
        e++;
    }

    while (top != -1)
    {
        p[++tp] = pop();
    }
    p[++tp] = '\0';
    return 0;
}

void main()
{
    post();
    printf("Postfix Expression : %s", p);
    char t[10][10];
    int b = -1;
    int i = 0;

    while (p[i] != '\0')
    {
        if (priority(p[i]) > 0)
        {
            // printf("operator");
            t[++b][2] = p[i];
            p[i] = '0';
            t[b][1] = p[--i];
            p[i] = '0';
            t[b][0] = p[--i];
            t[b][3] = '\0';
            int c = b + 1;
            p[i] = c + '0';
            // strcpy(stack,'\0');
            // printf("%s\n",p);
            for (int j = 0, k = 0; j <= tp; j++)
            {
                if (p[j] != '0')
                {
                    // printf("copy");
                    stack[k] = p[j];
                    k++;
                }
            }

            strcpy(p, stack);
            i = 0;
            tp = strlen(p);
            // printf("%s\n",p);
        }
        i++;
    }
    printf("\nQuadriple Table\n");
    printf("\nStatement\toperand1\toperand2\toperator\tResult\n");
    for (int i = 0; i <= b; i++)
    {
        printf("\n%d\t\t", i + 1);
        if (isdigit(t[i][0]) > 0)
            printf("t%c\t\t", t[i][0]);
        else
            printf("%c\t\t", t[i][0]);
        if (isdigit(t[i][1]) > 0)
            printf("t%c\t\t", t[i][1]);
        else
            printf("%c\t\t", t[i][1]);

        printf("%c\t\t", t[i][2]);
        printf("t%d\n", i + 1);
    }
    // printf("%d\t\tt%c\t\t-\t\t=\t\t%c\n",b+2,p[1],p[0]);

    printf("\nTriple Table\n");
    printf("\nStatement\toperand1\toperand2\toperator\n");
    for (int i = 0; i <= b; i++)
    {
        printf("\n%d\t\t", i + 1);
        printf("%c\t\t", t[i][0]);
        printf("%c\t\t", t[i][1]);

        printf("%c\t\n", t[i][2]);
    }
}
