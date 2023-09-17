#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void func(int m){
    printf("The value is: %d\n", m*m);
}


int main(int argc, char *argv[]){
   if(argc==2){
       int n =atoi(argv[1]);
        func(n);
   } 

return 0;
}