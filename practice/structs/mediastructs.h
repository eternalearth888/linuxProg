#ifndef STRUCTS_H
#define STRUCTS_H

#define MEDIABUF 1024

const int MEDIABUF = 1024;

/** WAY 1**/
struct media {
	char title[MEDIABUF];
	char author[MEDIABUF];
	int pubyear;
	char genre[MEDIABUF];
	double ranking;
}

/**WAY 1.5**/
Mediadef struct media MusicMedia;
Mediadef struct media BookMedia;
Mediadef struct media MovieMedia;

#endif
