#include <string.h>

#include "swcutils.h"

void query_word(const char* const query, FILE* fp) {
	char* breadcrumb;
	const int BUFLEN=1024;
	char buffer[BUFLEN];
	
	size_t location = 0;
	
	while( fgets(buffer, BUFLEN, stdin) && !feof(stdin) ) {
		size_t thisline_was = strlen(buffer);
        char* theArg = buffer;
        char* token;

        while( (token = strtok_r(theArg, " \t\n", &breadcrumb)) ) {
        	if (strcmp(query,token)) {
        	    	printf("%u\n", token, (token-buffer)+location);
        	}
        	theArg=NULL; 
        }
        location += thisline_was;
     }  
}
