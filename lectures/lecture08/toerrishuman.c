/*
	$ gcc toerrishuman.c -std=c99 -D_GNU_SOURCE
	$ ./a.out
*/
#include <stdio.h>
#include <unistd.h> //for chdir
#include <string.h>
#include <errno.h>
/**************************************/
//#define MYERR(fp,op) myerror(fp, __FUNCTION__,op)
#define MYERR(fp,...) myerror(fp, __FUNCTION__, __VA_ARGS__ "")

#define BUFFLEN 1024

void myerror(FILE* fp, const char* functionname, const char* op) {
	char errbuff[BUFFLEN];
	char* es = strerror_r(errno, errbuff, BUFFLEN); 
	if(strlen(op)) {
		fprintf(fp, "%s (%s): %s\n", functionname, op, es);
	} else {
		fprintf(fp, "%s: %s\n", functionname, es);
	}
}

// void in parameters is good practice without parameters
// WHY? Explicitly states, this argument takes no parameters
void show_errno( void ) {
	printf("ERRNO: %d\n", errno);
}

void testerror(void) {
	if (chdir("/does/not/exist")) {
		MYERR(stderr, "chdir dne");
	}
}

int main(int argc, char* argv[]) {

	FILE* fp = fopen("/etc/passwd", "w");
	
	if (!fp) {
		/*
		puts("Shucks, couldn't write /etc/passwd");
		show_errno();
		perror("main (write /etc/passwd)");
		perror("NULL");
		perror("");
		*/
		MYERR(stderr,"");
		
	}
	
	show_errno();
	testerror();
	show_errno();
	
	/*
	show_errno();
	if(chdir("/does/not/exist")){
		// myerror(stderr,__FUNCTION__,"chdir dne");		
		//__FUNCTION__ always resolves to current function we are in
		MYERR(stderr, "chdir dne");
	}
	
	
	show_errno();
	if (chdir("..")) {
		perror("main (chdir dne)");
	}	

	show_errno();
	*/
	
	return 0;
}
