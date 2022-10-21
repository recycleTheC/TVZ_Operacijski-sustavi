#include<stdio.h>
#include<stdlib.h>

#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

// int open(const char* staza, int zastavice, mode_t dozvole);
// ssize_t read(int opisnik, void* spremnik, size_t kolicina);
// ssize_t write(int opisnik, const void* spremnik, size_t kolicina); 

int main(int argc, char* argv[]){
	
	if(argc < 4){
		printf("Nije upisan dovoljan broj parametara!\n");
		exit(-1);
	}
	
	int bufferSize = -1;
	
	if(sscanf(argv[1], "%d", &bufferSize) != 1){
		printf("Nije upisana ispravna velicina buffera!\n");
		exit(-2);
	}
	
	if(bufferSize < 1){
		printf("Nije upisana ispravna velicina buffera!\n");
		exit(-2);
	}
	
	char* buffer = (char*)calloc(bufferSize, 1);
	if(buffer == NULL){
		printf("Greska pri alociranju buffera!\n");
		exit(-2);
	}

	int src = open(argv[2], O_RDONLY); // otvaranje samo za citanje
	if(src == -1) {
		printf("Izvorisna datoteka se ne moze otvoriti za citanje!\n");
		exit(-3);
	}
	
	int zastavice = O_WRONLY | O_CREAT | O_TRUNC;
	int prava = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	int dst = open(argv[3], zastavice, prava); // otvaranje za pisanje, postavljanje prava
	if(dst == -1){
		printf("Odredisna datoteka se ne moze otvoriti za pisanje!\n");
		exit(-4);
	}

	printf("Kopiranje datoteke uz buffer velicine %d bajta...\n", bufferSize);	

	while(read(src, buffer, bufferSize) > 0){
		if(write(dst, buffer, bufferSize) == -1){
			printf("Greska prilikom pisanja u datoteku! Prekidam rad.\n");
			exit(-5);
		}
	}

	close(src);
	close(dst);

	printf("Kopiranje zavreno!\n");

	return 0;

}
