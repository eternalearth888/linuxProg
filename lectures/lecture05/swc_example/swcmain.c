#include <stdio.h>
#include <string.h>

#include "swcutils.h"

int main(int argc, char* argv[]) {

    if (argc > 1) {
		query_word(argv[1],stdin);
    }
  
	return 0;
}
