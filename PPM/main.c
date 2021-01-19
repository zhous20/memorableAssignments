#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filter.h"

extern double getTime();

int main(int argc,char *argv[])
{
	double time0 = getTime();

	int *width, *height, *max;
	RGB *array=readPPM(argv[1],&width,&height,&max);

	double time1 = getTime();

	int n = atoi(argv[3]);
	if(*argv[4]=='A')
	{
		denoiseImage(width,height,array,n,MEAN);
		double time2 = getTime();
		writePPM(argv[2],width,height,max,denoiseImage(width,height,array,n,MEAN));
		double time3 = getTime();
		double n1=time1-time0;
		double n2=time2-time1;
		double n3=time3-time2;
		printf("Input file read in %.1e seconds\n", n1);
		printf("Image processed in %.1e seconds\n", n2);
		printf("Output file written in %.1e seconds\n", n3);
	}
	else if(*argv[4]=='M')
	{
		denoiseImage(width,height,array,n,MEDIAN);
		double time2 = getTime();
		writePPM(argv[2],width,height,max,denoiseImage(width,height,array,n,MEDIAN));
		double time3 = getTime();
		double n1=time1-time0;
		double n2=time2-time1;
		double n3=time3-time2;
		printf("Input file read in %.1e seconds\n", n1);
		printf("Image processed in %.1e seconds\n", n2);
		printf("Output file written in %.1e seconds\n", n3);
	}

	return 0;
}
