#include <string.h>
#include "structs.h"

struct media makemedia(char* title, char* author, int pubyear, char* genre, double ranking) {
	struct media newmedia;
	strncpy(newmedia.title, title, BOOKBUF);
	strncpy(newmedia.author, author, BOOKBUF);
	newmedia.pubyear = pubyear;
	return newmedia;
}

struct book* remakebook(struct book* oldbook, char* title, char* author, int pubyear, char* genre, double ranking) {
	strncpy(oldmedia->title, title, MEDIABUF);
	strncpy(oldmedia->author, author, MEDIABUF);
	oldmedia->pubyear = pubyear;
	return oldmedia;
}

void set_media_pubyear(struct media* media, int newyear) {
	if (newyear > 0) {
		media->pubyear = newyear;
	}
}
