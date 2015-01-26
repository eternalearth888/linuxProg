#ifndef STRUCTS_H
#define STRUCTS_H

#define ROOMBUF 1024

struct room {
	int id;
	char name[ROOMBUF];
	int startt;
	int endtt;
};

#endif
