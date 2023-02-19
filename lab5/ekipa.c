#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<string.h>

typedef enum {
	OSTALO,
	DIZNE,
	ELEKTRONIKA
} kvar_t;

typedef enum {
	PRAZNO,
	COKOLADA,
	CEVAPI,
	JANJETINA,
	STRUKLE,
	GRAH,
	KEKSI,
	KELJ,
	JABUKA
} jelo_t;

typedef struct {
	char ime[8];
	int konzumacija;
	int odbijanje;
	int prazan_stol;
} statistika_t;

pthread_mutex_t mutex;
jelo_t stol = PRAZNO;
int broj_jela = 0, kraj = 0;

int rng(int min, int max){
	return (rand() % (max - min + 1)) + min;
}

int faktorijel(int n){
	if(n <= 1) return 1;
	else return n * faktorijel(n - 1);
}

void programiranje(const char* ime){
	printf("%s sada programira\n", ime);
	faktorijel(rng(1,10));
}

void spavanje(const char* ime){
	int min = 5, max = 10;
	
	if(strcmp("Tin", ime) == 0){
		min = 6;
		max = 12;
	}
	
	printf("%s sada spava\n", ime);
	sleep(rng(min,max));
}

const char* jelo_str(jelo_t jelo){
	switch(jelo){
		case CEVAPI: return "cevapi";
		case KELJ: return "kelj";
		case COKOLADA: return "cokolada";
		case GRAH: return "grah";
		case STRUKLE: return "strukle";
		case JANJETINA: return "janjetina";
		case KEKSI: return "keksi";
		case JABUKA: return "jabuka";
		default: return "pogreska!";
	}
}

void* tin() {
	int counter = 0;
	const char* ime = "Tin";
	static statistika_t statistika = {"Tin", 0, 0, 0};

	while(!kraj){
		// spava
		spavanje(ime);
		
		// programira
		programiranje(ime);
		
		// konzumacija hrane - kritični odsječak		
		pthread_mutex_lock(&mutex);
		
		if(stol == PRAZNO){
			printf("%s je nasao prazan stol\n", ime);
			statistika.prazan_stol++;
		}
		else if(stol != CEVAPI && stol != JANJETINA){
			printf("%s konzumira hranu (%s)\n", ime, jelo_str(stol));
			statistika.konzumacija++;
			stol = PRAZNO;
		}
		else {
			printf("%s preskace obrok\n", ime);
			statistika.odbijanje++;
		}
		
		pthread_mutex_unlock(&mutex);
		
		// vozi auto na servis
		kvar_t kvar;
		
		if((counter * 100) % 20 == 0) kvar = ELEKTRONIKA;
		else if((counter * 100) % 25 == 0) kvar = DIZNE;
		else kvar = OSTALO;
		
		printf("%s vozi Alfu na servis\n", ime);
		
		switch(kvar){
			case DIZNE:
				sleep(4);
				break;
			case ELEKTRONIKA:
				sleep(2);
				break;
			case OSTALO:
				sleep(rng(2,4));
				break;
		}
		
	}
	
	return &statistika;
}

void* davor() {
	int counter = 0;
	const char* ime = "Davor";
	static statistika_t statistika = {"Davor", 0, 0, 0};

	while(!kraj){
		// spava
		spavanje(ime);
		
		// programira
		programiranje(ime);
		
		// konzumacija hrane - kritični odsječak		
		pthread_mutex_lock(&mutex);
		
		if(stol == PRAZNO){
			printf("%s je nasao prazan stol\n", ime);
			statistika.prazan_stol++;
		}
		else if(stol != COKOLADA && stol != KEKSI){
			printf("%s konzumira hranu (%s)\n", ime, jelo_str(stol));
			statistika.konzumacija++;
			stol = PRAZNO;
		}
		else {
			printf("%s preskace obrok\n", ime);
			statistika.odbijanje++;
		}
		
		pthread_mutex_unlock(&mutex);
		
		// gleda TV
		printf("%s gleda TV\n", ime);
		sleep(rng(2,4));
	}
	
	return &statistika;
}

void* ivica() {
	int counter = 0;
	const char* ime = "Ivica";
	static statistika_t statistika = {"Ivica", 0, 0, 0};

	while(!kraj){
		// spava
		spavanje(ime);
		
		// igra tenis
		printf("%s igra tenis\n", ime);
		sleep(rng(2,4));
		
		// konzumacija hrane - kritični odsječak		
		pthread_mutex_lock(&mutex);
		
		if(stol == PRAZNO){
			printf("%s je nasao prazan stol\n", ime);
			statistika.prazan_stol++;
		}
		else if(stol != GRAH && stol != KELJ){
			printf("%s konzumira hranu (%s)\n", ime, jelo_str(stol));
			statistika.konzumacija++;
			stol = PRAZNO;
		}
		else {
			printf("%s preskace obrok\n", ime);
			statistika.odbijanje++;
		}
		
		pthread_mutex_unlock(&mutex);
		
		// programira
		programiranje(ime);
	}
	
	return &statistika;
}

void* ivan() {
	int counter = 0;
	const char* ime = "Ivan";
	static statistika_t statistika = {"Ivan", 0, 0, 0};

	while(!kraj){
		// spava
		spavanje(ime);
		
		// slusa sviranje klavira
		printf("%s slusa sviranje klavira\n", ime);
		sleep(rng(2,4));
		
		// konzumacija hrane - kritični odsječak		
		pthread_mutex_lock(&mutex);
		
		if(stol == PRAZNO){
			printf("%s je nasao prazan stol\n", ime);
			statistika.prazan_stol++;
		}
		else if(stol != STRUKLE){
			printf("%s konzumira hranu (%s)\n", ime, jelo_str(stol));
			statistika.konzumacija++;
			stol = PRAZNO;
		}
		else {
			printf("%s preskace obrok\n", ime);
			statistika.odbijanje++;
		}
		
		pthread_mutex_unlock(&mutex);
		
		// programira
		programiranje(ime);
	}
	
	return &statistika;
}

void* kuharica() {

	while(broj_jela > 0){
		// kuhanje jela
		jelo_t skuhano_jelo = rng(1, 8);
		printf("Kuharica kuha jelo (%s)\n", jelo_str(skuhano_jelo));
		sleep(rng(1,2));
		broj_jela--;
		
		// cekanje na prazan stol
		while(stol != PRAZNO){}
		
		// stavljanje jela na stol - kriticni odsjecak
		pthread_mutex_lock(&mutex);
		
		stol = skuhano_jelo;
		printf("Kuharica je stavila jelo (%s) na stol\n", jelo_str(skuhano_jelo));
		
		pthread_mutex_unlock(&mutex);
		
		// odmaranje
		
		printf("Kuharica se odmara\n");
		sleep(rng(1,2));
	}
	
	printf("Kuharica je zavrsila s radom\n");
	kraj = 1;
	
	return 0;
}

int main(int argc, char* argv[]) {
	
    pthread_t osobe[5];
    
    if(argc != 2){
		printf("Neispravan poziv programa!\n");
		printf("%s <broj_jela>\n", argv[0]);
		exit(1);
	}
	
	if(sscanf(argv[1], "%d", &broj_jela) != 1){
		printf("Neispravan poziv programa!\n");
		printf("%s <broj_jela>\n", argv[0]);
		exit(1);
	}
		
	srand(time(NULL));
	pthread_mutex_init(&mutex, NULL);

    pthread_create(&osobe[0], NULL, tin, NULL);
    pthread_create(&osobe[1], NULL, davor, NULL);
    pthread_create(&osobe[2], NULL, ivica, NULL);
    pthread_create(&osobe[3], NULL, ivan, NULL);
    pthread_create(&osobe[4], NULL, kuharica, NULL);
    
    statistika_t statistike[4];
    
    for(int i = 0; i < 5; i++){
		void* tmp;
		pthread_join(osobe[i], &tmp);
		if(tmp != NULL){
			statistike[i] = *(statistika_t*)tmp;
		}
	}
	
	for(int i = 0; i < 4; i++){
		printf("%s - kozumacija: %d, odbijanje: %d, prazan stol: %d\n", statistike[i].ime, statistike[i].konzumacija, statistike[i].odbijanje, statistike[i].prazan_stol);
	}
	
	pthread_mutex_destroy(&mutex);
	
    return 0;
}
