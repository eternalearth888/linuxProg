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
void fill_struct(FILE *in, struct room *record);
void view_availableRooms(FILE *in,  struct room *record, int numRooms);

void save_res(FILE *in, struct room *record, int numRooms, int roomChoice);

void valid_time(time_t start_t, time_t end_t);
void valid_date(time_t start_d, time_t end_d);

int main(int argc, char* argv[]) {
	// First error check for the correct number of arguments
	// Must have at least : $ ./executable rooms.dat schedule.dat
	if (argc < 2) {
		fputs("Not enough ARGS.\n", stderr);
		return 1;
	}

	// Struct Related
	struct room *floorplan;

	// File Related - rooms.dat
	FILE *ifp;
	ifp = fopen(argv[2], "r");

	// File Related - schedule.data
	// Creating file
	FILE *ofp;
	ofp = fopen(argv[2],"a+"); //  Open for reading and writing (append if file exists)

	// File error check
	if ( ifp == NULL) {
		fprintf(stderr, "Can't open input file: '%s'\n", argv[1]);
		exit(1);
	}

	int nRoom = countRoom_fromFile(ifp);
	fill_struct(ifp, floorplan);

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
	fclose(ofp);
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

void fill_struct(FILE *in, struct room *record) {
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
}

void view_availableRooms(FILE *in,  struct room *record, int numRooms) {
	// Print Num Rooms
	//printf("Num Rooms: %i\n",numRooms);
	printf("Available Rooms:\n");

	// Verify ID:ROOMNAME, Print Struct
	for (int j = 0; j < numRooms; j++) {
		printf("%i:%s\n", record[j].id,record[j].name);
	}
	
	//User room choice for reservation 
	int roomChoice;
	
	printf("Choose room based on number:\n");
	scanf("%d", &chosen);

	save_res(numRooms,in,record,roomChoice);

}

void save_res(FILE *in, struct room *record, int numRooms, int roomChoice) {
	struct room reservations;

	// Grab the roomname
	strncpy(reservation[roomChoice].name, &record[roomChoice].name, ROOMNAME);

	// Adding start time
	// Followed example for time from here: http://stackoverflow.com/questions/11428014/c-validation-in-strptime
	struct tm dtm={0};
	char DATEBUF[]="2014/01/01";

	struct tm ttm={0};
	char TIMEBUF[]="00:00";

	time_t start_date;
	time_t start_time;
	time_t start;

	fputs("Start time reservation:\n");

	fputs("\tEnter Date 'YYYY/MM/DD' : ",stdout);
	fgets(start_date,sizeof(DATEBUF), stdin);
	strptime(DATEBUF, "%n%Y/%m/%d", &dtm);
	mktime(&dtm); 	// if the strings before and after mktime do not match, then we know the input string was not a valid date;


	fputs("\tEnter Time 'HH:MM' : ", stdout);
	fgets(start_time, sizeof(TIMEBUF), stdin);
	strptime(TIMEBUF, "%n/%H:%M", &ttm);
	mktime(&ttm);

	// Adding end time
	time_t end;
	fputs("Enter end time for reservation:\n");
	fputs("\tYYYY/MM/DD HH:MM\n",stdout);


	// Adding event description
	char event_desc[ROOMDESC];
	fputs("Event Description:\n", stdout);
	fgets(event_desc, ROOMDESC, stdin);
	strncpy(reservation[roomChoice].desc, event_desc, ROOMDESC);
}

void valid_time(time_t start_t, time_t end_t) {
	if (start_t > end_t) {
		fputs("Start time cannot be greater than end time.\n", stderr);
		exit(0);
	}
}

void valid_date(time_t start_d, time_t end_d){
	// First grab current date
	// Example from : http://en.wikibooks.org/wiki/C_Programming/C_Reference/time.h/time_t
	time_t now = time(NULL);
	struct tm *ts;
	char buf[80];

	// Format the correct date YYYY/MM/DD
	ts = localtime(&now);
	strftime(buf, sizeof(buf), %n%Y/%m/%d, ts);	

	if (buf < start_d) {
		fputs("Start date canonot be before current date.\n", stderr);
	} else {
		if (start_d > end_d) {
			fputs("Start date cannot be after end date.\n", stderr);
		}
	}

}