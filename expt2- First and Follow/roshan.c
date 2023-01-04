#include <stdio.h>
#include <string.h>

#define SIZE 1024

int remove_lr();
void find_first(char, char*);
void find_follow(char, char*);

char productions[20][SIZE] = {};
int prodCount = 0;

int main() {
    FILE *fp = fopen("input.txt", "r");
    char llnont = 'Z';

    while(1) {
        char prod[SIZE] = {}, alpha[SIZE] = {}, beta[SIZE] = {}, nont;
        fgets(prod, SIZE, fp);
        if(feof(fp)) break;
        prod[strcspn(prod, "\n")] = '\0';
        int hasLR = remove_lr(prod, alpha, beta, &nont);
        if(hasLR) {
            char buffer[2*SIZE] = {};
            sprintf(buffer, "%c=%s%c", nont, beta, llnont);
            strcpy(productions[prodCount++], buffer);

            sprintf(buffer, "%c=%s%c", llnont, alpha, llnont);
            strcpy(productions[prodCount++], buffer);

            sprintf(buffer, "%c=#", llnont);
            strcpy(productions[prodCount++], buffer);

            llnont--;
        }
        else {
            char buffer[2*SIZE] = {};

            if(strlen(alpha) != 0) {
                sprintf(buffer, "%c=%s", nont, alpha);
                strcpy(productions[prodCount++], buffer);
            }

            if(strlen(beta) != 0) {
                sprintf(buffer, "%c=%s", nont, beta);
                strcpy(productions[prodCount++], buffer);
            }
        }
    }
    printf("==============\n");


    printf("PROD WITHOUT LR\n");
    char nont[20] = {};
    for(int i=0; i<prodCount; i++) {
        printf("%s\n", productions[i]);
        int f = 1;
        for(int j=0; j<strlen(nont); j++) {
            if(nont[j] == productions[i][0]) 
                f = 0;
        }
        if(f == 1) {
            strncat(nont, &productions[i][0], 1);
        }
    }
    printf("==============\n");
    

    printf("FINDING FIRST\n");
    for(int i=0; i<strlen(nont); i++) {
        char firstOfVariable[100] = {};
        find_first(nont[i], firstOfVariable);

        // PRINTING FIRSTS
        printf("%c = { ", nont[i]);
        int temp[127] = {0};
        for(int j=0; j<strlen(firstOfVariable); j++) {
            if(temp[firstOfVariable[j]] == 0) {
                printf("%c, ", firstOfVariable[j]);
                temp[firstOfVariable[j]] = 1;
            }
        }
        printf("}\n");
    }
    printf("==============\n");
    

    printf("FINDING FOLLOW\n");
    for(int i=0; i<strlen(nont); i++) {
        char followOfVariable[100] = {};
        find_follow(nont[i], followOfVariable);

        // PRINTING FOLLOWS
        printf("%c = { ", nont[i]);
        int temp[127] = {0};
        for(int j=0; j<strlen(followOfVariable); j++) {
            if(temp[followOfVariable[j]] == 0) {
                printf("%c, ", followOfVariable[j]);
                temp[followOfVariable[j]] = 1;
            }
        }
        printf("}\n");
    }
}

int remove_lr(char *prod, char *alpha, char *beta, char *nont) {
    int i=2;
    int hasLR = 0;
    *nont = prod[0];
    printf("prod: %s\n", prod);
    if(prod[0] == prod[2]) {
        i++;
        hasLR = 1;
    }
    int f = 0;
    while(i < strlen(prod)){
        if(prod[i] == '|') {
            f = 1;
        }
        else {
            if(f == 0) {
                strncat(alpha, &prod[i], 1);
            }else {
                strncat(beta, &prod[i], 1);
            }
        }
        i++;
    }
    return hasLR;
}

void find_first(char ch, char *firstArray) {
    if(!(ch >= 'A' && ch <= 'Z')) {
        strncat(firstArray, &ch, 1);
    }
    int i=0;
    while(i<prodCount) {
        if(productions[i][0] == ch) {
            if(!(productions[i][2] >= 'A' && productions[i][2] <= 'Z')) {
                strncat(firstArray, &productions[i][2], 1);
            }else {
                find_first(productions[i][2], firstArray);
            }
        }
        i++;
    }
}

void find_follow(char ch, char *followArray) {
    // printf("%c", ch);
    if(ch == productions[0][0]) {
        char x = '$';
        strncat(followArray, &x, 1);
    }
    int i=0;
    while(i < prodCount) {
        for(int j=2; j<strlen(productions[i]); j++) {
            if(productions[i][j] == ch && productions[i][0] != ch) {
                // printf("yes");
                if(strlen(productions[i]) - 1 == j) {
                    find_follow(productions[i][0], followArray);
                }
                else {
                    char firstArray[100] = {};
                    find_first(productions[i][j+1], firstArray);
                    for(int k=0; k<strlen(firstArray); k++) {
                        if(firstArray[k] == '#') {
                            find_follow(productions[i][0], followArray);
                        }
                        else {
                            strncat(followArray, &firstArray[k], 1);
                        }
                    }
                }
            }
        }
        i++;
    }
}


/*
INPUT

E=E+T|T
T=T*F|F
F=(E)|i
*/