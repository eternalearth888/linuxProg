#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "crr.h"

/**FUNCTION DECLARATIONS**/
struct reservation_array *db;

// COMPLETED (IN ORDER OF COMPLETION)
void print_mainMenu();
void print_confMenu();
int countRoom(FILE *in);
struct room *fill_struct(FILE *in, int num);
void view_rooms(struct room *record, int num);
int valid_date(time_t start_t, time_t end_t);
time_t convertGMT(time_t time);
time_t convertLocal(time_t time);
void create_reservation(struct room *record, int roomChoice);
void insert_reservation(struct reservation record);

// IN PROGRESS
void save_changes(FILE *out, struct reservation_array *record, int argc, char* argv[]);
void view_reservations(FILE *out);
//void search_event(struct reservation_array *record);

/**MAIN PROGRAM**/

int main(int argc, char* argv[]) {
	// First error check for the correct number of arguments
	// Must have at least : $ ./executable rooms.dat schedule.dat
	if (argc < 3) {
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

	int choice;
	print_mainMenu();
	scanf("%i", &choice);
	while(choice != 0){	

		switch (choice) {
	//	review what rooms are available but not their schedule
	//		able to create a reservation however
			case 1:
				view_rooms(create_room, numRoom);
				break;
			case 2:
	//	search for a particular event based on a one-word (or subword) case-insensitive search of reservation descriptions, the interface should present all matching reservations in a menu so that one can be selected and deleted or changed
	//			view_reservationsDate();
				break;
			case 3:
	//	review the schedule for one room over all days (future looking, not historical), allowing them to delete or change a pre-existing reservation
	//			view_reseverationsOneRoom();
				break;
			case 4:
	//	search for a particular event based on a one-word (or subword) case-insensitive search of reservation descriptions, the interface should present all matching reservations in a menu so that one can be selected and deleted or changed
	//			search_event(db);
				break;
			case 5:
	// review all current reservations
				view_reservations(ofp);
				break;
			case 6:
				save_changes(ofp, db, argc, argv);
				break;
			default:
				printf("---------------------------------------------\n");
				printf("ERROR : Not a valid menu option. Try Again.\n");
				printf("---------------------------------------------\n");
				break;
		}
		print_mainMenu();
		scanf("%i", &choice);
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
	printf("\t5. View All Current Reservations\n");
	printf("\t6. Save Changes to File\n");
	printf("\t0. Quit (Changes are not saved!)\n");
	printf("---------------------------------------------\n");
	printf("Option: ");
}

void print_confMenu() {
	printf("---------------------------------------------\n");
	printf("ARE YOU SURE\n");
	printf("\n\t1. CONFIRM \t2. CANCEL\n");
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

void view_rooms(struct room *record, int num) {
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

/***************REQ11***************/
// Help from Krista Horn
time_t convertGMT(time_t time) {
	struct tm tm;
	localtime_r(&time, &tm);
	time = time - tm.tm_gmtoff;

	return time;
}

time_t convertLocal(time_t time) {
	struct tm tm;
	localtime_r(&time, &tm);
	time = time + tm.tm_gmtoff;

	return time;
}
/*************************************/

void create_reservation(struct room* record, int roomChoice) {
	struct reservation create_res;

	// Grab the id
	create_res.id = record[roomChoice].id;

	// Grab the roomname
	strncpy(create_res.name, record[roomChoice].name, ROOMNAME);

	// Adding start time
	// Followed example for time from here: http://stackoverflow.com/questions/11428014/c-validation-in-strptime
	char DATEBUF[] = "2014/01/01 00:00\n";

	struct tm stm = {0};
	char start[1024];
	time_t start_t;
	fgets(start, sizeof(DATEBUF), stdin);
	puts("Start time reservation:");
	fputs("\tEnter Date 'YYYY/MM/DD HH:MM' : ",stdout);
	fgets(start, sizeof(DATEBUF), stdin);
	fflush(stdout);
	strptime(start, "%n%Y/%m/%d%n%H:%M%n", &stm);
	// if the strings before and after mktime do not match, then we know the input string was not a valid date;
	start_t = mktime(&stm); 	
	
	// Adding end time
	struct tm etm = {0};
	char end[1024];
	time_t end_t;
	puts("End time for reservation:");
	fputs("\tEnter Date 'YYYY/MM/DD HH:MM' : ",stdout);
	fgets(end, sizeof(DATEBUF), stdin);
	fflush(stdout);
	strptime(end, "%n%Y/%m/%d%n%H:%M", &etm);
	// if the strings before and after mktime do not match, then we know the input string was not a valid date;
	end_t = mktime(&etm); 	

	// Error checking dates and times
	if (valid_date(start_t,end_t) == 0) {
		puts("\nValid Date...\n");

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


// Functions in progress
//REQ 10
void save_changes(FILE *out, struct reservation_array *record, int argc, char* argv[]) {
	int confirm;
	print_confMenu();
	scanf("%i", &confirm);

	if (confirm == 1) {
		fwrite(record->record, sizeof(struct reservation), record->numElements, out);
		fprintf(stdout, "\nCURRENT CHANGES SAVED : %s\n", argv[2]);
	} else if (confirm == 2) {
		exit(0);
	}
}

void view_reservations(FILE* out){
	// example from : http://www.linuxquestions.org/questions/programming-9/c-howto-read-binary-file-into-buffer-172985/
	struct reservation_array *buffer;
	int count;
	unsigned long length_file;
	// Get file length
	fseek(out, 0, SEEK_END);
	length_file=ftell(out);

	if ( (length_file%sizeof(struct reservation)) == 0) {
		count = length_file/sizeof(struct reservation);
	}

	fseek(out, 0, SEEK_SET);

	// Allocate memory
	buffer = (struct reservation_array*)malloc(length_file);
	buffer->record = (struct reservation*)malloc(length_file);

	if (!buffer) {
		fprintf(stderr, "ERROR: Could not allocate memory to buffer");
        fclose(out);
		exit(1);
	}

	//Read file contents into buffer
	fread(buffer->record, sizeof(struct reservation), count, out);
	printf("\nCurrent Reservations:\n");
	printf("\tID\tROOM NAME\tSTART TIME\tEND TIME\tDESCRIPTION\n");
	printf("--------------------------------------------------\n");
	for (int i = 0; i < count; i++) {
		printf("\t%i", buffer->record[i].id);
		printf("\t%s", buffer->record[i].name);
		printf("\t%lu", convertLocal(buffer->record[i].start));
		printf("\t%lu", convertLocal(buffer->record[i].end));
		printf("\t%s", buffer->record[i].desc);
	}
	
	fclose(out);
//	free(buffer);
}

/**
void search_event(struct reservation_array *record) {
	qsort(record, record->numElements, sizeof(struct reserve), string_cmpdesc)
}
**/