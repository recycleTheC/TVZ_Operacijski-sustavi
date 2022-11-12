#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define RED "\x1B[31m"
#define RESET "\x1B[0m"

typedef struct {
	char tip[16];
	int redni_broj;
} Zapis;

int predvidiTip(int paritet, int redni_broj){
	if(redni_broj % 2 != 0) {
		if(paritet == 0) return 1;
		else return 0;
	}
	else return paritet;
}

int main(int argc, char* argv[]){
	
	if(argc < 2){
		printf(RED "Neispravan poziv naredbe!\n" RESET);
		printf("%s <ulazna_datoteka> <debug?>\n", argv[0]);
		exit(-1);
	}
	
	int debug = argc == 3 ? strcmp(argv[2], "debug") == 0 ? 1 : 0 : 0;
	
	char putanja[64] = {0};
	
	if(sscanf(argv[1], "%s", putanja) != 1){
		printf("Neispravan unos putanje datoteke!\n");
		exit(-1);
	}
	
	FILE* datoteka = fopen(putanja, "r");
	
	if(datoteka == NULL){
		printf("Nije moguce otvoriti datoteku '%s'\n", putanja);
		exit(-2);
	}
	
	printf("Citanje datoteke '%s' ...\n", putanja);
	
	char tip[2][16] = {"Roditelj", "Dijete"};
	int redni_broj = 0, broj_neocekivanih = 0, paritet = 0;
	Zapis zapis, prethodni;
	
	fscanf(datoteka, "%s #%d", zapis.tip, &zapis.redni_broj);
	
	if(strcmp(zapis.tip, tip[0]) == 0) paritet = 0;
	else if (strcmp(zapis.tip, tip[1]) == 0) paritet = 1;
	else {
		printf("Nesto nije u redu s ulaznom datotekom! Napraviti rucnu provjeru...\n");
		exit(-3);
	}
	
	prethodni = zapis;
	redni_broj++;
	
	while(fscanf(datoteka, "%s #%d", zapis.tip, &zapis.redni_broj) == 2){
		redni_broj++;

		if(strcmp(zapis.tip, tip[predvidiTip(paritet, redni_broj)]) == 0){
			broj_neocekivanih++;
			if(debug) printf("Neocekivani zapis (%d): %s #%d\n", redni_broj, zapis.tip, zapis.redni_broj);
		}

		prethodni = zapis;
	}
	
	if(redni_broj % 2 == 0 && broj_neocekivanih % 2 == 0){
		broj_neocekivanih /= 2;
		redni_broj /= 2;
	}
	else {
		printf("Nesto nije u redu s ulaznom datotekom! (%d/%d) Napraviti rucnu provjeru...\n", broj_neocekivanih, redni_broj);
		exit(-3);
	}
	
	printf("Broj odstupanja: %d\n", broj_neocekivanih);
	printf("Broj izvodjenja: %d\n", redni_broj);
	
	if(broj_neocekivanih > 0){
		double odstupanje = (double)broj_neocekivanih * 100 / redni_broj;
		printf(RED "\nOdstupanje: %.3lf\%\n" RESET, odstupanje);
		printf("Točnost: %.3lf\%\n", 100.00 - odstupanje);
	}
	
	fclose(datoteka);
	
	return 0;
}
