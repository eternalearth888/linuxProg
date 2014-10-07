#include <stdio.h>
#include <string.h>

int main( int argc, char* argv[] ) { 

    
    char* breadcrumb;
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
