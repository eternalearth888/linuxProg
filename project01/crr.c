#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "crr.h"

struct room makeroom(char* name) {
	struct room newroom;
	strncpy(newroom.name, name, ROOMBUF);
	return newroom;
}

int main(int argc, char* argv[]) {
	// Struct Related
	#define FLOORPLAN 10
	struct room floorplan[FLOORPLAN];

	// File Related
	FILE *ifp;
	ifp = fopen(argv[1], "r");

	// First error check for the correct number of arguments
	if (argc < 2) {
		fputs("Not enough ARGS.\n", stderr);
		return 1;
	}

	if ( ifp == NULL) {
		fprintf(stderr, "Can't open input file: '%s'\n", argv[1]);
		exit(1);
	} 

	// READ argv[1] text file (ex: rooms.dat)
	int i = 0;
	while (fscanf(ifp, "%s", &floorplan[i].name) != EOF) {
		i++;
	}

	// Verify rooms
	for (int j = 0; j < FLOORPLAN; j++) {
		printf("%i:%s\n", j,floorplan[j].name);
	}

	fclose(ifp);
	//free(floorplan);

	return 0;
}

