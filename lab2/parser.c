#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
	char tip[16];
	int redni_broj;
} Zapis;

int main(int argc, char* argv[]){
	
	if(argc < 2){
		printf("Neispravan poziv naredbe!\n");
		printf("%s <ulazna_datoteka>\n", argv[0]);
		exit(-1);
	}
	
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
	
	int redni_broj = 0, broj_neocekivanih = 0;
	Zapis zapis, prethodni;
	
	while(fscanf(datoteka, "%s #%d", zapis.tip, &zapis.redni_broj) == 2){
		redni_broj++;
		
		if(redni_broj % 2 == 0) {
			int greska = 0;
		
			if(strcmp(zapis.tip, prethodni.tip) == 0){
				greska++;
				broj_neocekivanih++;
			}
			
			if(greska) printf("Neocekivani zapis (%d): %s #%d\n", redni_broj, zapis.tip, zapis.redni_broj);
		}

		prethodni = zapis;
	}
	
	if(redni_broj > 0 && redni_broj % 2 == 0 && broj_neocekivanih % 2 == 0){
		redni_broj /= 2;
		broj_neocekivanih /= 2;
	}
	else {
		printf("Nesto nije u redu s ulaznom datotekom! Napraviti rucnu provjeru...\n");
		exit(-3);
	}
	
	printf("Broj odstupanja: %d\n", broj_neocekivanih);
	printf("Broj izvodjenja: %d\n", redni_broj);
	
	if(broj_neocekivanih > 0){
		printf("Odstupanje: %.2f\%\n", broj_neocekivanih * 100.0 / redni_broj);
	}
	
	fclose(datoteka);
	
	return 0;
}
