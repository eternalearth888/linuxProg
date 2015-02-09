#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "crr.h"

/**FUNCTION DECLARATIONS**/

// Print Functions
void print_menu();
void print_confirmation(int choice);

int countRoom(FILE *in);
struct room *fill_struct(FILE *in, int num);

void view_available(struct room *record, int num);
//void save_res(struct room *record, int roomChoice);
void valid_time(time_t start_t, time_t end_t);

/**MAIN PROGRAM**/

int main(int argc, char* argv[]) {
	// First error check for the correct number of arguments
	// Must have at least : $ ./executable rooms.dat schedule.dat
	if (argc < 2) {
		fputs("Not enough ARGS.\n", stderr);
		return 1;
	}

	// File Related - rooms.dat
	FILE *ifp;
	ifp = fopen(argv[1], "r");

	// File Related - schedule.data
	// Creating file
	FILE *ofp;
	ofp = fopen(argv[2],"a+"); //  Open for reading and writing (append if file exists)

	// File error check
	if ( ifp == NULL) {
		fprintf(stderr, "Can't open input file: '%s'\n", argv[1]);
		exit(1);
	}

	// Gathering room data
	int numRoom = countRoom(ifp);

	// Fill room struct with id and names
	struct room *create_room = fill_struct(ifp, numRoom);

	
	print_menu();
	int choice;
	scanf("%i", &choice);	

	printf("---------------------------------------------\n");
	printf("---------------------------------------------\n");

	switch (choice) {
		case 1:
			view_available(create_room, numRoom);
			break;
		case 2:
//			view_specificDate(ifp, create_room);
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
	free(create_room);

	return 0;
}

void print_menu() {
	printf("Menu:\n");
	printf("---------------------------------------------\n");
	printf("\t1. View Available Rooms\n");
	printf("\t2. View Reservations On Specific Date\n");
	printf("\t3. View Specific Room\n");
	printf("\t4. Search Event\n");
	printf("\t5. Save Changes\n");
	printf("\t0. To Quit\n");
	printf("---------------------------------------------\n");
	printf("Option: ");
}

int countRoom(FILE *in) {
	// Count number of non-blank lines in rooms.dat
	char line;
	int num = 0;

	while((line = fgetc(in)) != EOF) {
		if (line == '\n') {
			num++;
		}

	}
	//Start at the beginning of the file now that we have reached the end
	fseek(in, 0, SEEK_SET);

	return num;
}

struct room *fill_struct(FILE *in, int num) {
	struct room *record_room;

	// Now that we know how many rooms to get from the file
	// Malloc the struct to adjust as necessary	
	record_room = malloc(num*sizeof(struct room));

	// READ argv[1] text file (ex: rooms.dat)
	// Input values for room names into struct and add ids with them
	int i = 0;
	while (fscanf(in, "%s", &record_room[i].name) != EOF) {
		record_room[i].id = i;
		//sprintf(record[i].name,"TEST");
		i++;
	}

	return record_room;
}

void print_rooms(struct room *record, int num) {
	for (int j = 0; j < num; j++) {
		printf("\t%i:%s\n", record[j].id, record[j].name);
	}
}

void view_available(struct room *record, int num) {
	// Print Num Rooms
	//printf("Num Rooms: %i\n",num);

	printf("Available Rooms:\n");
	print_rooms(record, num);

	//User room choice for reservation 
	int roomChoice;
	int confirm;
	
	printf("\nCHOOSE ROOM NUMBER: ");
	scanf("%d", &roomChoice);
	printf("---------------------------------------------\n");
	printf("Are you sure?\n");
	printf("\n\t1. CONFIRM \t2. CANCEL\n");
	scanf("%d", &confirm);
	printf("Option: ");

	if (confirm == 0) {
		exit(1);
	} else {
//		save_res(roomChoice);
	}
}
/**
void save_res(int roomChoice) {
	// Grab the id
	reservation[roomChoice].id = record[roomChoice].id;

	// Grab the roomname
	strncpy(reservation[roomChoice].name, record[roomChoice].name, ROOMNAME);

	// Adding start time
	// Followed example for time from here: http://stackoverflow.com/questions/11428014/c-validation-in-strptime
	struct tm dtm={0};
	char DATEBUF[]="2014/01/01 00:00";
	
	char start[1024];
	time_t start_t;

	puts("Start time reservation:");
	fputs("\tEnter Date 'YYYY/MM/DD HH:MM' : ",stdout);
	fgets(start, sizeof(DATEBUF), stdin);
	strptime(DATEBUF, "%Y/%m/%d %H:%M", &dtm);
	// if the strings before and after mktime do not match, then we know the input string was not a valid date;
	start_t = mktime(&dtm); 	

	
	printf("---------------------------------------------");
	
	// Adding end time
	char end[1024];
	time_t end_t;

	puts("End time for reservation:");
	fputs("\tEnter Date 'YYYY/MM/DD HH:MM' : ",stdout);
	fgets(end, sizeof(DATEBUF), stdin);
	strptime(DATEBUF, "%Y/%m/%d %H:%M", &dtm);
	// if the strings before and after mktime do not match, then we know the input string was not a valid date;
	end_t = mktime(&dtm); 	

	// Error checking dates and times
	if (valid_date(start,end)) {
		puts("Valid Date...");

		// Store start and end date
		reservation[roomChoice].start_t = start;
		reservation[roomChoice].end_t = end;
	}

	// Adding event description
	char event_desc[ROOMDESC];
	fputs("Event Description:\n", stdout);
	fgets(event_desc, ROOMDESC, stdin);
	strncpy(reservation[roomChoice].desc, event_desc, ROOMDESC);
}**/

void valid_time(time_t start_t, time_t end_t) {
	if (start_t > end_t) {
		fputs("Start time cannot be greater than end time.\n", stderr);
		exit(0);
	}
}