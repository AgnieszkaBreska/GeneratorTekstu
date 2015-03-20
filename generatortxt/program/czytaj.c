#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLITER 20
int main (int argc, char** argv){

    int n = 3;
    struct gram{
        char tabgram[n][MAXLITER]; 
        char tabslowa[5][MAXLITER];
    };
    struct gram wektor[10];

    char c;

    FILE *in = argc > 1 ? fopen (argv[1], "r" ) : stdin;

    int k,i,j;
    /*odczytanie pierwszej struktury */
    for (j = 0; j < n; j++){
        for (i = 0; i < MAXLITER; i++){
            c = getc(in);
            if(c == ' ' || c == '\n')
                break; 
            wektor[0].tabgram[j][i] = c;
        }
        wektor[0].tabgram[j][i] = '\0';
    }

    for (i = 0; i < MAXLITER; i++){
        c = getc(in);
        if(c == ' ' || c == '\n')
            break; 
        wektor[0].tabslowa[0][i] = c;
    }
    wektor[0].tabslowa[0][i] = '\0';

    /*odczytywanie kolejnych struktur*/
    for(k = 1; k < 10 ; k++){
        for(j = 0; j < (n-1); j++){
            for(i = 0; i < MAXLITER; i++){
                wektor[k].tabgram[j][i] = wektor[k-1].tabgram[j+1][i];
            }
        }
        for( i = 0; i < MAXLITER; i++)
            wektor[k].tabgram[n-1][i] = wektor[k-1].tabslowa[0][i]; 

        for (i = 0; i < MAXLITER; i++){
            c = getc(in);
            if(c == ' ' || c == '\n')
                break; 
            wektor[k].tabslowa[0][i] = c;
        }
        wektor[k].tabslowa[0][i] = '\0';

    }

    for (k = 0; k < 10; k++){
        printf("[ ");
        for (j = 0; j < n; j++){
            for (i = 0 ; wektor[k].tabgram[j][i] != '\0'; i++){
                printf("%c",wektor[k].tabgram[j][i]);
            }
            printf(" ");
        }
        for (i = 0 ; wektor[k].tabslowa[0][i] != '\0'; i++){ 
            printf("%c",wektor[k].tabslowa[0][i]);
        }

        printf("]\n");
    }
    return 0;
}

