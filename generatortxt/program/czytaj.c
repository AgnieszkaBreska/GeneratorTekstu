#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

void wypisz(struct gram wektor[20], int n, int m){

    int k,j,i;

    for (k = 0; k < m; k++){
        printf("[ ");
        for (j = 0; j < n; j++){
            for (i = 0 ; wektor[k].tabgram[j][i] != '\0'; i++){
                printf("%c",wektor[k].tabgram[j][i]);
            }
            printf(" ");
        }   
        printf("]\t\t ");
        printf("[ ");
        for (i = 0 ; wektor[k].tabslowa[0][i] != '\0'; i++){ 
            printf("%c",wektor[k].tabslowa[0][i]);
        }   

        printf("]\n");
    }   
    licznik = k;
    printf ("ilość  =  %d \n", licznik);
}
/*
int sprawdz(struct gram wektor[20],int n){

    int k,j,i;
    char tmpwekt[n][MAXLITER];

    for(k = 1; k < 20; k++){
        for (j = 0; j < (n-1); j+=){
            for (i = 0; i < MAXLITER; i++){
                tmpwekt[j][i] = wektor[k-1].tabgram[j+1][i];
            }
        }
        for(i = 0; i < MAXLITER; i++)
            tmp[n-1][i] = wektor[k-1].tabslowa[0][i];

    }
}
*/

void read_file (int n,FILE* in){

int k = 20;
    struct gram wektor[k];

    char c;

    int m,i,j;
    /*odczytanie pierwszej struktury */
    for (j = 0; j < n; j++){
        for (i = 0; i < MAXLITER; i++){
            c = getc(in);
            if(c == ' ' || c == '\n'|| c == EOF)
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

    /*zapisywanie n wyrazów do tymczasowego wektora*/
/*
    if(sprawdz(wektor,n) == 0){
   
    }else{
    
    }

    
       for(k = 1; k < 20; k++){
       for (j = 0; j < (n-1); j+=){
       for (i = 0; i < MAXLITER; i++){
       tmpwekt[j][i] = wektor[k-1].tabgram[j+1][i];
       }
       }
       for(i = 0; i < MAXLITER; i++)
       tmp[n-1][i] = wektor[k-1].tabslowa[0][i];

       }

   */ 
    /*odczytywanie kolejnych struktur*
     */
      for(m = 1; m < k ; m++){
     for(j = 0; j < (n-1); j++){
     for(i = 0; i < MAXLITER; i++){
     wektor[m].tabgram[j][i] = wektor[m-1].tabgram[j+1][i];
     }
     }
     for( i = 0; i < MAXLITER; i++)
     wektor[m].tabgram[n-1][i] = wektor[m-1].tabslowa[0][i]; 

     for (i = 0; i < MAXLITER; i++){
     c = getc(in);
     if(c == ' ' || c == '\n' || c == EOF)
     break; 
     wektor[m].tabslowa[0][i] = c;
     }
     wektor[m].tabslowa[0][i] = '\0';

     }
    wypisz(wektor,n,k);
}
