#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char* argv[] ) { 

	FILE* fp;
	
	float *data;
	float dtemp;
	int N=1000000;
	
	
	fp=fopen("realdata.lis", "r");

	if (!fp) {
		fputs("ERROR OPENING FILE", stderr);
		exit(1);
	}
	
	/** 
	*	//find out how many numbers/lines we have
	*	while (!feof(fp)) {
	*		fscanf(fp, "%f", dtemp);
	*		N++;
	*	}
	**/
	
	// now we know how many numbers we have
	// dynamically allocate an array with exactly the right size
	data=malloc(N*sizeof(float));
	
	// read numbers into array
	for (int i=0; i < N; i++) {
		fscanf(fp, "%f", &data[i]);
	}
	
	// print array
	for (int j=0; j < N; j++) {
		printf("%f", data[j]);
		printf("\n");
	}
	
	// free pointers and close files
	free(data);
	data = NULL;
	fclose(fp);
	
	return 0;
}
