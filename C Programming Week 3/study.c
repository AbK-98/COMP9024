#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int func(int n){
    printf("The value is: %d\n", n);
    return n*n;
}

int main(){

    int k;
    printf("The address of k is:\n");
    //checking if value is successfully read
    if((scanf("%d",&k)==1)&&(k>0)){ 
       int m= func(k);
       printf("The value is: %d", m);
    }
    else{
        printf("Its not a numebr");
    }
    return 0;
    
}