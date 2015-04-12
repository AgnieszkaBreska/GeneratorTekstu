#include "czytaj.h"
#define IN 1
#define OUT 0
#define TAK 1
#define NIE 0

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

            printf("%s",wektor[k].tabgram[j]);
            printf(" ");
        }   
        printf("]\t\t ");
        for(i = 0; i < wektor[k].i; i++)
            printf("[%s]",wektor[k].tabslowa[i]);
        printf("\n");
    }   
    printf ("ilość  =  %d \n", licznik_struktur);
}

void read_file (int n,FILE* plik[30],int s, int iloscslow){

    int lw,i,j,a;

    lw = iloscslow - n;

    struct gram *wektor = malloc(lw*sizeof(struct gram));

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
            wektor[licznik_struktur].i = 1;
            ++licznik_struktur;     
            if(i == 0){
                -- licznik_struktur; 
            }
            if(c == EOF){
                break;
            }
        }
    }
    /*sprawdzanie powtorzen i tworzenie wektora wynikowego */
    struct gram *wektor_wynikowy = malloc(lw*sizeof(struct gram));
    if(!wektor_wynikowy)
        printf("nie ma pamieci!\n");
    int powtorzenie,k;
    int licznik_struktur_wynikowy = 1;
    for(j = 0; j < n; j++){
        for( i = 0; i < MAXLITER; i++)
            wektor_wynikowy[0].tabgram[j][i] = wektor[0].tabgram[j][i];
    }
    for( i = 0; i < MAXLITER; i++)
        wektor_wynikowy[0].tabslowa[0][i] = wektor[0].tabslowa[0][i];
    wektor_wynikowy[0].i = 1;

    for (k = 1; k < licznik_struktur; k++){
        for(a = 0; a < licznik_struktur_wynikowy; a++){
            powtorzenie = TAK;
            for(j = 0; j < n; j++){
                if(strcmp(wektor_wynikowy[a].tabgram[j],wektor[k].tabgram[j]) != 0){
                    powtorzenie = NIE;
                    break;
                }
            }
            if(powtorzenie == TAK)
                break;
        }

        if(powtorzenie == TAK){
            for(i = 0; i < MAXLITER; i++)
                wektor_wynikowy[a].tabslowa[wektor_wynikowy[a].i][i] = wektor[k].tabslowa[0][i];
            ++wektor_wynikowy[a].i;
        }

        if(powtorzenie == NIE){
            for(j = 0; j < n; j++){
                for(i = 0; i < MAXLITER; i++)
                    wektor_wynikowy[licznik_struktur_wynikowy].tabgram[j][i] = wektor[k].tabgram[j][i];
            }
            for(i = 0; i < MAXLITER; i++)
                wektor_wynikowy[licznik_struktur_wynikowy].tabslowa[0][i] = wektor[k].tabslowa[0][i];
            wektor_wynikowy[licznik_struktur_wynikowy].i = 1;
            ++licznik_struktur_wynikowy;
        }
    }    

  /*  wypisz(wektor,n,licznik_struktur);*/
    wypisz(wektor_wynikowy,n,licznik_struktur_wynikowy);
}
