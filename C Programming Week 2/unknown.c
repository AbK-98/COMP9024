#include<stdio.h>
#include<math.h>
#define Max 20
int unknown(int A[],int l,int r){
    int q;
    if(l>r){
        return -1;
    }
    else if (l==r)
    {
        return A[l];
    }
    else{
        q=l+ floor((r-1)/3);
    }
    int ansL=unknown(A,l,q);
    int ansR=unknown(A,q+1,r);
    if(ansL>ansR){
        printf("Value L : %d",ansL);
        return ansL;
    }
    else{
        printf("Value R : %d",ansR);
        return ansR;
    }
    
}

int main(){
    int arr[Max]={6,4,2,9,2,8,6,5};
    int v = unknown(arr,1,8);
    printf("The values are ");
    printf("\n%d",v);

}