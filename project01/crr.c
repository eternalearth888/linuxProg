#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "crr.h"

struct room makeroom(int id, char* name, time_t start, time_t end, char* desc) {
	struct room newroom;
	newroom.id = id;
	time_t start_t;
	time_t end_t;
	strncpy(newroom.name, name, ROOMNAME);
	strncpy(newroom.desc, desc, ROOMDESC);
	return newroom;
}

void printMenu();
int countRoom_fromFile(FILE *in);
void view_availableRooms(FILE *in,  struct room *record, int numRooms);

int main(int argc, char* argv[]) {
	// First error check for the correct number of arguments
	if (argc < 2) {
		fputs("Not enough ARGS.\n", stderr);
		return 1;
	}

	// Struct Related
	struct room *floorplan;

	// File Related
	FILE *ifp;
	ifp = fopen(argv[1], "r");

	// File error check
	if ( ifp == NULL) {
		fprintf(stderr, "Can't open input file: '%s'\n", argv[1]);
		exit(1);
	}

	int nRoom = countRoom_fromFile(ifp);

	int choice;

	printMenu();
	scanf("%i", &choice);	

	switch (choice) {
		case 1:
			view_availableRooms(ifp, floorplan, nRoom);
			break;
		case 2:
//			view_specificDate(ifp, floorplan);
			break;
		case 3:
//			view_specifcRoom();
			break;
		case 4:
//			search_event();
			break;
		case 5:
//			save_changes();
			break;
		case 0:
			printf("Good-bye!\n");
			exit(0);
			break;
		default:
			printf("Not a valid menu option. Try Again.\n");
			break;
	}

	// Close files and free pointers
	fclose(ifp);
	free(floorplan);

	return 0;
}

void printMenu() {
	printf("Menu:\n");
	printf("---------------------------------------------\n");
	printf("1. View Available Rooms\n");
	printf("2. View Reservations On Specific Date\n");
	printf("3. View Specific Room\n");
	printf("4. Search Event\n");
	printf("5. Save Changes\n");
	printf("0. To Quit\n");
	printf("---------------------------------------------\n");
	printf("Option: ");
}

int countRoom_fromFile(FILE *in) {

	// Count number of non-blank lines in rooms.dat
	char line;
	int numRooms = 0;

	while((line = fgetc(in)) != EOF) {
		if (line == '\n') {
			numRooms++;
		}

	}

	//Start at the beginning of the file now that we have reached the end
	fseek(in, 0, SEEK_SET);
	return numRooms;
}

void view_availableRooms(FILE *in,  struct room *record, int numRooms) {
	// Now that we know how many rooms to get from the file
	// Malloc the struct to adjust as necessary	
	record = malloc(numRooms*sizeof(struct room));

	// READ argv[1] text file (ex: rooms.dat)
	// Input values for room names into struct and add ids with them
	int i = 0;
	while (fscanf(in, "%s", &record[i].name) != EOF) {
		record[i].id = i;
		i++;
	}

	// Print Num Rooms
	printf("Num Rooms: %i\n",numRooms);

	// Verify ID:ROOMNAME, Print Struct
	for (int j = 0; j < numRooms; j++) {
		printf("%i:%s\n", record[j].id,record[j].name);
	}
	exit(0);

}