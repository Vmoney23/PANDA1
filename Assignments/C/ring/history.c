#include "ring.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

void loadRing(ring *r) {
	insertBefore(r, "http://www.google.com");
	insertBefore(r, "https://www.google.co.uk/?gfe_rd=cr&ei=58RkVqCSEITP0wWvzrPQDg#q=what%20is%20computer%20science");
	shiftBackward(r);
	insertBefore(r, "http://www.bbc.co.uk/guides/zxgdwmn");
	shiftBackward(r);
	insertBefore(r, "https://www.google.co.uk/?gfe_rd=cr&ei=58RkVqCSEITP0wWvzrPQDg#q=what%20is%20computer%20science");
	shiftBackward(r);
	insertBefore(r, "https://www.google.co.uk/?gfe_rd=cr&ei=58RkVqCSEITP0wWvzrPQDg#q=university+of+bristol+computer+science");
	shiftBackward(r);
	insertBefore(r, "https://www.cs.bris.ac.uk/Teaching/");
	shiftBackward(r);
	insertBefore(r, "https://www.cs.bris.ac.uk/Teaching/yearpage.jsp?stage=1");
	shiftBackward(r);
	insertBefore(r, "https://www.cs.bris.ac.uk/Teaching/");
	shiftBackward(r);
	insertBefore(r, "https://www.google.co.uk/?gfe_rd=cr&ei=58RkVqCSEITP0wWvzrPQDg#q=university+of+bristol+computer+science");
	shiftBackward(r);
	insertBefore(r, "http://www.cs.bris.ac.uk/");
	shiftBackward(r);
	insertBefore(r, "https://www.cs.bris.ac.uk/ugadmissions/");
	shiftBackward(r);
	insertBefore(r, "https://www.cs.bris.ac.uk/ugadmissions/whyBristol/");
	shiftBackward(r);
	insertBefore(r, "https://www.cs.bris.ac.uk/ugadmissions/howToApply/");
	shiftBackward(r);
	insertBefore(r, "https://www.cs.bris.ac.uk/People/");
	shiftBackward(r);
	insertBefore(r, "https://www.cs.bris.ac.uk/People/staff.jsp");
	shiftBackward(r);
	insertBefore(r, "https://www.cs.bris.ac.uk/People/personal.jsp?key=4196");
	shiftBackward(r);
	insertBefore(r, "http://www.cs.bris.ac.uk/~ian/");
	shiftBackward(r);
	insertBefore(r, "http://pastebin.com/SusF2063");
	setFirst(r);
}

int query(ring *r) {
	printf("What would you like to do?\n");
	printf("1 - View previous website\n");
	printf("2 - View next website\n");
	printf("3 - View latest website\n");
	printf("4 - View first website\n");
	printf("5 - Open current website\n");
	printf("6 - Remove from history\n");
	printf("7 - Quit\n");
	char option, nl;
	char link[120] = "open ";
	scanf("%c%c", &option, &nl);
	switch(option){
		case '1':
			shiftForward(r);
			printf("Previous:\n%s\n", getCurrent(r));
			return 1;
			break;
		case '2':
			shiftBackward(r);
			printf("Next:\n%s\n", getCurrent(r));
			return 1;
			break;
		case '3':
			setFirst(r);
			printf("Latest:\n%s\n", getCurrent(r));
			return 1;
			break;
		case '4':
			setLast(r);
			printf("First:\n%s\n", getCurrent(r));
			return 1;
			break;
		case '5':
			printf("Opening:\n%s\n", getCurrent(r));
			strcat(link, getCurrent(r));
			system(link);
			return 1;
			break;
		case '6':
			deleteCurrent(r);
			printf("Previous:\n%s\n", getCurrent(r));
			return 1;
			break;
		case '7':
			return 0;
			break;
		default:
			printf("Please enter a valid option!\n");
			return 1;
	}
}

int main() {
	ring *hist;
	hist = newRing();
	printf("Welcome to your browser history: \n");
	loadRing(hist);
	printf("Your last viewed website was:\n%s\n\n", getCurrent(hist));
	_Bool yes = 1;
	while (yes) {
		yes = query(hist);
	};
	return 0;
}
