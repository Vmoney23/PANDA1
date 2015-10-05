/* Classify a triangle according to the integer lengths of its sides. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Checks sides against definitions of each type of triangle
char *check(long sideA, long sideB, long sideC) {
  if ((sideA <= 0) || (sideB <= 0) || (sideC <= 0)) return "Illegal";
  else if (((sideA + sideB) < sideC) || ((sideB + sideC) < sideA) || ((sideA + sideC) < sideB)) return "Impossible";
  else if (((sideA + sideB) == sideC) || ((sideB + sideC) == sideA) || ((sideA + sideC) == sideB)) return "Flat";
  else if (sideA == sideB && sideB == sideC) return "Equilateral";
  else if ((sideA == sideB && sideB != sideC) || (sideB == sideC && sideB != sideA) || (sideA == sideC && sideA != sideB)) return "Isosceles";
  else if ((sideA * sideA + sideB * sideB == sideC * sideC) || (sideB * sideB + sideC * sideC == sideA * sideA) || (sideA * sideA + sideC * sideC == sideB * sideB)) return "Right";
  else if (sideA != sideB && sideB != sideC) return "Scalene";
  else return "error";
}

// Checks input to make sure it valid, by comparing the input string to its integer value (which is in string form)
char *compare(char *length1, char *length2, char *length3) {
  int sideA = atoi(length1);
  int sideB = atoi(length2);
  int sideC = atoi(length3);
  char a[20], b[20], c[20];
  sprintf(a, "%d", sideA);
  sprintf(b, "%d", sideB);
  sprintf(c, "%d", sideC);

  if ((strcmp(a, length1) == 0) && (strcmp(b, length2) == 0) && (strcmp(c, length3) == 0)) {
    return check(sideA, sideB, sideC);
  }
  else {
    return "Illegal";
  }
}

// Main function that accepts inputs and begins the checks
char *triangle(char *length1, char *length2, char *length3) {
  return compare(length1, length2, length3);
}

// Check that two strings are equal
void eq(char *actual, char *expected) {
    if (strcmp(actual, expected) != 0) {
        fprintf(stderr, "Test failure, actual: %s\n", actual);
        fprintf(stderr, "Expected: %s\n", expected);
        exit(1);
    }
}

// Run tests on the triangle function.
void test() {
    int mark = 0;
    eq(triangle("8", "8", "8"), "Equilateral"); mark++;
    eq(triangle("1073", "1073", "1073"), "Equilateral"); mark++;
    eq(triangle("15", "15", "13"), "Isosceles"); mark++;
    eq(triangle("15", "13", "15"), "Isosceles"); mark++;
    eq(triangle("13", "15", "15"), "Isosceles"); mark++;
    eq(triangle("25", "25", "27"), "Isosceles"); mark++;
    eq(triangle("25", "27", "25"), "Isosceles"); mark++;
    eq(triangle("27", "25", "25"), "Isosceles"); mark++;
    eq(triangle("3", "4", "5"), "Right"); mark++;
    eq(triangle("5", "12", "13"), "Right"); mark++;
    eq(triangle("5", "13", "12"), "Right"); mark++;
    eq(triangle("12", "5", "13"), "Right"); mark++;
    eq(triangle("12", "13", "5"), "Right"); mark++;
    eq(triangle("13", "5", "12"), "Right"); mark++;
    eq(triangle("13", "12", "5"), "Right"); mark++;
    eq(triangle("12", "14", "15"), "Scalene"); mark++;
    eq(triangle("12", "15", "14"), "Scalene"); mark++;
    eq(triangle("14", "12", "15"), "Scalene"); mark++;
    eq(triangle("14", "15", "12"), "Scalene"); mark++;
    eq(triangle("15", "12", "14"), "Scalene"); mark++;
    eq(triangle("15", "14", "12"), "Scalene"); mark++;
    eq(triangle("7", "9", "16"), "Flat"); mark++;
    eq(triangle("7", "16", "9"), "Flat"); mark++;
    eq(triangle("9", "16", "7"), "Flat"); mark++;
    eq(triangle("16", "7", "9"), "Flat"); mark++;
    eq(triangle("16", "9", "7"), "Flat"); mark++;
    eq(triangle("2", "3", "13"), "Impossible"); mark++;
    eq(triangle("2", "13", "3"), "Impossible"); mark++;
    eq(triangle("13", "2", "3"), "Impossible"); mark++;
    eq(triangle("0", "0", "0"), "Illegal"); mark++;
    eq(triangle("0", "10", "12"), "Illegal"); mark++;
    eq(triangle("10", "0", "12"), "Illegal"); mark++;
    eq(triangle("10", "12", "0"), "Illegal"); mark++;
    eq(triangle("-1", "-1", "-1"), "Illegal"); mark++;
    eq(triangle("-1", "10", "12"), "Illegal"); mark++;
    eq(triangle("10", "-1", "12"), "Illegal"); mark++;
    eq(triangle("10", "12", "-1"), "Illegal"); mark++;
    eq(triangle("x", "y", "z"), "Illegal"); mark++;
    eq(triangle("10", "12", "13.4"), "Illegal"); mark++;
    eq(triangle("03", "4", "5"), "Illegal"); mark++;
    eq(triangle("3", "04", "5"), "Illegal"); mark++;
    eq(triangle("3", "4", "05"), "Illegal"); mark++;
    eq(triangle("3x", "4y", "5z"), "Illegal"); mark++;
    eq(triangle("2147483648","2147483647","2147483647"),"Illegal"); mark++;
    eq(triangle("2147483647","2147483648","2147483647"),"Illegal"); mark++;
    eq(triangle("2147483647","2147483647","2147483648"),"Illegal"); mark++;
    eq(triangle("2147483647","2147483647","2147483647"),"Equilateral"); mark++;
    eq(triangle("1100000000","1705032704","1805032704"),"Scalene"); mark++;
    eq(triangle("2000000001","2000000002","2000000003"),"Scalene"); mark++;
    eq(triangle("150000002","666666671","683333338"),"Scalene"); mark++;

    printf("Tests passed: %d\n", mark);
}

// Run the program or, if there are no arguments, test it.
int main(int argc, char **argv) {
    if (argc == 1) {
        test();
    }
    else if (argc == 4) {
        char *result = triangle(argv[1], argv[2], argv[3]);
        printf("%s\n", result);
    }
    else {
        fprintf(stderr, "Use e.g.: ./triangle 3 4 5\n");
        exit(1);
    }
}
