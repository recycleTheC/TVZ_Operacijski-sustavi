#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	if(argc < 3){
		printf("Nije upisan dovoljan broj parametara!\n");
		exit(-1);
	}

	FILE* src = fopen(argv[1], "rb");
	if(src == NULL) {
		printf("Izvorisna datoteka ne postoji!\n");
		exit(-2);
	}

	FILE* dst = fopen(argv[2], "wb");
	if(dst == NULL){
		printf("Odredisna datoteka ne postoji!\n");
		exit(-3);
	}

	fseek(src, 0, SEEK_END);
	int size = ftell(src);
	fseek(src, 0, SEEK_SET);

	printf("Velicina ishodisne datoteke: %d\n", size);
	printf("Citam bajt po bajt...\n");	

	for(int i = 0; i < size; i++) {
		char data;
		fread(&data, sizeof(data), 1, src);
		fwrite(&data, sizeof(data), 1, dst);
	}

	fclose(src);
	fclose(dst);

	printf("Kopiranje zavreno!\n");

	return 0;

}
