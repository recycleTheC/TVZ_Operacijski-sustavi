#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){
	
	if(argc < 2){
		printf("Neispravan poziv naredbe!\n");
		printf("%s <broj_child_procesa>\n", argv[0]);
		exit(-1);
	}
	
	int broj_child_procesa = 0;
	
	if(sscanf(argv[1], "%d", &broj_child_procesa) != 1){
		printf("Neispravan unos! Morate unijeti broj procesa djeteta!\n");
		exit(-1);
	}
	
	pid_t pid;
	
	setbuf(stdout, NULL);
	
	for(int i = 0; i < broj_child_procesa; i++){
		switch(pid = fork()){
			case -1:
				printf("Kreiranje procesa djeteta neuspjesno!\n");
				exit(-1);
			case 0:
				printf("Dijete #%d\n", i + 1);
				exit(0);
			default:
				printf("Roditelj #%d\n", i + 1);
				wait(NULL);
				break;
		}
	}
		
	return 0;
}
