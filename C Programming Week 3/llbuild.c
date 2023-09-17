#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<assert.h>

#define true 1
#define false 0

typedef struct node{
   int data;
   struct node *next;
}NodeT;

NodeT *makeNode(int v){
    NodeT *new=malloc(sizeof(NodeT));
    assert(new!=NULL);
    new->data=v;
    new->next=NULL;
    return new; 
}

NodeT *insertNode(NodeT *list, int d){
    NodeT *new =makeNode(d);
    new->next=list;
    return new;
}

NodeT *deleteHead(NodeT *list){
    assert(list!=NULL);
    NodeT *head=list;
    list=list->next;
    free(head);
    return list;
}

void DeleteList(NodeT *list){
    NodeT *p, *temp;
    p=list;
    while(p!=NULL){
        temp=p->next;
        free(p);
        p=temp;
    }
}

//Needs some mod
void ScanList(NodeT *list){
    NodeT *p;
    p=list;
    printf("List is:");
    for(p=list;p!=NULL;p=p->next){
        printf("%d",p->data);
        if(p->next!=NULL){
            printf("->");
        }
        
    }
}

NodeT *appendLL(NodeT *list, int d){
    NodeT *p;
    p=list;
    while(p!=NULL){
        p=p->next;
    }
    NodeT *new =makeNode(d);
    new->next=p;
    return new;

}


int main(){
    int n;
    NodeT *all=NULL; //Initialise it to NULL

    printf("Enter a number:");
    while((scanf("%d",&n)==1)&&(n>0)){
        if(n%2==0){
            all=insertNode(all,n);
        }
        else{
            all=appendLL(all,n);
        }

    }
    fprintf(stderr,"Done.");
    ScanList(all);
    DeleteList(all);
    exit(1);

return 0;
}