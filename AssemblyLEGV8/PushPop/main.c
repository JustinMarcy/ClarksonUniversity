#include <stdio.h>
#include <stdlib.h>
extern long long int sum(int a);

int main (void) {
  for(;;) { //continuous loop until the user states that they want to exit
    int a; //initialize user input
    printf("Please enter any integer equal to or greater than 1: \n");
    scanf("%d", &a); //user input for a
    if (a < 1) {//if input is less than 1
      printf("Error: integer was less than 1, please try again \n"); //print error
    }
    else if (a >= 1) {//result for a=1
      printf("Result: %lld \n", sum(a)); //call assembly function, pass argument, get result, output
      int b; //value for input for continuing program
      printf("To continue, enter 1  | To exit, enter 0 \n");
      scanf("%d", &b);
      	  if (b == 0) {     //exit loop if 0
          break;
      	  }
    }
    else { //error for input
      printf("Error: Input could not be understood \n"); //non-integer case
    }
  }
  return 0; //exit program
  }
