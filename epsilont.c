#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE 1024

int stateCount, terminalCount;
char states[SIZE] = {}, terminals[SIZE] = {}, transitions[SIZE][SIZE][10] = {}, isFinal[SIZE] = {};

void epsilon_closure(char, char *);
int is_character_in_string(char *, char);

int main()
{

    printf("Enter no of states:\n");
    scanf("%d", &stateCount);

    printf("Enter states:\n");
    for (int i = 0; i < stateCount; i++)
    {
        while ((getchar()) != '\n')
            ;
        scanf("%c", &states[i]);
    }

    printf("Enter no of terminals: ");
    scanf("%d", &terminalCount);

    printf("Enter terminals:\n");
    for (int i = 0; i < terminalCount; i++)
    {
        while ((getchar()) != '\n')
            ;
        scanf("%c", &terminals[i]);
    }

    printf("Enter transition table\n");
    for (int i = 0; i < terminalCount; i++)
    {
        printf("\t%c", terminals[i]);
    }
    printf("\teps\tfinal (y/n)\n");
    for (int i = 0; i < stateCount; i++)
    {
        printf("%c\t", states[i]);
        for (int j = 0; j < (terminalCount + 1); j++)
        {
            fflush(stdin);
            scanf("%s\t", transitions[i][j]);
        }
        scanf("%c", &isFinal[i]);
    }

    printf("TRANSITION TABLE\n");
    for (int i = 0; i < stateCount; i++)
    {
        for (int j = 0; j < (terminalCount + 1); j++)
        {
            printf("%s\t", transitions[i][j]);
        }
        printf("%c\n", isFinal[i]);
    }
    printf("========================\n");

    printf("CLOSURES\n");
    for (int i = 0; i < stateCount; i++)
    {
        char closure[SIZE] = {};
        epsilon_closure(states[i], closure);
        printf("%c\t%s\n", states[i], closure);
    }
}

int is_character_in_string(char *str, char ch)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ch)
        {
            return 1;
        }
    }
    return 0;
}

void epsilon_closure(char ch, char *closure)
{
    int i;
    for (i = 0; i < stateCount; i++)
    {
        if (states[i] == ch)
        {
            break;
        }
    }

    if (!is_character_in_string(closure, ch))
    {
        strncat(closure, &ch, 1);
    }
    int f = 0;
    for (int j = 0; j < strlen(transitions[i][terminalCount]); j++)
    {
        char x = transitions[i][terminalCount][j];
        if (!is_character_in_string(closure, x) && x != '-')
        {
            f = 1;
            strncat(closure, &x, 1);
        }
    }
    if (f == 0)
    {
        return;
    }
    while (1)
    {
        char temp[SIZE] = {};
        strcpy(temp, closure);
        for (int j = 0; j < strlen(temp); j++)
        {
            epsilon_closure(temp[j], closure);
        }
        if (strlen(temp) == strlen(closure))
        {
            break;
        }
    }
}