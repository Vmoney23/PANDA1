#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// typedef double item;
// typedef int item;
typedef char *item;
// typedef struct x item;
// typedef struct x *item;

struct ring;
typedef struct ring ring;

// Create new ring structure
ring *newRing();
// Set current to first 
void setFirst(ring *r);
// Set current to last 
void setLast(ring *r);
// Insert new before current
void insertBefore(ring *r, item x);
// Insert new after current
void insertAfter(ring *r, item x);
// Get data from current
item getCurrent(ring *r);
// Shift current forward
void shiftForward(ring *r);
// Shift current backward
void shiftBackward(ring *r);
// Delete current
void deleteCurrent(ring *r);
// Check if ring is empty
bool isEmpty(ring *r);
