#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<assert.h>

/*
int main(){
  int data[12] = {6, 5, 3, 2, 7, 4, 9, 1, 8};
  printf("Value is :%d",*(data+*(data+4)));
return 0;
}

*/

void func(int *a) {
   //a = malloc(sizeof(int));
   assert(a != NULL);
}

int main(void) {
   int *p=malloc(sizeof(int));
   func(p);
   *p = 6;
   printf("%d\n",*p);
   free(p);
   return 0;
}

