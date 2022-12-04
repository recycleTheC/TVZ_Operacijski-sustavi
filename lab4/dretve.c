#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int zbroj = 0;

void* funkcija(void* i) {
    zbroj++;
    return 0;
}

int main(int argc, char* argv[]) {

    int broj_dretvi = 0;

    if(argc != 2) {
        printf("Neispravan poziv naredbe!\nZavrsavam s radom!\n");
        exit(1);
    }

    if(sscanf(argv[1], "%d", &broj_dretvi) != 1) {
        printf("Nije unesen ispravan broj procesa!\nZavrsavam s radom!\n");
        exit(1);
    }

    pthread_t* dretve = (pthread_t*)calloc(broj_dretvi, sizeof(pthread_t));
    if(dretve == NULL) {
        printf("Dogodila se pogreska pri alociranju memorije!");
        exit(1);
    }

    for(long i = 0; i < broj_dretvi; i++) {
        if(pthread_create(&dretve[i], NULL, funkcija, (void*)i)) {
            printf("Greska prilikom stvaranja dretve %ld\n", i);
        }
    }

    for(long i = 0; i < broj_dretvi; i++) {
        pthread_join(dretve[i], NULL);
    }

    printf("Zbroj na kraju roditelja: %d\n", zbroj);

    free(dretve);

    return 0;
}
