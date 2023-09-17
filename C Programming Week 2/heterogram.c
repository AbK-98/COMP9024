#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_Size 31

bool isHeterogram(char A[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int n = i+1;
        //printf("i is value: %c\n",A[i]);  Check to see values
        while (n < len)
        {
            //printf("n is value: %c\n",A[n]); Check to see values
            if (A[i] == A[n])
            {
                //printf("It is not hetereogram\n"); Check to see values
                return false;
            }
            n++;
        }
    }
    //printf("it is heterogram\n"); Check to see values
    return true;
}

int main()
{
    printf("Enter a string: ");
    char arr[MAX_Size];
    scanf("%s", arr);
    int l= strlen(arr);

    bool v = isHeterogram(arr, l);
    if (v){
        printf("yes");
    }
    else{
        printf("no");
    }
    //printf("the value is:%d\n", v); Check to see values
    return 0;
}