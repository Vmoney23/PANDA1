#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

void add(tree *t) {
	char nl, name[20], number[20];
	printf("Please enter the full name of the contact you are adding:\n");
	scanf("%s%c", &name, &nl);
	printf("Please enter their phone number:\n");
	scanf("%s%c", &number, &nl);
	insert(t, name, number);
}

void find(tree *t) {
	char nl, name[20];
	printf("Please enter the name of the contact you are trying to find:\n");
	scanf("%s%c", &name, &nl);
	getKey(t, name);
}

void update(tree *t) {
	char nl, name[20], number[20];
	printf("Please enter the of the contact you want to update:\n");
	scanf("%s%c", &name, &nl);
	printf("Please enter the new number:\n");
	scanf("%s%c", &number, &nl);
	editKey(t, name, number);
	printf("%s successfully updated\n", name);
}

int query(tree *t) {
	char option, nl;
	printf("Please select an option from below:\n");
	printf("1 - Add contact\n");
	printf("2 - Find contact\n");
	printf("3 - Update contact\n");
	printf("4 - Quit\n");
	scanf("%c%c", &option, &nl);
	switch(option) {
		case '1':
			add(t);
			printf("You now have %d contact(s)\n", getCount(t));
			return 1;
			break;
		case '2':
			find(t);
			return 1;
			break;
		case '3':
			update(t);
			return 1;
			break;
		case '4':
			return 0;
			break;
		default :
			printf("Please enter a valid option!\n");
			return 1;
			break;
	}
}

int main() {
	tree *t = newTree();
	_Bool loop = 1;
	while (loop == 1) {
		loop = query(t);
	}
	return 0;
}
