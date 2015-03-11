#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    int n = 2;
    int a = 3;
    int w = 100;
    int i, tmp;

    if (argc == 1){
        fprintf( stderr, "%s: błąd: proszę podać tekst do przetworzenia ( -t plik1.txt plik2.txt ...)\n", argv[0] ); 
        return EXIT_FAILURE;
    }
    /* sprawdzanie flag*/

    for(i = 1; i < argc; i++){
        if (strcmp( argv[i], "-t") == 0){
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
        else if (strcmp( argv[i], "-n") == 0){
            if(i+1 < argc && strcmp(argv[i+1],"-w") != 0 && strcmp(argv[i+1],"-a") != 0 && strcmp(argv[i+1],"-t") != 0){
                if (atoi(argv[i+1]) != 0)
                    n = atoi (argv[i+1]);
            } 
        }
        else if (strcmp( argv[i], "-w") == 0){
            if(i+1 < argc && strcmp(argv[i+1],"-n") != 0 && strcmp(argv[i+1],"-a") != 0 && strcmp(argv[i+1],"-t") != 0){
                if (atoi(argv[i+1]) != 0)
                    w = atoi (argv[i+1]);
            }
        } 
        else if (strcmp( argv[i], "-a") == 0){
            if(i+1 < argc && strcmp(argv[i+1],"-n") != 0 && strcmp(argv[i+1],"-w") != 0 && strcmp(argv[i+1],"-t") != 0){
                if (atoi(argv[i+1]) != 0)
                    a = atoi (argv[i+1]);

            } 
        }
    }
    int liczba_slow_w_akapicie;
    if(w/a == 0){
        a = 1;
        liczba_slow_w_akapicie = w;
    }
    else
        liczba_slow_w_akapicie = w/a;
    printf("%d - liczba słów w akapicie\n", liczba_slow_w_akapicie);
    printf("%d - gramy\n", n);
    printf("%d - ilość wyrazów\n", w);
    printf("%d - ilość akapitów\n", a);
    return 0;
}
