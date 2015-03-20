#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    int n_gram = 2;
    int akapit = 1;
    int wyrazy = 200;
    int i, tmp;
    int flaga_a = 0;
    int flaga_w = 0;
    int flaga_t = 0;
    int flaga_n = 0;

    if (argc == 1){
        fprintf( stderr, "%s: błąd: proszę podać tekst do przetworzenia ( -t plik1.txt plik2.txt ...)\n", argv[0] ); 
        return EXIT_FAILURE;
    }
    
    /* sprawdzanie flag -t */

    for(i = 1; i < argc; i++){
        if (strcmp( argv[i], "-t") == 0 && flaga_t ==0){
            flaga_t = 1;
            for( tmp = i + 1; tmp < argc; tmp++){
                if(strcmp(argv[tmp], "-n") == 0 || strcmp(argv[tmp],"-w") == 0 || strcmp(argv[tmp],"-a") == 0){
                    break;
                }
                /*odczyt plików*/
                /*   FILE*in = fopen(argv[tmp], "r");
                     if (in == NULL){
                     printf("Nie mozna otworzyc %s\n", argv[tmp]);
                     return 1;

                     }
                     else{
                     read_file(in);
                     }*/
                fprintf(stdout,"%s - plik\n",argv[tmp]);
            }
        }
         /* sprawdzanie flag -n */  
        else if (strcmp( argv[i], "-n") == 0){
            if(i+1 < argc && strcmp(argv[i+1],"-w") != 0 && strcmp(argv[i+1],"-a") != 0 && strcmp(argv[i+1],"-t") != 0){
                if (atoi(argv[i+1]) > 0 && flaga_n == 0){
                    n_gram = atoi (argv[i+1]);
                    flaga_n = 1;
                }
            } 
        }
         /* sprawdzanie flag -w */  
        else if (strcmp( argv[i], "-w") == 0){
            if(i+1 < argc && strcmp(argv[i+1],"-n") != 0 && strcmp(argv[i+1],"-a") != 0 && strcmp(argv[i+1],"-t") != 0){
                if (atoi(argv[i+1]) > 0 && flaga_a == 0){
                    wyrazy = atoi (argv[i+1]);
                    flaga_w = 1;
                }
            }
        }
        /* sprawdzanie flag -a */   
        else if (strcmp( argv[i], "-a") == 0){
            if(i+1 < argc && strcmp(argv[i+1],"-n") != 0 && strcmp(argv[i+1],"-w") != 0 && strcmp(argv[i+1],"-t") != 0){
                if (atoi(argv[i+1]) > 0 && flaga_w == 0){
                    akapit = atoi (argv[i+1]);
                    flaga_a = 1;
                    wyrazy = akapit*200;
                }
            } 
        }
    }

    printf("%d - gramy\n", n_gram);
    printf("%d - ilość wyrazów\n", wyrazy);
    printf("%d - ilość akapitów\n", akapit);
    return 0;
}
