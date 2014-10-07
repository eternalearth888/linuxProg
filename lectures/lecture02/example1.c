#include <stdio.h>
#include <string.h>

// argc = number of arguments
// argv = an array of charater pointers

int main(int argc, char* argv[]) {
	char aChar = 'a', anotherChar = '\n';
	
	// a string in C is just an array of characters
	char mud[] = "My name is mud";
	puts(mud);
	
	/* 
	* let's make a segFault! woohoo!
	* 
	* int i = 0;
	* while (1) {
	*	printf("The char at %d is value %d and character %c\n", i, mud[i], mud[i]);
	*	i++;
	* }
	*/
	
	// %lu : l = long, u = unsigned
	printf("The string is %lu bytes long?%s\n", strlen(mud), mud);
	
	// artificially terminated string at byte 11 with a character
	mud[11] = '\0';
	printf("The string is %lu bytes long?%s\n", strlen(mud), mud);
	
	mud[11] = 'M';
	printf("The string is %lu bytes long?%s\n", strlen(mud), mud);

	return 0;
}        

/*
 * MAN PAGES REVIEWED:
 *		strlen, strchr, strcmp, strstr, strcasecmp, strtok
 */
 


