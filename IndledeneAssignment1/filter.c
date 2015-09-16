#include <stdio.h>
#include <stdlib.h>
#include "filter.h"

int filter(int data){

	static long count = 0;

	static short xArrayL[13] = {0}; //Low pass
	static short yArrayL[3] = {0};
	static short xArrayH[33] = {0}; //High pass
	static short yArrayH[2] = {0};
	static short xArrayD[5] = {0};  //Derivative
	static short toSquare = 0;      //To Square
	static short xArrayM[30] = {0}; //Moving window
	short result;					//Result

	xArrayL[(count+13)%13]=data; //Assign nextData to the array

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

	//Reset count, as it is static
	count++;
	count = count%(2*3*5*13*30*33);

	return result;
}
