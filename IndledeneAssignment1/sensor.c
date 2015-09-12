#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int getNextData(FILE *file){
	int value;
	fscanf(file, "%i", &value);  //fscanf saves next number to value

	if(value == EOF){            //Fail mesasge if EOF is found
		printf("End of file is found");
	}

	return value;
}
