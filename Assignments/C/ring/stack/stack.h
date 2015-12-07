/* Stacks, implemented as linked lists. Nodes are re-used, so all the functions
run in O(1) time. Illegal operations cause the program to crash. */
#include <stdbool.h>

// The type of items stored in stacks.  Uncomment and adapt one of the
// following for doubles, ints, fixed size strings, variable strings as
// pointers, structures, or pointers to structures.
typedef double item;
// typedef int item;
// typedef char *item;
// typedef struct x item;
// typedef struct x *item;

// The type of a stack.  Only the stack module has access to the details.
struct stack; 
typedef struct stack stack;

// Create a new empty stack of items.
stack *new_stack();

// Push an item onto the top of a stack.
void push(stack *s, item x);

// Pop an item from the top of a non-empty stack.
item pop(stack *s);

// Get the top item from a non-empty stack without removing it.
item top(stack *s);

// Check whether a stack is empty.
bool is_empty(stack *s);
