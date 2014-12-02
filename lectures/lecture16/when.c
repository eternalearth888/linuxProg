/***
 * examples for date time coding
 */


#include <stdio.h>
#include <time.h>
#include <string.h>

#define BUFLEN 1024

/***
 * calendar time is a TIMESTAMP --- either time_t or struct tm
 */
time_t get_onesec_resolution( void )
{
	puts( __FUNCTION__ );

	time_t t;
	t = time( NULL ); // or time(&t);

	char buf[BUFLEN];
	// at least 26 bytes required (see manpage)
	ctime_r(&t,buf);
	
	fputs("The time() is ", stdout );
	fputs(buf, stdout);
	return t;
}

// try first without the stringerizer
#define LZDIFF_D( field )  printf( "%-10s local%8d  zulu%8d\n", #field, lzone->field, zulu->field )
#define LZDIFF_LD( field )  printf( "%-10s local%8ld  zulu%8ld\n", #field, lzone->field, zulu->field )
#define LZDIFF_S( field )  printf( "%-10s local%8s  zulu%8s\n", #field, lzone->field, zulu->field )
void set_broken_time( time_t t, struct tm* const lzone, struct tm* const zulu )
{
	puts( __FUNCTION__ );

	gmtime_r( &t, zulu );
	localtime_r( &t, lzone );

	LZDIFF_D( tm_sec ); 	 /// sec [0,60] for leap sec
	LZDIFF_D( tm_min ); 	 /// min
	LZDIFF_D( tm_hour ); 	 /// 24 hour time (index)
	LZDIFF_D( tm_mday ); 	 /// ORDINAL 
	LZDIFF_D( tm_mon ); 	 /// index since January=0
	LZDIFF_D( tm_year ); 	 /// index since 1900
	LZDIFF_D( tm_wday ); 	 /// index since Sunday=0
	LZDIFF_D( tm_yday ); 	 /// index since January 1=0
	LZDIFF_D( tm_isdst ); 	 /// is in DST  (1=in dst, 0=not in dsk, <0=use system config)
	LZDIFF_LD( tm_gmtoff );  /// number of seconds east of zulu when tm was valued, WITH isdst factored in
	LZDIFF_S( tm_zone );     /// tz name
}



void format_broken_time( struct tm t )
{
	puts( __FUNCTION__ );


	const char* fmts[] = { "%F", "%D", "%x", "%Z", "y %y m %m d %d sec %S", "%s" };
	const char* comments[] = { 
		"ISO 8601", 
		"\"Yecch-for Americans only...\" --- strftime(3)",
		"We must be Americans...",
		"Timezone identifier", 
		"ad hoc", 
		"Seconds since Jan 1 1970" };
	char buf[BUFLEN];
	for( int i=0; i<sizeof(fmts)/sizeof(char*); i++ ) {
		strftime(buf,BUFLEN,fmts[i],&t);
		printf( "fmt /%s/ value /%s/  /* %s */\n", fmts[i], buf, comments[i] );
	}
}


/***
 * convert local t to UTC t (zulu)
 *
 * NOTE:  the programmer never needs to know what actual timezone the program
 * is being executed in!  
 */
time_t to_zulu( time_t t ) 
{
	struct tm lzone;
	localtime_r( &t, &lzone);
	t -= lzone.tm_gmtoff;
	return t;
}

/** utility function */
char* truncate_at_newline( char* s ) 
{
	char *nl = strchr(s,'\n');
	if( nl ) *nl = '\0';
	return s;
}

void parse_times( )
{
	puts( __FUNCTION__ );

	struct tm broken_time;
	char buf[BUFLEN];
	char out[BUFLEN];
	fputs( "Enter YYYY/MM/DD HH:MM:SS, empty line to end: ", stdout );
	fflush(stdout);
	while( fgets( buf, BUFLEN, stdin ) && buf[0] != '\n' ) {
		/***
		 * CRITICAL!  otherwise tm_isdst affects the outcome!
		 */
		memset( &broken_time, '\0', sizeof(struct tm) );
		//broken_time.tm_isdst = -1;   // system specified --- you want this when reading input from user
		/***
		 * %n is any amount of whitespace,
		 * %Y is YYYYY
		 * %m, %d is oridinal month, day
		 * %H, %M, %S is seconds
		 */
		if( !strptime( buf, "%n%Y/%m/%d%n%H:%M:%S", &broken_time ) ) {
			fprintf( stderr, "Error parsing /%s/ w/ strptime\n", truncate_at_newline(buf) );
			continue;
		}
		// create a time_t
		time_t t = mktime(&broken_time);
		// format a time_t --- _r variant not gauranteed to "call" tzset (geesh)
		ctime_r( &t, out );
		truncate_at_newline(out);   // lob off newlines
		truncate_at_newline(buf);
		printf( "Read |%s|     from input |%s|\n", out, buf );

		t = to_zulu( t );
		ctime_r( &t, out );
		truncate_at_newline(out);   // lob off newline
		printf( "Read |%s UTC| from input |%s|\n", out, buf );

	}
}


/***
 * User I/O in localtime,
 * Storage in zulu!
 */
int main( int argc, char* argv[] ) 
{
	time_t t = get_onesec_resolution();
	struct tm local, zulu;

	set_broken_time( t, &local, &zulu );

	format_broken_time( local );

	/** see also getdate_r **/
	parse_times( );

	return 0;
}


