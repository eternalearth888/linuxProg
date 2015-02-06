#ifndef STRUCTS_H
#define STRUCTS_H

#define ROOMNAME 48

struct room {
	int id;
	char name[ROOMNAME];
	time_t start;
	time_t end;
	char desc[140];
};

#endif
