#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define VELICINA_POLJA 100000

char polje[VELICINA_POLJA] = {0};

int main(){
	srand(time(NULL));
	
	for(int i = 0; i < VELICINA_POLJA; i++){
		if(rand() % 2 == 0) polje[i] = 1;
		else polje[i] = -1;
		
		printf("%c\n", polje[i]);
	}
	
	sleep(50);
	
	return 0;
}
