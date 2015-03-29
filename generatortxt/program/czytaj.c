#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

void read_file (int n,FILE* in){

    
    struct gram wektor[20];
    
    char c;

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
    for(k = 1; k < 20 ; k++){
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

    for (k = 0; k < 20; k++){
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
    licznik = k;
    printf ("ilość  =  %d \n", licznik);
}

