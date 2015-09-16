#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int getNextData(FILE *file){
	int value;
	fscanf(file, "%i", &value);  //fscanf saves next number to value

	if(value == EOF){
			printf("End of file is found");
	}

	/*
	 * Alternative way
	 *
	static FILE *file = fopen(filename, "r");
	if(!file){
		printf("Didn't load file");
		return -1;
	}
	int value;
	fscanf(file, "%i", &value);

	if(value == EOF){
		printf("End of file is found");
	}
	 */

	return value;
}
