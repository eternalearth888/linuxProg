#include <stdio.h>
#include <string.h>

int main( int argc, char* argv[] ) { 

	FILE* fp = stdout;
	
	for (int i = 1; i < argc; i++) {
	
		fprintf( fp, ">> fd %d <<", fileno(fp));
		fputs( argv[i], fp);
		fputs("\n", fp);
	
		if (i % 2 == 0) {
//				fprintf(stderr, ">> fd %d <<", fileno(stderr));
//				fputs("Even:\t", stderr);
//				fputs(argv[i], stderr);
//				fputs("\n", stderr);
				fp = stderr;
		} else {
//			fprintf(stdout, ">> fd %d <<", fileno(stdout));
//				fputs("Odd:\t",stdout);
//				fputs(argv[i], stdout);
//				fputs("\n", stdout);
				fp = stdout;
		}
	}
	fclose(fp);
	

	return 0;
}



/** NOTES:
 * 		fprintf(stdout, argv[c]) the c libary will interpret each one of the percents
 * 			as a format specifier. We don't want to do that. 
 *		
 *		Shift+K while on "thing" to learn in vim to see man page for stuff while coding
 *
 *		/usr/share/dict/words contains all words that Linux recognizes during spellcheck
 *			Guaranteed to end with a single new line
 *
 *
 *
**/
 

