#include "staty.h"

int staty_wejscia(struct gram wektor[],int licznik,struct gram wektor_wynikowy[],int licznikwynikowy,int n){

    int i,j,k,MAX,b;
    double pw;
    FILE *outt = fopen("../wynik/staty_wejscia.txt", "w");
    if (outt == NULL){
        printf("nie można pisać do pliku staty_wejścia.txt\n");
        return 1;
    }
    
    fprintf(outt,"Ilość wydenerowanych n-gramów: %d\nIlość słów w tekście wejściowym: %d\n",licznikwynikowy,licznik+n-1);

    /*najczesciej powtarzające się n-gramy*/
    
    fprintf(outt,"\nNajczęściej powtarzające się n-gramy\n\n");
    for(k = 0; k < 10; k++){
        MAX = 0;
        for(j = 0; j < licznikwynikowy; j++){
            if(MAX < wektor_wynikowy[j].i){
                MAX = wektor_wynikowy[j].i;
                b = j;
            }
        }
        if(wektor_wynikowy[b].i == 0)
            break;
        pw = ((double)wektor_wynikowy[b].i)/((double)licznikwynikowy);
        fprintf(outt,"%2d. [",k+1);
        for(i = 0; i < n; i++){
            fprintf(outt,"%s ",wektor_wynikowy[b].tabgram[i]);
        }
        fprintf(outt,"] - ilość wystąpień: %-3d, prawdopodobieńśtwo wystąpienia w tekście: %f]\n",wektor_wynikowy[b].i,pw);
        wektor_wynikowy[b].i = 0;
    }

    printf("Udało się wygenerować statystyki dla pliku wejsciowego\n\n");


    fclose(outt);
    return 0;
}


int staty_wyjscia(int wyrazy){

    int a, b, i, j, k, flaga, MAX;
    i = 1;
    char c;
    char buff[30];
    double pw;
    FILE *plik = fopen("../wynik/tekst.txt","r");
    FILE *outt = fopen("../wynik/staty_wyjscia.txt","w");

    if (plik == NULL){
        printf("nie można czytac pliku tekst.txt\n");
        return 1;
    }
    if (outt == NULL){
        printf("nie można pisać do pliku staty_wyjscia.txt\n");
        return 1;
    }

    struct statystyki{
        int i;
        char slowo[30];
    };
    struct statystyki *tablica = malloc(wyrazy*sizeof(struct statystyki));

    if (tablica == NULL){
        printf("nie udało się zaalokować pamięci do statystyk\n");
        return 1;
    }

    fprintf(outt,"Wyrazy w tekscie wyjściowym: %d\n",wyrazy);

    for(a = 0; a < 30; a++){
        if((c = getc(plik)) == ' ' || c == '\n' || c == EOF || c == '\t'){
            tablica[0].slowo[a] = '\0';
            break;
        }
        else
            tablica[0].slowo[a] = c;
        tablica[0].i = 1;
    }

    for(k = 1; k < wyrazy; k++){
        flaga = 0;
        for(a = 0; a < 30; a++){
            if((c = getc(plik)) == ' ' || c == '\n' || c == EOF || c == '\t'){
                buff[a] = '\0';
                break;
            }
            else
                buff[a] = c;
        }

        for(j = 0; j < i; j++){
            if(strcmp(buff,tablica[j].slowo) == 0){
                ++tablica[j].i;
                flaga = 1;
                break;
            }
        }
        if(flaga == 0 && a > 0){
            strcpy(tablica[i].slowo,buff);
            tablica[i].i = 1;
            ++i;
        }
    }

    for(k = 0; k < 10; k++){
        MAX = 0;
        for(j = 0; j < i; j++){
            if(MAX < tablica[j].i){
                MAX = tablica[j].i;
                b = j;
            }
        }
        if(tablica[b].i == 0)
            break;
        pw = ((double)tablica[b].i)/((double)wyrazy);
        fprintf(outt,"%2d. [%-15s - ilość wystąpień: %-4d, prawdopodobieńśtwo wystąpienia w tekście: %f]\n",k+1,tablica[b].slowo,tablica[b].i,pw);
        tablica[b].i = 0;
    }

    printf("Udało się wygenerować statystyki dla pliku wyjściowego\n");
    free(tablica);
    fclose(plik);
    fclose(outt);
    return 0;
}
