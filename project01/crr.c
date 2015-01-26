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

	#define FLOORPLAN 10

	struct room floorplan[] = {{1,"Kitchen"},{2,"Ballroom"},{3,"Conservatory"},{4,"Dining Room"},{5, "Cellar"},{6,"Billiard Room"},{7,"Library"},{8,"Lounge"},{9,"Hall"},{10,"Study"}};

	
	printf("ID\tROOM\n");
	printf("-----------------------\n");
	for (int i = 0; i < (sizeof(floorplan)/sizeof(struct room)); i++) {
		printf("%i\t", floorplan[i].id);
		printf("%s\n", floorplan[i].name);
	}
	printf("-----------------------\n");

//	free(floorplan);
	return 0;
}

