#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum { MAX = 100 };

typedef struct board {
  char current[MAX][MAX];
  char next[MAX][MAX];
  int size;
} board;

// Returns the number of 'alive' cells there are
int getSize(board b);
// Creates a next arrangement based on the current arrangement
board update(board b);
// 'next' gets moved to 'current' and then updated
board next(board b);
// prints out current board
void printCurrent(board b);
// prints out next board
void printNext(board b);
// returns true if cell is live
_Bool isLive(char cell);
// returns number of live adjacent cells
int getAdjacent(board b, int n, int m);


int getSize(board b) {
	return (b.size);
}

_Bool isLive(char cell) {
	char *hash = "#";
	if (strcmp(&cell, hash) == 0) {
		return 1;
	} else {
		return 0; 
	}
}

board next(board b) {
	for (int i = 0; i < getSize(b)-1; i++) {
		for (int j = 0; j < getSize(b)-1; j++) {
			strcpy(&b.current[i][j], &b.next[i][j]);
		}
	}
	return b;
}

// if b.current[i][j] is live and adjacent = 2 or 3, b.next = live
// if b.current[i][j] is dead and adjacent = 3, b.next = live
// else dead 
board update(board b) {
	for (int i = 0; i < getSize(b)-1; i++) {
		for (int j = 0; j < getSize(b)-1; j++) {
			if (isLive(b.current[i][j])) {
				int adj = getAdjacent(b, i, j);
				if (adj == 2 || adj == 3) {
					strcpy(&b.next[i][j], "#");
				} else {
					strcpy(&b.next[i][j], ".");
				}
			} else {
				int adj = getAdjacent(b, i, j);
				if (adj == 3) {
					strcpy(&b.next[i][j], "#");
				} else {
					strcpy(&b.next[i][j], ".");
				}
			}
		}
	}
	return b;
}

int getAdjacent(board b, int n, int m) {
	int counter = 0, x, y;
	for (int i = (-1); i < 2; i++) {
		for (int j = (-1); j < 2; j++) {
			x = n + i;
			y = m + j;
			if (isLive(b.current[x][y])) {
				printf(""); // not really sure why but the code only work if this blank print statement is here
				if ((x != n) || (y != m)) {
					counter++;
				}
			}
		}
	}
	return counter;
}

void printCurrent(board b) {
	for (int n = 0; n < getSize(b)-1; n++) {
		for (int m = 0; m < getSize(b)-1; m++) {
			printf("%c", b.current[n][m]);
		}
		printf("\n");
	}
}

void printNext(board b) {
	for (int n = 0; n < getSize(b)-1; n++) {
		for (int m = 0; m < getSize(b)-1; m++) {
			printf("%c", b.next[n][m]);
		}
		printf("\n");
	}
}

// initialises game of life. Takes input colony and stores it in a 'board', updates it and prints the version at the next tick
int main(int n, char *args[n]) {
	if (n == 2) {
		int x, i = 0, j = 0;;
		printf("Enter n:\n");
		scanf("%d", &x);
		printf("Enter pattern (press ctrl+d to terminate pattern): \n");
		board b;
		b.size = 0;
		while (! feof(stdin)) {
			fgets(&b.current[i][j], MAX, stdin);
			b.size++;
			if (i < MAX) {
				i++;
			}
		}
		printf("\n");
		for (int i = 0; i < x; i++) {
			b = update(b);
			printf("N: %d\n", i);
			printNext(b);
			printf("\n");
			b = next(b);
		}
		printf("Final: \n");
		printNext(b);
	} else {
		int i = 0, j = 0;
		board b;
		b.size = 0;
		while (! feof(stdin)) {
			fgets(&b.current[i][j], MAX, stdin);
			b.size++;
			if (i < MAX) {
				i++;
			}
		}
		b = update(b);
		printNext(b);
		char input, nl;
	}
	return 0;
}
