/*
 * Maria Deslis
 * Fall 2014 - Hellman
 * Linx Programming
 * Sample 1
 */
#include <stdio.h>
#include <math.h>
#include <cstdlib>

void diamondT(int width);
void diamondB(int width);
void printSpace(int num);

int main() {
	int n;
	char symbol;

	printf("%s","Enter a width: ");
	scanf("%i", &n);
//	printf("%s","Enter a char: ");
//	scanf("%s", &symbol);

	diamondT(n);
	diamondB(n);

	return 0;
}

void diamondT(int width) {
	int space = width-1;

	for (int row = 1; row <= width; row++) {
		printf("%s","|");
		printSpace(space);
		for (int col = 1; col <= (2*row-1); col++) {
			putchar('*');
		}
		printSpace(space);
		printf("%s","|\n");
		space--;
	}

}

void diamondB(int width) {
	int space = 1;

	for (int row = 1; row <= width-1; row++) {
		printf("%s","|");
		printSpace(space);
		for (int col = 0; col < (2*(width-row)-1); col++) {
			putchar('*');
		}
		printSpace(space);
		printf("%s","|\n");
		space++;
	}
}

void printSpace(int num) {
		if (num > 0) {
			for (int i = 0; i < num; i++) {
				putchar(' ');
			}
		}
}
