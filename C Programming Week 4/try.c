#include<stdio.h>

 int main(){

    int *p;
    int i=0,y=1;
    p=&i;
    (*p)++;
    printf("i=%d",i);
     p=&y;
    (*p)++;
    printf("y=%d",*p);

    return 0;

 }