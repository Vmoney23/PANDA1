#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "display.h"

struct state {
    int xcurr, ycurr, xold, yold, rgba;
    bool pen;
};

struct state newState() {
  struct state s;
  s.xcurr = 0;
  s.ycurr = 0;
  s.xold = 0;
  s.yold = 0;
  s.pen = false;
  return s;
}

struct state DX(display *d, int operand, struct state s) {
  s.xold = s.xcurr;
  s.xcurr = s.xcurr + operand;
  return s;
}

struct state DY(display *d, int operand, struct state s) {
  s.yold = s.ycurr;
  s.ycurr = s.ycurr + operand;
  return s;
}

struct state DT(display *d, int operand, struct state s) {
  if (s.pen == true) {
    if((s.xcurr != s.xold) || (s.ycurr != s.yold)) {
      line(d, s.xold, s.yold, s.xcurr, s.ycurr);
    }
  }
  s.xold = s.xcurr;
  s.yold = s.ycurr;
  pause(d, operand);
  return s;
}

struct state PEN(display *d, struct state s, int operand) {
  if (s.pen == true && operand == 3) {
    line(d, s.xold, s.yold, s.xcurr, s.ycurr);
    s.pen = false;
  } else {
    s.pen = true;
  }
  s.xold = s.xcurr;
  s.yold = s.ycurr;
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
  s = newState();
  int opcode, signOperand, unsignOperand;
  unsigned char b = fgetc(in);
  while (! feof(in)) {
    opcode = opCode(b);
    signOperand = signedOperand(b);
    unsignOperand = unsignedOperand(b);
    printf("%d\n", unsignOperand);

    if (opcode == 0) {
      s = DX(d, signOperand, s);
      printf("0: %d\n", signOperand);
    } else if (opcode == 1) {
      s = DY(d, signOperand, s);
      printf("1: %d\n", signOperand);
    } else if (opcode == 2) {
      s = DT(d, unsignOperand, s);
      printf("2: %d\n", unsignOperand);
    } else if (opcode == 3) {
      if ((signOperand) == 3) {
        s = PEN(d, s, signOperand);
        printf("3: %d\n", signOperand);
      } else if ((signOperand) == 4) {
        printf("3: %d\n", signOperand);
        clear(d);
      } else if ((signOperand) == 5) {
        printf("3: %d\n", signOperand);
        key(d);
      }
    }

    printf("s state: x: %d, y: %d, pen: %d\n", s.xcurr, s.ycurr, s.pen);
    b = fgetc(in);
  }
}

// DONE: upgrade this function to read instructions from the file and obey them
void run(char *filename, bool testing) {
    FILE *in = fopen(filename, "rb");
    struct state s;
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
