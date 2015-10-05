#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void cal();

void new() {
  printf("Would you like to go again?\n1 - Yes\n2 - No\n");
  int q3;
  scanf("%d", &q3);
  printf("You entered %d\n", q3);
  if(q3 == 1) {
    cal();
  }
  else if(q3 == 2) {
    printf("Bye Felicia!\n");
  }
  else {
    printf("Please reload the program and enter a valid option\n");
  }
}

//Performs Addition
void add() {
  printf("Please enter the first number:\n");
  int first, second, result;
  scanf("%d", &first);
  printf("Now the number you want to add to %d:\n", first);
  scanf("%d", &second);
  result = first + second;
  printf("Result: %d\n", result);
  new();
}

//Performs Subtraction
void sub() {
  printf("Please enter the first number:\n");
  int first, second, result;
  scanf("%d", &first);
  printf("Now the number you want to subtract from %d:\n", first);
  scanf("%d", &second);
  result = first - second;
  printf("Result: %d\n", result);
  new();
}

//Performs Multiplication
void mul() {
  printf("Please enter the first number:\n");
  int first, second, result;
  scanf("%d", &first);
  printf("Now the number you want to multiply with %d:\n", first);
  scanf("%d", &second);
  result = first * second;
  printf("Result: %d\n", result);
  new();
}

//Performs Division
void divide() {
  printf("Please enter the first number:\n");
  int first, second, result;
  scanf("%d", &first);
  printf("Now the divide %d by:\n", first);
  scanf("%d", &second);
  result = first / second;
  printf("Result: %d\n", result);
  new();
}

//Asks you what operation you want to perform
void cal() {
  printf("What kind of calculation would you like to perform?\n");
  printf("1 - Addition\n2 - Subtraction\n3 - Multiplication\n4 - Division\n");
  int q2;
  scanf("%d", &q2);
  printf("You entered %d, ", q2);
  if (q2 == 1) {
    printf("Addition.\n");
    add();
  }
  else if (q2 == 2) {
    printf("Subtraction.\n");
    sub();
  }
  else if (q2 == 3) {
    printf("Multiplication.\n");
    mul();
  }
  else if (q2 == 4) {
    printf("Division.\n");
    divide();
  }
  else {
    printf("Please reload the program and enter a valid option\n");
  }
}

//Asks you if you want to perform a calculation or not
int main(void) {
  printf("Welcome to the Calculator\nWould you like to perform a calculation?\n1 - Yes\n2 - No\n");
  int q1;
  scanf("%d", &q1);
  printf("You entered %d\n", q1);
  if(q1 == 1) {
    cal();
  }
  else if(q1 == 2) {
    printf("Bye Felicia!\n");
  }
  else {
    printf("Please reload the program and enter a valid option\n");
  }
}
