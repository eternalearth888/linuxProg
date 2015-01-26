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
	struct room *floorplan;

	// File Related
	FILE *ifp;
	ifp = fopen(argv[1], "r");

	// First error check for the correct number of arguments
	if (argc < 2) {
		fputs("Not enough ARGS.\n", stderr);
		return 1;
	}

	// File error check
	if ( ifp == NULL) {
		fprintf(stderr, "Can't open input file: '%s'\n", argv[1]);
		exit(1);
	}

	// Count number of non-blank lines in rooms.dat
	char line;
	int numRooms = 0;

	while((line = fgetc(ifp)) != EOF) {
		if (line == '\n') {
			numRooms++;
		}
	}

	//Start at the beginning of the file now that we have reached the end
	fseek(ifp, 0, SEEK_SET);

	// Now that we know how many rooms to get from the file
	// Malloc the struct to adjust as necessary	
	floorplan = malloc(numRooms*sizeof(struct room));

	// READ argv[1] text file (ex: rooms.dat)
	// Input values for room names into struct and add ids with them
	int i = 0;
	while (fscanf(ifp, "%s", &floorplan[i].name) != EOF) {
		floorplan[i].id = i;
		i++;
	}

	printf("Num Rooms: %i\n",numRooms);

	// Verify ID:ROOMNAME
	for (int j = 0; j < numRooms; j++) {
		printf("%i:%s\n", floorplan[j].id,floorplan[j].name);
	}

	fclose(ifp);
	free(floorplan);

	return 0;
}

