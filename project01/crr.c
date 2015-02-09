#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "crr.h"

/**FUNCTION DECLARATIONS**/
struct reservation_array *db;

// Completed functions in order of completion
void print_mainMenu();
void print_confMenu();
int countRoom(FILE *in);
struct room *fill_struct(FILE *in, int num);
void view_available(struct room *record, int num);
int valid_date(time_t start_t, time_t end_t);
time_t convertGMT(time_t time);
time_t convertLocal(time_t time);

// Incompleted
void create_reservation(struct room *record, int roomChoice);
void insert_reservation(struct reservation record);

/**MAIN PROGRAM**/

int main(int argc, char* argv[]) {
	// First error check for the correct number of arguments
	// Must have at least : $ ./executable rooms.dat schedule.dat
	if (argc < 2) {
		fputs("Not enough ARGS.\n", stderr);
		return 1;
	}

	db = malloc(sizeof(struct reservation_array*));

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

	// Initializing max length for reservation_array
	db->numElements = 0;
	db->maxlength_numElements = 0;

	// Fill room struct with id and names
	struct room *create_room = fill_struct(ifp, numRoom);

	
	print_mainMenu();
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
	//fclose(ofp);
	free(create_room);

	return 0;
}

/**COMPLETED FUNCTIONS**/
void print_mainMenu() {
	printf("Menu:\n");
	printf("---------------------------------------------\n");
	printf("\t1. View Available Rooms\n");
	printf("\t2. View Reservations On Specific Date\n");
	printf("\t3. View Specific Room\n");
	printf("\t4. Search Event\n");
	printf("\t5. Save Changes to File\n");
	printf("\t0. To Quit\n");
	printf("---------------------------------------------\n");
	printf("Option: ");
}

void print_confMenu() {
	printf("---------------------------------------------\n");
	printf("Are you sure?\n");
	printf("\n\t1. CONFIRM \t2. CANCEL\n");
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

	//Start at the beginning of the file now that we have reached the end
	fseek(in, 0, SEEK_SET);


	return record_room;
}

void print_roomStruct(struct room *record, int num) {
	for (int j = 0; j < num; j++) {
		printf("\t%i:%s\n", record[j].id, record[j].name);
	}
}

void view_available(struct room *record, int num) {
	// Print Num Rooms
	//printf("Num Rooms: %i\n",num);

	printf("Available Rooms:\n");
	print_roomStruct(record, num);

	//User room choice for reservation 
	int roomChoice;
	int confirm;
	
	printf("\nCHOOSE ROOM NUMBER: ");
	scanf("%d", &roomChoice);
	print_confMenu();
	scanf("%i", &confirm);

	if (confirm == 1) {
		create_reservation(record, roomChoice);
	} else if (confirm == 2) {
		exit(0);
	}
}

int valid_date(time_t start_t, time_t end_t) {
	if (start_t > end_t) { 
		fputs("Start time cannot be greater than end time.\n", stderr);
		return 1;
	}
	return 0;
}

//REQ11
time_t convertGMT(time_t time) {
	struct tm *zone;
	time = timegm(zone);

	return time;
}

time_t convertLocal(time_t time) {
	struct tm *zone;
	time = timelocal(zone);

	return time;
}

/**CURRENT FUNCTIONS**/

void create_reservation(struct room* record, int roomChoice) {
	struct reservation create_res;



	// Grab the id
	create_res.id = record[roomChoice].id;

	// Grab the roomname
	strncpy(create_res.name, record[roomChoice].name, ROOMNAME);

	// Adding start time
	// Followed example for time from here: http://stackoverflow.com/questions/11428014/c-validation-in-strptime
	struct tm dtm={0};
	char DATEBUF[]="2014/01/01 00:00";
	
	char start[1024];
	time_t start_t;
	fgets(start, sizeof(DATEBUF), stdin);
	puts("Start time reservation:");
	fputs("\tEnter Date 'YYYY/MM/DD HH:MM' : ",stdout);
	fgets(start, sizeof(DATEBUF), stdin);
	fflush(stdout);
	strptime(DATEBUF, "%Y/%m/%d %H:%M", &dtm);
	// if the strings before and after mktime do not match, then we know the input string was not a valid date;
	start_t = mktime(&dtm); 	
	
	// Adding end time
	char end[1024];
	time_t end_t;
	puts("End time for reservation:");
	fputs("\tEnter Date 'YYYY/MM/DD HH:MM' : ",stdout);
	fgets(end, sizeof(DATEBUF), stdin);
	fflush(stdout);
	strptime(DATEBUF, "%Y/%m/%d %H:%M", &dtm);
	// if the strings before and after mktime do not match, then we know the input string was not a valid date;
	end_t = mktime(&dtm); 	

	// Error checking dates and times
	if (valid_date(start_t,end_t) == 0) {
		puts("Valid Date...");

		// Store start and end date now that they have been validated
		// Store them as localtime --> gmt
		create_res.start = convertGMT(start_t);
		create_res.end = convertGMT(end_t);
	}

	// Adding event description
	char event_desc[ROOMDESC];
	fputs("Event Description:\n", stdout);
	fgets(event_desc, ROOMDESC, stdin);
	fflush(stdout);
	strncpy(create_res.desc, event_desc, ROOMDESC);

	int confirm;
	print_confMenu();
	scanf("%i", &confirm);

	
	if (confirm == 1) {
		insert_reservation(create_res);
	} else if (confirm == 2) {
		exit(0);
	}
}

void insert_reservation(struct reservation record) {
	if (db->maxlength_numElements > 0){

		db->record[db->numElements] = record;
		db->numElements++;
	} else {
		// Only occurs on the first
		db->record = malloc(1024*sizeof(struct reservation));
		db->maxlength_numElements=1024;

		// NOTE
		db->record[db->numElements].id = record.id;
		strncpy(db->record[db->numElements].name, record.name, ROOMNAME);
		db->record[db->numElements].start = record.start;
		db->record[db->numElements].end = record.end;
		strncpy(db->record[db->numElements].desc, record.desc, ROOMDESC);

		db->numElements++;
	}
}