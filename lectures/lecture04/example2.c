/**
 *	Usage: Word at dictionary name offset
 *
 * 	Displays the word at offset in the fiile dictionary name,
 *	or nothing if the character at offset is '\n'
 	Offset being bytes. Begins at offset 0 ... n+1 (file length)
 * 
 **/

#include <stdio.h>

int main (int argc, char *argv[]) {

	//Remember where we are in the file
	long myoffset = 0;
	long theiroffset = 0;
	
	FILE* fp;
	char buffer[1024];

	// First check to see if there are two arguments
	if ( argc < 3 ) {
		fputs("Not enough ARGS.\n", stderr);
		return 1;
	}
	
	if ( (fp = fopen(argv[1], "r")) == NULL ) {
		fprintf(stderr, "Cannot open '%s'\n", argv[1]);
		return 1;
	}
	
	if ( (sscanf(argv[2], "%li", &myoffset)) != 1 ) {
		fprintf(stderr, "%s is an invalid offset.\n", argv[2]);
		return 1;
	}
	
	while( myoffset < theiroffset ) {
		fgets(buffer, 1024, fp);
		myoffset += strlen(buffer);
	}

	fclose(fp);
	

	return 0;
}
