#include <stdio.h>

int main () {
  int i, sum = 0;
  //float n;
  printf("\nSum Calculator from 1 to 100 \n \n");

  /* I didn't use this after all for simplicity reasons
  do {
       printf("Please enter a natural number N : ");
       scanf("%f", &n);
   } while (n <= 0);
  */

  for(i = 1; i <= 100 ; ++i) {
    sum += i;
  }
  printf("sum = %d \n \n", sum) ;
  return 0;
}
