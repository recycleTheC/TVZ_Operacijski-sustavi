#include<stdio.h>
#include<stdlib.h>

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
	}

	FILE* src = fopen(argv[2], "rb");
	if(src == NULL) {
		printf("Izvorisna datoteka se ne moze otvoriti za citanje!\n");
		exit(-3);
	}

	FILE* dst = fopen(argv[3], "wb");
	if(dst == NULL){
		printf("Odredisna datoteka se ne moze otvoriti za pisanje!\n");
		exit(-4);
	}

	/*fseek(src, 0, SEEK_END);
	unsigned long size = ftell(src);
	fseek(src, 0, SEEK_SET);
	printf("Velicina ishodisne datoteke: %d bajta\n", size);*/
	
	printf("Zapocinjem kopiranje datoteka koristeci buffer velicine %d bajta...\n", bufferSize);	

	while(fread(buffer, bufferSize, 1, src) != 0){
		fwrite(buffer, bufferSize, 1, dst);
	}

	fclose(src);
	fclose(dst);

	printf("Kopiranje zavreno!\n");

	return 0;

}
