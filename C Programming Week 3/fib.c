#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<assert.h>


int main(int argc, char *argv[]){
   if(argc==2){
       int n =atoi(argv[1]);
       if(n>0){
        unsigned long long int *arr=malloc(sizeof(unsigned long long int)*(n+1));
        *arr=0;
        *(arr+1)=1;
        for(int i=2;i<=n;i++){
            *(arr+i)= *(arr+i-1)+ *(arr+i-2);
        }
        printf("%llu",*(arr+n));
        free(arr);
       }
        
   }else{
    fprintf(stderr,"Usage: ./fib number");
    exit(1);
   }

    return 0;
}