#include <stdio.h>
#include <stdlib.h>


int read_req(void){

   char buff[20];
   int i;
   gets(buff);
   i = atoi(buff);
   return i;

}

void secretFunction(){
  printf("Congratulations!\n");
  printf("You have entered the secret function.\n");
}

int main(){

   int x = read_req();
   printf("x = %d\n", x);

   return 0;
}

