/*
 * Maria Deslis
 * Fall 2014 - Hellman
 * Linx Programming
 * Sample 1
 */
#include <stdio.h>
#include <math.h>
#include <cstdlib>

void diamondTop(int width, char sym);

int main() {
	int n;
	char symbol;

	printf("%s","Enter a width: ");
	scanf("%i", &n);
	printf("%s","Enter a char: ");
	scanf("%s", &symbol);

	diamondTop(n,symbol);

	return 0;
}

void diamondTop(int width, char sym) {
	for (int row = 0; row <= width; row+=2) {
		printf("|");
		for (int spaces = 0; spaces < abs((width/2)-(row/2)); spaces++) {
			printf(" ");
		}
		for (int c = 0; c < (width-abs(width-row)); c++) {
			printf("%s", &sym);
		}
	}
	printf("|\n");
}
