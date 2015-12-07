#include "ring.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	item data;
	struct node *next;
	struct node *prev;
};
typedef struct node node;

struct ring {
	// node *first;
	// node *last;
	node *current;
	node *sentinel;
	int count;
};

// Create new ring structure
ring *newRing() {
	ring *r = malloc(sizeof(ring));
	node *n = malloc(sizeof(node));
	n->next = n->prev = n;
	r->sentinel = n;
	r->sentinel->next = r->sentinel->prev = n;
	r->count = 0;
	return r;
}

// Set current to first 
void setFirst(ring *r) {
	r->current = r->sentinel->next;
}

// Set current to last 
void setLast(ring *r) {
	r->current = r->sentinel->prev;
}

// Insert new before current
void insertBefore(ring *r, item x) {
	node *newNode;
	newNode = malloc(sizeof(node));
	newNode->data = x;
	if (isEmpty(r)){
		newNode->next = r->sentinel;
		newNode->prev = r->sentinel;
		r->sentinel->next = r->sentinel->prev = r->current = newNode;
	} else {
		newNode->next = r->current;
		newNode->prev = r->current->prev;
		r->current->prev = newNode;
		if (r->sentinel->next == r->current) {
			r->sentinel->next = newNode;
		}
	}
	r->count++;
}

// Insert new after current
void insertAfter(ring *r, item x) {
	node *newNode;
	newNode = malloc(sizeof(node));
	newNode->data = x;
	if (isEmpty(r)){
		newNode->next = r->sentinel;
		newNode->prev = r->sentinel;
		r->sentinel->next = r->sentinel->prev = r->current = newNode;
	} else {
		newNode->next = r->current->next;
		newNode->prev = r->current;
		r->current->next = newNode;
		if (r->sentinel->prev == r->current) {
			r->sentinel->prev = newNode;
		}
	}
	r->count++;
}

// Get data from current
item getCurrent(ring *r) {
	return (r->current->data);
}

// Shift current forward
void shiftForward(ring *r) {
	if (r->current->next != r->sentinel) {
	r->current = r->current->next;
	} else {
		r->current = r->sentinel->next;
	}

}

// Shift current backward
void shiftBackward(ring *r) {
	if (r->current->prev != r->sentinel) {
	r->current = r->current->prev;
	} else {
		r->current = r->sentinel->prev;
	}
}

// Delete current
void deleteCurrent(ring *r) {
	if (r->current == r->sentinel) {
		printf("Can't delete the sentinel node!\n");
	}
	else {
		node *nodeP = r->current->prev;
		node *nodeN = r->current->next;
		if (nodeN == r->sentinel) {
			r->current->prev->next = r->sentinel;
			r->sentinel->prev = nodeP;
			r->current = r->sentinel->next;
			r->current->prev = r->sentinel;
			r->current->next = r->sentinel->next->next;
		} else if (nodeP == r->sentinel) {
			r->sentinel->next = nodeN;
			r->current->next->prev = r->sentinel;
			r->current = nodeN;
			r->current->prev = r->sentinel;
			r->current->next = nodeN->next;
		} else {
			r->current->prev->next = nodeN;
			r->current->next->prev = nodeP;
			r->current = nodeN;
			r->current->prev = nodeP;
			r->current->next = nodeN->next;
		}
	}
}

// Check if ring is empty
bool isEmpty(ring *r) {
	if (r->count == 0) {
		return true;
	} else {
		return false;
	}
}
