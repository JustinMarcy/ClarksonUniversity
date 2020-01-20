/*
 * main.c
 *
 *  Created on: Oct 28, 2019
 *      Author: Justin
 */
#include<stdio.h>
#pragma fib.S
unsigned char my_assembly_func (
  unsigned int argument)
{
return (argument + 1);   // Insert dummy lines to access all args and retvals
}

main () {
	for(;;) {
		int a;
		printf("Please enter any integer equal to or greater than 1: ");
		scanf("%d", &a);

			if (a < 1) {		//if input is less than 1
				printf("Error: integer was less than 1, please try again");
			}
			else if (a == 1) {		//result for a=1
				printf("1, 1, 2, 3, 5,");
			}
			else {
				printf("Calling assembly function"); //call assembly function, pass argument, get result, output
			}
			int b;
			printf("To continue, enter 1  | To exit, enter 0 ");
			scanf("%d", &b);
			if (b == 0) {     		//exit program if 0
				break;
			}
		}
	}
