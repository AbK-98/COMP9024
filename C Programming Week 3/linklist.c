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

void ScanList(NodeT *list){
    NodeT *p;
    p=list;
    for(p=list;p!=NULL;p=p->next){
        printf("Value is %d",p->data);
    }
}

int inLL(NodeT *list, int d){
    NodeT *p;
    for(p=list;p!=NULL;p=p->next){
        if(p->data==d){
            return true;
        }
        return false;
    }
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