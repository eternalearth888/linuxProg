#ifndef STRUCTS_H
#define STRUCTS_H

#define ROOMNAME 48
#define ROOMDESC 140

struct room {
	int id;
	char name[ROOMNAME];
};

struct reservation {
	int id;
	char name[ROOMNAME];
	time_t start;
	time_t end;
	char desc[ROOMDESC];
};

// 1 record of multiple reservations
struct reservation_array {
	int numElements;
	int maxlength_numElements;
	struct reservation *record;
};

#endif