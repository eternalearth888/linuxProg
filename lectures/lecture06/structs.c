#include <string.h>
#include "structs.h"
#include <stdio.h>

struct book makebook(char* title, char* author, int pubyear) {
	struct book newbook;
	strncpy(newbook.title, title, BOOKBUF);
	strncpy(newbook.author, author, BOOKBUF);
	newbook.pubyear = pubyear;
	return newbook;
}

struct book* remakebook(struct book* oldbook, char* title, char* author, int pubyear) {
	strncpy(oldbook->title, title, BOOKBUF);
	strncpy(oldbook->author, author, BOOKBUF);
	oldbook->pubyear = pubyear;
	return oldbook;
}

void set_book_pubyear(struct book*book, int newyear) {
	if (newyear > 0) {
		book->pubyear = newyear;
	}
}

int tmp[] = {1, 2, 3};

int main(int argc, char* argv[]) {

//	const int BOOKSHELF = 8;
	
	#define BOOKSHELF 8
	
	struct book book_shelf_1[] = { {"The C Language", "K&R", 1969}, {}, {"Harry Potter", "JK Rowling", 2001} };

	struct book book_shelf_2 = calloc(BOOKSHELF, sizeof(struct book));
	if (!book_shelf_2) {
		fputs("Help, I've fallen and lost my memory.(2)\n", stderr);
		return 1;
	}
	
	struct book book_shelf_3 = malloc(BOOKSHELF*sizeof(struct book));
	if (!book_shelf_3) {
		fputs("Help, I've fallen and lost my memory.(3)\n", stderr);
		return 1;
	}
	
	/** NOTES:
	struct book book_shelf_2[BOOKSHELF] = { {}, }; // remaining portion of array is zeroed out
	struct book book_shelf_3[BOOKSHELF];			// garbage because no initial values
	**/
	
	//realloc func changes the size of them me block pointed to by ptr to size bytes
	
	struct book* book_shelf_4 = realloc(book_shelf_3,BOOKSHELF*BOOKSHELF*sizeof(struct book));
	if (!book_shelf_4) {
		fputs("Help, I've fallen and lost my memory.(4)\n", stderr);
		return 1;
	}
	
	for (int i = 0; i < (sizeof(book_shelf_1)/sizeof(struct book)); i++) {
		printf("Book shelf 1, book %i\n", i);
		printf("Title: %s\n", book_shelf_1[i].title);
		printf("Author: %s\n", book_shelf_1[i].author);
		printf("Published: %i\n", book_shelf_1[i].pubyear);
		puts("");
	}
	
	free(book_shelf_2);
	free(book_shelf_3);
	free(book_shelf_4);
}
