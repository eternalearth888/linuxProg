#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compareDouble(void* left, void* right) {
	double diff = *(double*)left-*(double*)right;
	if (diff < 0) {
		return -1;
	} else if (diff > 0) {
		return 1;
	}
	return 0;
}

int main( int argc, char* argv[] ) { 

	FILE* fp;
	
	double *data;
	double dtemp;
	int N=1000000;
	
	
	fp=fopen("realdata.lis", "r");

	if (!fp) {
		fputs("ERROR OPENING FILE", stderr);
		exit(1);
	}
	
	// now we know how many numbers we have
	// dynamically allocate an array with exactly the right size
	data=malloc(N*sizeof(double));
	
	// read numbers into array
	for (int i=0; i < N; i++) {
		fscanf(fp, "%lf", &data[i]);
	}
	
	// print array
	for (int j=0; j < N; j++) {
		printf("%lf", data[j]);
		printf("\n");
	}
	
	// free pointers and close files
	free(data);
	data = NULL;
	fclose(fp);
	
	return 0;
}
