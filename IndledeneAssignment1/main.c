#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filter.h"

static const char filename[] = "ECG.txt";

int main(int argc, char *argv[]) {

	FILE *file = fopen(filename, "r"); //Open file
	if(!file){
		printf("Couldn't load file, check file name."); //If the file isn't scanned return -1
		return -1;
	}

	for(int i = 0; i < 10; i++){ //Testing
		int data = getNextData(file);
		printf("%i, ", data);
		int out = filter(data);
		printf("%i. \n", out);
	}

	return 0;
}
