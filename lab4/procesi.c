#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int zbroj = 0;

int main(int argc, char* argv[]){

	int broj_procesa = 0;
	
	if(argc != 2){
		printf("Neispravan poziv naredbe!\nZavrsavam s radom!\n");
		exit(1);
	}
	
	if(sscanf(argv[1], "%d", &broj_procesa) != 1){
		printf("Nije unesen ispravan broj procesa!\nZavrsavam s radom!\n");
		exit(1);
	}
	
	pid_t pid;
	
	for(int i = 0; i < broj_procesa; i++) {
		switch(pid = fork()){
			case -1:
				printf("Dogodila se pogreska pri kreiranju procesa!\n");
				exit(2);
			case 0:
				zbroj++;
				exit(0);
			default:
				wait(NULL);
				break;
		}
	}
	
	printf("Zbroj na kraju roditelja: %d\n", zbroj);
	
	return 0;
}
