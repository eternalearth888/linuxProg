We are familiar with the venerable wc(1) utility.  We will write one 
with a slightly different flavor:  swc.

Specific Word Count
===================
swc defines a word to be any sequence of printable characters (not whitespace or 
control characters like '\r', '\f') bounded on the left side by the beginning of a line
or whitespace, and on the right side by whitespace or the end of a line ('\n').

usage:

     $ swc QUERY < /path/inputFile.lis

Prints out the in order sequence of offsets where the QUERY word exists on the
input stream.

Example
=======

If the file FOO consists of these three sentences:

  Long, long, time ago, I can still remember\n
  How UNIX used to make me smile...\n
  And I knew that with a login name\n
  That I could still play those UNIX games\n
  
  0    5    0    5    0    5    0    5    0    5
            1    1    2    2    3    3    4    4 

Then

  $ swc still < FOO
  28
  113
  $

Algorithm
=========
  1. Confirm 1 argument, remember QUERY
  2. Allocate a string buffer (char buffer[])
  3. In a loop, while not at the end of file:
    a. read a line, remember length
	b. print locations of QUERY using strtok_r
	c. update length
