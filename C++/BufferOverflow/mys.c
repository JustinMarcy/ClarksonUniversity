#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
    char buff[15];
    
    //0: wrong password
    //1: correct password
    int flag = 0;

    //password  validation

    int attempt = 3;
    while (attempt > 0 && flag == 0) {
      printf("Enter password: ");    
      scanf("%s", buff);
	  
      if(!strcmp(buff, "pass123"))
	flag = 1;

      attempt--;
    }

    if (flag == 0) {
      printf("Multiple login failures; this will be reported.\n");
    }
    
    
    if(flag) {
        printf ("Root privileges granted \n");
    }

    return 0;
}

