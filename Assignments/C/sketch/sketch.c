#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "display.h"

struct state {
    int xcurr, ycurr, xold, yold;
    bool pen;
};

struct state newState() {
  struct state s;
  s.xcurr = 0;
  s.ycurr = 0;
  s.xold = 0;
  s.yold = 0;
  s.pen = false;
  // printf("State setup complete\n");
  return s;
}

struct state DX(display *d, int operand, struct state s) {
  // int operInt = operand;
  int xnew;
  xnew = s.xcurr + operand;
  if (s.pen == true) {
    line(d,s.xcurr,s.ycurr,xnew,s.ycurr);
    // printf("line(%d,%d,%d,%d)\n",s.xcurr,s.ycurr,xnew,s.ycurr);
    // printf("Drawing x:\t");
  }
  s.xold = s.xcurr;
  s.xcurr = xnew;
  // printf("Moved %d in x-direction, to %d\n", operInt, s.xcurr);
  return s;
}

struct state DY(display *d, int operand, struct state s) {
  // int operInt = operand;
  int ynew;
  ynew = s.ycurr + operand;
  if (s.pen == true) {
    line(d,s.xcurr,s.ycurr,s.xcurr,ynew);
    // printf("line(%d,%d,%d,%d)\n",s.xcurr,s.ycurr,s.xcurr,ynew);
    // printf("Drawing y:\t");
  }
  s.yold = s.ycurr;
  s.ycurr = ynew;
  // printf("Moved %d in y-direction, to %d\n", operInt, s.ycurr);
  return s;
}

struct state togglePen(struct state s) {
  if (s.pen == false) {
    s.pen = true;
    // printf("pen on\n");
  } else {
    s.pen = false;
    // printf("pen off\n");
  }
  return s;
}

int opCode (unsigned char o) {
  signed char res = (o >> 6);
  return res;
}

int signedOperand (unsigned char o) {
  signed char res = (o << 2);
  return (res >> 2);
}

int unsignedOperand (unsigned char o) {
  unsigned char res = o << 2;
    return (res >> 2);
}

void interpret(FILE *in, display *d, struct state s){
  int opcode, signOperand, unsignOperand;
  unsigned char b = fgetc(in);
  while (! feof(in)) {
    opcode = opCode(b);
    signOperand = signedOperand(b);
    unsignOperand = unsignedOperand(b);

    if (opcode == 0) {
      s = DX(d, signOperand, s);
      printf("0: %d\n", signOperand);
    } else if (opcode == 1) {
      s = DY(d, signOperand, s);
      printf("1: %d\n", signOperand);
    } else if (opcode == 3) {
      s = togglePen(s);
      printf("3: %d\n", signOperand);
    } else if (opcode == 2) {
      pause(d, unsignOperand);
      printf("2: %d\n", unsignOperand);
    }
    // printf("s state: x: %d, y: %d, pen: %d\n", s.xcurr, s.ycurr, s.pen);
    b = fgetc(in);
  }
}

// TODO: upgrade this function to read instructions from the file and obey them
void run(char *filename, bool testing) {
    FILE *in = fopen(filename, "rb");
    struct state s;
    s = newState();
    if (in == NULL) {
        printf("Can't open %s\n", filename);
        exit(1);
    }
    display *d = newDisplay(filename, 200, 200, testing);
    interpret(in,d,s);
    end(d);
    fclose(in);
    if (testing) printf("Sketch %s OK\n", filename);
}

// ----------------------------------------------------------------------------
// Nothing below this point needs to be changed.
// ----------------------------------------------------------------------------

void testSketches() {
    // Stage 1
    run("line.sketch", true);
    run("square.sketch", true);
    run("box.sketch", true);
    run("oxo.sketch", true);

    // Stage 2
    run("diag.sketch", true);
    run("cross.sketch", true);

    // Stage 3
    run("clear.sketch", true);
    run("key.sketch", true);

    // Stage 4
    run("pauses.sketch", true);
    run("field.sketch", true);
    run("lawn.sketch", true);
}

int main(int n, char *args[n]) {
    if (n == 1) testSketches();
    else if (n == 2) run(args[1], false);
    else {
        fprintf(stderr, "Usage: sketch [file.sketch]");
        exit(1);
    }
}
