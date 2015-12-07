#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct tree {
    struct node *root;
    int count;
};

struct node {
	struct node *l;
	item key;
	item2 number;
	struct node *r;
};
typedef struct node node;

tree *newTree() {
    tree *t = malloc(sizeof(tree));
    t->root = NULL;
    t->count = 0;
    return t;
}

node *newNode(item key, item2 number) {
    node *n = malloc(sizeof(node));
    *n = (node) { NULL, key, number, NULL };
    return n;
}

node *insertNode(node *n, item key, item2 number) {
    if (n == NULL) {
    	n = newNode(key, number);
    } else if (key < n->key) {
        n->l = insertNode(n->l, key, number);
    } else if (key > n->key) {
        n->r = insertNode(n->r, key, number);
    }
    return n;
}

node *findNode(node *n, item key) {
    if (n == NULL) {}
    else if (compareKey(key, n->key) < 0) {
        n = findNode(n->l, key);
    } else if (compareKey(key, n->key) > 0) {
        n = findNode(n->r, key);
    }
    return n;
}

void insert(tree *t, item key, item2 number) {
    t->root = insertNode(t->root, key, number);
    t->count++;
}

int compareKey(item newkey, item currentkey) {
	return strcmp(newkey, currentkey); 
}

void getKey(tree *t, item key) {
	if(findNode(t->root, key) == NULL) {
		printf("No such contact!\n");
	} else {
		node *this;
		this = findNode(t->root, key);
		printf("Here is %s's number: %s\n", key, this->number);
	}
}

void editKey(tree *t, item key, item newNumber) {
	if(findNode(t->root, key) == NULL) {
		printf("No such contact!\n");
	} else {
		node *this;
		this = findNode(t->root, key);
		this->number = newNumber;
	}
}

int getCount(tree *t) {
	return (t->count);
}
