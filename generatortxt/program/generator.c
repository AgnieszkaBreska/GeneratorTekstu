#include "generator.h"
int generuj(struct gram wektor[],int licznik,int n, int w){

    FILE *out = fopen("../wynik/tekst.txt", "w");
    
    if (out == NULL){
        fprintf(stdout,"nie można pisać do pliku");
        return 1;
    }

    srand(time(NULL));
    int i,j,k,l;
    int pierwszy_n_gram;
    int slowo;
    pierwszy_n_gram = rand()%licznik;
    int flaga;
    i = n+1;
    /*fprintf(stdout,"nr pierwszego n-gramu = %d\n",pierwszy_n_gram);*/

    for(j = 0; j < n; j++){
        fprintf(out,"%s ",wektor[pierwszy_n_gram].tabgram[j]);
    }
        slowo = rand()%(wektor[pierwszy_n_gram].i);
        fprintf(out,"%s ", wektor[pierwszy_n_gram].tabslowa[slowo]);

    for(k = (n + 1); k < w; k++){
        for(l = 0; l < licznik; l++){
            flaga = 1;
            for(j = 0; j < (n-1); j++){
                if(strcmp(wektor[pierwszy_n_gram].tabgram[j+1],wektor[l].tabgram[j])!= NIE){
                    flaga = NIE;
                    break;
                }
            }
            if(flaga == TAK && strcmp(wektor[pierwszy_n_gram].tabslowa[slowo],wektor[l].tabgram[n-1]) == NIE){
                slowo = rand()%(wektor[l].i);
                fprintf(out,"%s ",wektor[l].tabslowa[slowo]);
                pierwszy_n_gram = l;
                ++i;
                break;
            }
        }
        if((k% 25) == 0)
            fprintf(out,"\n");
        if((k % 100) == 0)
            fprintf(out,"\t");
    }
    /*printf("\n liczba wyrazów: %d\n",i);*/
    fclose(out);
    printf("Udało się wygenerować tekst wyjściowy!\n");
    if(staty_wyjscia(i) != 0)
        return 1;
    return 0;
}
