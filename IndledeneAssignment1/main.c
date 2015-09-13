#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

static const char filename[] = "ECG.txt";

int main(int argc, char *argv[]) {

	FILE *file = fopen(filename, "r"); //Open file
	if(!file){
		printf("Didn't load file"); //If the file isn't scanned return -1
		return -1;
	}

	short xArrayL[13] = {0};//Low pass
	long count = 0;
	short yArrayL[3] = {0};
	short xArrayH[33] = {0};
	short yArrayH[2] = {0};
	short xArrayD[5] = {0};
	short toSquare = 0;
	short xArrayM[30] = {0};
	short result;

	for(int i = 0; i < 100; i++){
		//Setup
		int nextData = getNextData(file); //Load next data point
		printf("%d, ", nextData); //print data point
		xArrayL[(count+13)%13]=nextData; //Assign nextData to the array

		//Low pass
		yArrayL[(count)%3] = 2 * yArrayL[(count-1+3)%3] - yArrayL[(count-2+3)%3] + (xArrayL[(count)%13]-2 * xArrayL[(count-6+13)%13] + xArrayL[(count-12+13)%13])/32;
		xArrayH[(count)%33] = yArrayL[count%3];
		printf("%d, ", xArrayH[(count)%33]);

		//High pass
		yArrayH[count%2] = yArrayH[(count-1+2)%2]-xArrayH[count%33]/32+xArrayH[(count-16+33)%33]-xArrayH[(count-17+33)%33]+(xArrayH[(count-32+33)%33])/32;
		xArrayD[count%5] = yArrayH[count%2];
		printf("%d, ",xArrayD[count%5]);

		//Derivative
		toSquare = (2*xArrayD[count%5]+xArrayD[(count-1+5)%5]-xArrayD[(count-3+5)%5]-2*xArrayD[(count-4+5)%5])/8;
		printf("%d, ", toSquare);

		//Squaring
		xArrayM[count%30] = toSquare*toSquare;
		printf("%d, ", xArrayM[count%30]);

		//Moving Window Integration
		int j = 29;
		int temp = 0;
		while(j>=0){
			temp += xArrayM[(count-j+30)%30];
			j--;
		}
		result = temp/30;
		count++;
		count = count%(2*3*5*13*30*33);

		printf("%d. \n", result);
	}
	return 0;
}

//Low Pass Filter:
//short temp = 0;
//xArrayL[(count+13)%13]=nextData;
//temp = 2 * yArrayL[(count-1+3)%3] - yArrayL[(count-2+3)%3] + (xArrayL[(count)%13]-2 * xArrayL[(count-6+13)%13] + xArrayL[(count-12+13)%13])/32;
//yArrayL[(count)%3]= temp;
//xArrayH[(count)%33] = yArrayL[count%3];
//temp = ((count-12+13) % 13);
//printf("%i, ", temp);
//printf("%i.\n", xArrayH[i]);




//
//	short xArrayL[13] = {0};//Low pass
//    long count = 0;
//    short yArrayL[3] = {0};
//    short xArrayH[33] = {0};//High pass
//    short yArrayH[2] = {0};
//    short xArrayD[5] = {0};//Derivative
//    //Squaring
//    short toSquare = 0;
//    short xArrayM[30] = {0};//Movin' window
//    //result
//    short result;
//
//    //Low pass... I hope
//    yArrayL[count%13] = 2*yArrayL[(count-1)%3]-yArrayL[count%3]+1/32*(xArrayL[count%13]-2*xArrayL[(count-6)%13]+xArrayL[(count-12)%13]);
//    xArrayH[count%33] = yArrayL[count%13];
//    //High pass... Passhaps? Teehee!
//    yArrayH[count%2] = yArrayH[(count-1)%2]-xArrayH[count%33]/32+xArrayH[(count-16)%33]-xArrayH[(count-17)%33]+(xArrayH[(count-32)%33])/32;
//    xArrayD[count%5] = yArrayH[count%2];
//    //It's derivative, dear Watson!
//    toSquare = 1/8*(2*xArrayD[count%5]+xArrayD[(count-1)%5]-xArrayD[(count-3)%5]-2*xArrayD[(count-4)%5]);
//    //I'm square with that!
//    xArrayM[count%30] = toSquare^2;
//    //I'm movin' da windo'
//    int i = 29;
//    int temp = 0;
//    while(i>=0){
//        temp += xArrayM[(count-i)%30];
//        i--;
//    }
//    result = temp/30;
//    count++;
//    count = count%(2*3*5*13*30*33);
