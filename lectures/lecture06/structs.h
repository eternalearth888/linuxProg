#ifndef STRUCTS_H
#define STRUCTS_H

#define BOOKBUF 1024

/** WAY 1**/
struct book {
	char title[BOOKBUF];
	char author[BOOKBUF];
	int pubyear;
};

/**WAY 1.5**/
typedef struct book BookType;

/**WAY 2**/
typedef struct biography {
	char title[BOOKBUF];
	char author[BOOKBUF];
	int pubyear;
	char about[BOOKBUF];
}BiographyType;

struct book makebook(char *title, char* author, int pubyear);

struct BookType make_another_book(char *title, char* author, int pubyear);

#endif
