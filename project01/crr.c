#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "crr.h"

struct room makeroom(int id, char* name) {
	struct room newroom;
	newroom.id = id;
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
		floorplan[i].id = i;
		i++;
	}

	// Verify rooms
	for (int j = 0; j < FLOORPLAN; j++) {
		printf("%i:%s\n", floorplan[j].id,floorplan[j].name);
	}

	fclose(ifp);
	//free(floorplan);

	return 0;
}

