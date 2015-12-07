#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct tree {
	struct node *root;
};

struct node {
	struct node *left;
	item key;
	item2 number;
	struct node *right;
};
typedef struct node node;

tree *newTree() {
    tree *t = malloc(sizeof(tree));
    t->root = NULL;
    return t;
}

node *findNode(node *p, item n) {
    if (p == NULL) {}
    else if (compare(n, p->key) < 0) {
        p = findNode(p->left, n);
  	} else if (compare(n, p->key) > 0) {
        p = findNode(p->right, n);
  	}
    return p;
}

node *newNode(item key, item2 number) {
    node *p = malloc(sizeof(node));
    *p = (node) { NULL, key, number, NULL };
    return p;
}

node *insertNode(node *p, item key, item2 number) {
    if (p == NULL)  {
      p = newNode(key, number);
    } else if (key < p->key) {
        p->left = insertNode(p->left, key, number);
    } else if (key > p->key) {
        p->right = insertNode(p->right, key, number);
    }
    return p;
}

void insert(tree *t, item key, item2 number) {
  	t->root = insertNode(t->root, key, number);
}

void getNumber(tree *t, item key) {
  if (findNode(t->root, key) == NULL) {
    printf("No such contact\n");
  }
  else {
    node *this;
    this = findNode(t->root, key);
    printf("Number: %s\n", this->number);
  }
}

void editNumber(tree *t, item key, item newNumber) {
  if(findNode(t->root, key) == NULL) {
    printf("NULL.\nThis name does not exist.\n");
  }
  else {
    node *this;
    this = findNode(t->root, key);
    this->number = newNumber;
  }
}
