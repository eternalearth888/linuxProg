#include <stdio.h>
#include <string.h>

#if 0
	HOW TO RUN ME: gcc example1.c -o example1
	$ ./example1 < unixsong.txt
	
#endif

// argc and argv is how we retrieve command line arguments
int main( int argc, char* argv[] ) { 
    
    char* breadcrumb;
	const int BUFLEN=1024;
	char buffer[BUFLEN];
	size_t location = 0;
	
	
	// stdin==cin, stdout==cout, stderr=cerr
	while( fgets(buffer, BUFLEN, stdin) && !feof(stdin) ) {
		size_t thisline_was = strlen(buffer);
		//size_t thistoken = location;
        char* theArg = buffer;
        char* token;

        while( (token = strtok_r(theArg, " \t\n", &breadcrumb)) ) {
        	printf("The next token is '%s'at %u\n", token, (token-buffer)+location);
        	theArg=NULL; 
        	
        	// +1 is assuming you are finding one white space between the tokens
        	//thistoken += strlen(token)+ 1;
        }  
        location += thisline_was;
     }  
  
    return 0;
}

#if 0

NOTES:
 -apropos displays where the manual pages exist
 
#endif
