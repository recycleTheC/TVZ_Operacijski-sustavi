#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>

long mjesta[10][10] = {{0}};

int rng(int min, int max){
	return (rand() % (max - min + 1)) + min;
}

void login(void){
	sleep(rng(1,5));
}

long* dohvati_polje(void) {
    sleep(rng(1,3));
    return &mjesta[0][0];
}

typedef struct {
	long index;
	int kasnjenje;
} arguments;

void* check_in(void* args){
	arguments* argumenti = (arguments*)args;
	
	if(argumenti->kasnjenje) sleep(1);
	
	// login na sustav
	login();
	
	// dohvat mjesta
	long* mjesta = dohvati_polje();
	
	// odabir mjesta
	long index = argumenti->index;
	int odabrano_mjesto = rng(0,99);
	
	// u 50% slucajeva korisnik odbija ponudjeno mjesto
	if(index % 2 == 0) odabrano_mjesto = rng(0,99);
	
	printf("Odabrano mjesto: %ld -> %d\n", index + 1, odabrano_mjesto);
	
	sleep(rng(1,2));
	
	*(mjesta + odabrano_mjesto) = index + 1;
	
	free(args);
	
	pthread_exit(NULL);
}

void provjeri_rezervacije(int* popunjeno, int* nepopunjeno){
	*popunjeno = 0;
	*nepopunjeno = 0;
	
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if(mjesta[i][j] == 0) (*nepopunjeno)++;
			else (*popunjeno)++;
		}
	}
}

int main() {
	
	srand(time(NULL));
    int broj_dretvi = 100;

    pthread_t* dretve = (pthread_t*)calloc(broj_dretvi, sizeof(pthread_t));
    if(dretve == NULL) {
        printf("Dogodila se pogreska pri alociranju memorije!");
        exit(1);
    }

	int kasnije_pokretanje = rng(0,99);
	printf("Kasnije ce se pokrenuti %d dretvi!\n", kasnije_pokretanje);

    for(long i = 0; i < broj_dretvi; i++) {
		arguments* arg = (arguments*)malloc(sizeof(arguments));
		
		arg->index = i;
		arg->kasnjenje = i < kasnije_pokretanje ? 1 : 0;
		
        if(pthread_create(&dretve[i], NULL, check_in, (void*)arg)) {
            printf("Greska prilikom stvaranja dretve %ld\n", i);
        }
    }

    for(long i = 0; i < broj_dretvi; i++) {
        pthread_join(dretve[i], NULL);
    }

	printf("\nPopunjenost mjesta u avionu:\n\n");
	
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			int mjesto = mjesta[i][j];
			
			if(mjesto == 0) printf("%3c", '.');
			else printf("%3d", mjesto);
		}
		printf("\n");
	}
	
	printf("\n");
	
	int popunjeno = 0, nepopunjeno = 0;
	provjeri_rezervacije(&popunjeno, &nepopunjeno);
	
	printf("Popunjeno mjesta: %d\n", popunjeno);
	printf("Nepopunjeno mjesta: %d\n", nepopunjeno);

    free(dretve);

    return 0;
}
