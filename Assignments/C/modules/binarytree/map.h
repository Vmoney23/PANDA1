// typedef double item;
// typedef int item;
typedef char *item;
// typedef struct x item;
// typedef struct x *item;

// typedef double item2;
// typedef int item2;
typedef char *item2;
// typedef struct x item2;
// typedef struct x *item2;

struct tree;
typedef struct tree tree;

tree *newTree();
void insert(tree *t, item one, item2 two);
void getKey(tree *t, item name);
void editKey(tree *t, item one, item new);
int compareKey(item newKey, item currentkey);
int getCount(tree *t);
