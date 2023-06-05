#include<stdio.h>

#define MAX_SIZE 10
#define BOOL char
#define FALSE 0
#define TRUE 1

int backnum(int n){

    if(n>=99999 || n<=9999){
        printf("\nNumber %d is outside limits\n",n);
        return FALSE;
    }
    else{
        int ncheck=n*4;
        printf("\nNumber %d is within limits\n",n);
        int i,rev=0;
        while(i<5){
            int temp;
            temp=n%10;
            n=n/10;
            rev=rev*10+temp;
            i++;
        }
        if(rev==ncheck){
            return TRUE;
        }
        else{
            return FALSE;
        }

    }

}

int main(){
    int num;
    char s[]= "abhi";
    printf("Hello %s\n", s);
    printf("Give the number:\n");
    scanf("%d", &num);
    int b = backnum(num);
    if(b==1){
        printf("\nThe number %d satisfies the condition and is same as reversed.\n", num);
    }
    else{
        printf("\nThe number %d does not satisfy the condition\n", num);
    }
    return 0; 
}