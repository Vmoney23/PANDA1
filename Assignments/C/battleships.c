#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

struct board setupP();
struct board setupAI();
struct board position();
struct board check();
struct board newMove();
struct board move();
struct board AImove();
struct board AImissed();
bool won();
void display();

const char HIT = '*', MISS = 'O', BLANK = '~', SHIP = '+', P = 'P', AI = 'C';
time_t t = 0;

struct board {
    char cells[5][5];
    char player;
    int row, column;
    int hits, misses;
};

struct board newBoard(char player) {
	struct board b;
	b.player = player;
	for (int i = 0; i < 5; i++) {
		b.cells[i][0] = BLANK;
		b.cells[i][1] = BLANK;
		b.cells[i][2] = BLANK;
		b.cells[i][3] = BLANK;
		b.cells[i][4] = BLANK;
	}
	b.hits = 0;
	b.misses = 0;
	return b;
}

struct board setupP(struct board b){
	for (int i = 0; i<7; i++) {
		int row = rand() % 5;
		int col = rand() % 5;
		if (b.cells[row][col] == BLANK){
			b.cells[row][col] = SHIP;
		} else {
			i = i-1;
		}
	}
	return b;
}

struct board setupAI(struct board b) {
	for (int i = 0; i<7; i++) {
		int row = rand() % 5;
		int col = rand() % 5;
		if (b.cells[row][col] == BLANK){
			b.cells[row][col] = SHIP;
		} else {
			i = i-1;
		}
	}
	return b;
}

struct board position(struct board b, char *text) {
    if (text[0] == 'a') {
      b.row = 0;
    } else if (text[0] == 'b') {
      b.row = 1;
    } else if (text[0] == 'c') {
      b.row = 2;
    } else if (text[0] == 'd') {
      b.row = 3;
    } else if (text[0] == 'e') {
      b.row = 4;
    } else {
      b.row = -1;
      b.column = -1;
    }

    if (text[1] == '1') {
      b.column = 0;
    } else if (text[1] == '2') {
      b.column = 1;
    } else if (text[1] == '3') {
      b.column = 2;
    } else if (text[1] == '4') {
      b.column = 3;
    } else if (text[1] == '5') {
      b.column = 4;
    } else {
      b.row = -1;
      b.column = -1;
    }

    char null = '\0';
    if (text[2] != null) {
      b.row = -1;
      b.column = -1;
    }

    return b;
}

struct board check(struct board b) {
	if (b.cells[b.row][b.column] == SHIP) {
		b.cells[b.row][b.column] = HIT;
		printf("HIT!!\n");
		b.hits++;
	} else if (b.cells[b.row][b.column] == HIT) {
		printf("Already Hit\n");
		b = newMove(b);
		b = move(b);
	} else if (b.cells[b.row][b.column] == MISS) {
		printf("Already Missed\n");
		b = newMove(b);
		b = move(b);
	} else {
		b.cells[b.row][b.column] = MISS;
		printf("MISS!!\n");
		b.misses++;
	} 
	return b;
}

struct board newMove(struct board b) {
	char move[2];
	printf("Player, Please enter coordinates for your move: \n");
	scanf("%s", move);
	b = position(b, move);
	return b;
}

struct board move(struct board b) {
	if ((b.row != -1) && (b.column != -1)) {
    	return check(b);
    } else {
    	b = newMove(b);
    	return move(b);
    }
}

struct board AImove(struct board b) {
	int row = rand() % 5;
	int col = rand() % 5;
	if (b.cells[row][col] == SHIP) {
		b.cells[row][col] = HIT;
		printf("YOU GOT HIT!!\n");
		b.hits++;
	} else if (b.cells[row][col] == BLANK) {
		b.cells[row][col] = MISS;
		printf("AI MISSED!!\n");
		b.misses++;
	} else {
		b = AImissed(b);
	}
	return b;
}

struct board AImissed(struct board b) {
	return AImove(b);
}

bool won(struct board b) {
	if (b.hits == 7) {
		if (b.player == P) {
			printf("You Lose! Try again.\n");
		} else {
			printf("You Win! Congratulations!\n");
		}
		return true;
	} else {
		return false;
	}
}

void display(struct board b) {
	printf("%c\t1\t2\t3\t4\t5\n", b.player);
  for (int i=0; i < 5 ; i++){
    char *let;
    if (i == 0) {
      let = "a";
    } else if (i == 1) {
      let = "b";
    } else if (i == 2) {
      let = "c";
    } else if (i == 3) {
    	let = "d";
    } else {
    	let = "e";
    }
    printf("%c\t", *let);
    for (int j = 0; j < 5; j++){
    	if (b.player == P) {
    		printf("%c\t", b.cells[i][j]);
    	} else {
	    	if ((b.cells[i][j] == SHIP) || b.cells[i][j] == BLANK) {
	    		printf("~\t");
	    	} else {
	    		printf("%c\t", b.cells[i][j]);
	    	}
	    }
    }
    printf("\n");
  }
  printf("\n");
}

int main(){
	// Setup Boards
	srand((unsigned) time(&t));
	printf("Welcome to Battleships.\nIn this game, you will be playing against an 'AI'.\nYour goal is to hit all 7 of their ships before they hit yours.\nEach ship is of size 1, so there is no need to look for clusters of points,\nhowever as the board is randomly generated, you may find clusters\n");
	printf("Your board is board P, the computer's is C.\nTo enter a move, type in the row letter, and the column number (ie: a1)\n");
	struct board p;
	p = newBoard(P);
	p = setupP(p);
	struct board c;
	c = newBoard(AI);
	c = setupAI(c);
	display(c);
	display(p);
	do {
		c = newMove(c);
		c = move(c);
		display(c);
		p = AImove(p);
		display(p);
		printf("Your score: %d Hits, %d Misses\n", c.hits, c.misses);
		printf("AI's score: %d Hits, %d Misses\n", p.hits, p.misses);
	}
	while (won(p) != true && won(c) != true);
	return 0;
}