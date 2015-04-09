#include "czytaj.h"
#define IN 1
#define OUT 0

int sprawdz(FILE *plik[30], int s){
    int i, lw, c;
    lw = 0;
    int stan;

    for ( i = 0; i < s; i++){
        stan = OUT;
        while((c = getc(plik[i])) != EOF){
            if( c == ' '|| c == '\n' || c == '\t')
                stan = OUT;
            else if (stan == OUT){
                stan = IN;
                ++lw;
            }
        }
        rewind(plik[i]);
    }
    return lw;
}



void wypisz(struct gram wektor[], int n, int licznik_struktur){

    int k,j,i;

    for (k = 0; k < licznik_struktur; k++){
        printf("[ ");
        for (j = 0; j < n; j++){
            for (i = 0 ; wektor[k].tabgram[j][i] != '\0'; i++){
                printf("%c",wektor[k].tabgram[j][i]);
            }
            printf(" ");
        }   
        printf("]\t\t ");
        printf("[");
        for (i = 0 ; wektor[k].tabslowa[0][i] != '\0'; i++){ 
            printf("%c",wektor[k].tabslowa[0][i]);
        }   

        printf("]\n");
    }   
    printf ("ilość  =  %d \n", licznik_struktur);
}

void read_file (int n,FILE* plik[30],int s, int iloscslow){

    int lw,i,j,a;

    lw = iloscslow - n;

    struct gram wektor[lw];

    int licznik_struktur = 0;
    char c;

    for(a = 0; a < s; a++){
        /*odczytanie pierwszego n-garmu z pliku*/
        for (j = 0; j < n; j++){
            for (i = 0; i < MAXLITER; i++){
                c = getc(plik[a]);
                if(c == ' ' || c == '\n' || c == '\t')
                    break; 
                wektor[licznik_struktur].tabgram[j][i] = c;
            }
            wektor[licznik_struktur].tabgram[j][i] = '\0';
        }

        for (i = 0; i < MAXLITER; i++){
            c = getc(plik[a]);
            if(c == ' ' || c == '\n' ||c == EOF || c == '\t')
                break; 
            wektor[licznik_struktur].tabslowa[0][i] = c;
        }
        wektor[licznik_struktur].tabslowa[0][i] = '\0';
        wektor[licznik_struktur].i = 1;
        ++licznik_struktur;
        /*odczytywanie kolejnych n-gramów*/
        while( licznik_struktur < lw){
            for(j = 0; j < (n-1); j++){
                for(i = 0; i < MAXLITER; i++){
                    wektor[licznik_struktur].tabgram[j][i] = wektor[licznik_struktur - 1].tabgram[j+1][i];
                }
            }
            for( i = 0; i < MAXLITER; i++)
                wektor[licznik_struktur].tabgram[n-1][i] = wektor[licznik_struktur-1].tabslowa[0][i]; 

            for (i = 0; i < MAXLITER; i++){
                c = getc(plik[a]);
                if(c == ' ' || c == '\n' || c == EOF || c == '\t')
                    break; 
                wektor[licznik_struktur].tabslowa[0][i] = c;
            }
            wektor[licznik_struktur].tabslowa[0][i] = '\0';
            ++licznik_struktur;     
            if(i == 0){
                -- licznik_struktur;
                break; 
            }
            if(c == EOF){
                break;
            }
        }
    }
    wypisz(wektor,n,licznik_struktur);
}
