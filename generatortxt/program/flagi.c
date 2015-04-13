#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "czytaj.h"

int main(int argc, char* argv[]){

    int n_gram = 2;
    int akapit = 1;
    int wyrazy = 10;
    int i, tmp;
    int flaga_a = 0;
    int flaga_w = 0;
    int flaga_t = 0;
    int flaga_n = 0;

    if (argc == 1){
        fprintf( stderr, "%s: błąd: proszę podać tekst do przetworzenia ( -t plik1.txt plik2.txt ...)\n", argv[0] ); 
        return EXIT_FAILURE;
    }


    for(i = 1; i < argc; i++){

        /* sprawdzanie flag -n */  
        if (strcmp( argv[i], "-n") == 0){
            if(i+1 < argc && strcmp(argv[i+1],"-w") != 0 && strcmp(argv[i+1],"-a") != 0 && strcmp(argv[i+1],"-t") != 0){
                if (atoi(argv[i+1]) > 0 && flaga_n == 0 && atoi(argv[i+1]) <= 10){
                    n_gram = atoi (argv[i+1]);
                    flaga_n = 1;
                }
                else{
                    fprintf( stderr, "%s: błąd! Proszą podać właściwą liczbę n-gramów (0<n<11)\n", argv[0]);
                    return EXIT_FAILURE;
                }
            }
        }
        /* sprawdzanie flag -w */  
        else if (strcmp( argv[i], "-w") == 0){
            if(i+1 < argc && strcmp(argv[i+1],"-n") != 0 && strcmp(argv[i+1],"-a") != 0 && strcmp(argv[i+1],"-t") != 0){
                if (atoi(argv[i+1]) > 0 && flaga_a == 0){
                    wyrazy = atoi (argv[i+1]);
                    flaga_w = 1;
                    if(wyrazy%100 == 0){
                        akapit = wyrazy/100;
                    }
                    else
                        akapit = wyrazy/100 +1;
                }
                else if(atoi(argv[i+1]) <= 0){
                    fprintf( stderr, "%s: błąd! Proszą podać właściwą liczbę wyrazów\n", argv[0]);
                    return EXIT_FAILURE;
                }  
                else{
                    fprintf( stderr, "%s: błąd! Została już podana ilość akapitów!(w = a*100)\n", argv[0]);
                    return EXIT_FAILURE;
                }
            }
        }
        /* sprawdzanie flag -a */   
        else if (strcmp( argv[i], "-a") == 0){
            if(i+1 < argc && strcmp(argv[i+1],"-n") != 0 && strcmp(argv[i+1],"-w") != 0 && strcmp(argv[i+1],"-t") != 0){
                if (atoi(argv[i+1]) > 0 && flaga_w == 0){
                    akapit = atoi (argv[i+1]);
                    flaga_a = 1;
                    wyrazy = akapit*100;
                }
                else if(atoi(argv[i+1]) <= 0){
                    fprintf( stderr, "%s: błąd! Proszą podać właściwą liczbę akapitów\n", argv[0]);
                    return EXIT_FAILURE;
                }  
                else{
                    akapit = wyrazy/100;
                }
            } 
        }
    }

    FILE *wektorplikow[30];
    int s = 0;
    char *sciezka = "../dane/";
    char buf[100];
    strcpy(buf,sciezka);
    int d = 8;
    /* sprawdzanie flag -t */
    for(i = 1; i < argc; i++){ 
        if (strcmp( argv[i], "-t") == 0 && flaga_t ==0){
            flaga_t = 1;
            for( tmp = i + 1; tmp < argc; tmp++){
                if(strcmp(argv[tmp], "-n") == 0 || strcmp(argv[tmp],"-w") == 0 || strcmp(argv[tmp],"-a") == 0){
                    break;
                }else{
                    /*odczyt plików*/
                    for(d = 8; d < 100; d++){
                        buf[d] = argv[tmp][d-8];
                    }
                    wektorplikow[s] = fopen(buf, "r");
                    if (wektorplikow[s] == NULL){
                        printf("Nie mozna otworzyc %s\n", argv[tmp]);
                        return 1;
                    }
                }
                s++;
            }
        }
    }

    int iloscslow;
    iloscslow = sprawdz(wektorplikow,s);
   /* printf("liosc slow w tekstach = %d\n" ,iloscslow);*/
    if(iloscslow < wyrazy){
        printf("Zbyt mała ilość słów w tekstach bazowych (ilość slów < liczba wyrazów do wygenerowania)\n");
        return 1;
    }
    if(iloscslow <= n_gram){
        printf("Zbyt mała ilość słów w tekstach bazowych (slość słów < n-gram)\n");
        return 1;
    }
    if(read_file(n_gram,wektorplikow,s,iloscslow,wyrazy) != 0){
        return 1;
    }
    
    for(d = 0; d < s; d++)
       fclose(wektorplikow[d]);
    return 0;
}
