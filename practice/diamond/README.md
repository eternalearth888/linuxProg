Make an application that does this:

$ ./diamond
Enter a char
*
Enter a width
8
$ echo $?
1
$ ./diamond
Enter a char
*
Enter a width
7
|   *   |
|  ***  |
| ***** |
|*******|
| ***** |
|  ***  |
|   *   |
$ echo $?
0
$ 
