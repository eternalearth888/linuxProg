#include <stdio.h>
#include <string.h>

int main( int argc, char* argv[] ) { 

    
    char* breadcrumb;

    /**
    * int i = 0;
    * for (i = 0; i < argc; i++) {
    *   //printf("Arg %i value /%s/\n", i, argv[i]);
    *   char* theArg = argv[i];
    *   char* token;
	*
    *   while( (token=strtok_r(theArg, " \t", &breadcrumb)) ) {
    *   	printf("The next token is '%s'\n", token);
    *   	theArg=NULL; 
    *   }  
    *}   
	**/
	
	const int BUFLEN=1024;
	char buffer[BUFLEN];
	
	// stdin==cin, stdout==cout, stderr=cerr
	while( fgets(buffer, BUFLEN, stdin) && !feof(stdin) ) {
        char* theArg = buffer;
        char* token;

        while( (token = strtok_r(theArg, " \t\n", &breadcrumb)) ) {
        	printf("The next token is '%s'\n", token);
        	theArg='\0'; 
        }  
     }  
  
    return 0;
}

/**
*
* Using "strtok" and command line arguments
* 
* Prints out each value of the argv to the console with corresponding argument
* 
* 
* 
* RESULTS:
* ====================
* 
* $ gcc strTok.c
* $ ./a.out A B "ABCD    XYZ" "         "
* Arg 0 value /./a.out/
* Arg 1 value /A/
* Arg 2 value /B/
* Arg 3 value /ABCD    XYZ/
* Arg 4 value /         /
* 
**/
