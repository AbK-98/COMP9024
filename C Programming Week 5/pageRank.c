#include "WGraph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define NODES 1000

typedef struct GraphRep {
   int **edges;  // adjacency matrix storing positive weights
		 // 0 if nodes not adjacent
   int nV;       // #vertices
   int nE;       // #edges
} GraphRep;


void insertionSort(int ar1[],int ar2[],int ar3[],int ar4[],int n) {
   int i;
   for (i = 1; i < n; i++) {
      int el1 = ar1[i];                 // for this element ...
      int el2=ar2[i];
      int el3=ar3[i];
      int el4=ar4[i];

      int j = i-1;
      while (j >= 0 && (ar1[j] < el1 || (ar1[j] == el1 && ar3[j] < el3))) {  // ... work down the ordered list
         ar1[j+1] = ar1[j];               // ... moving elements up
         ar2[j+1] = ar2[j];
         ar3[j+1] = ar3[j];
         ar4[j+1] = ar4[j];

         j--;
      }
      ar1[j+1] = el1;                   // and insert in correct position
      ar2[j+1] = el2;
      ar3[j+1] = el3;
      ar4[j+1] = el4;
   }
}

void pRanker(Graph g, Edge e, int v){
    assert(g != NULL);
    int Inbnd[v], Outbnd[v],score[v],index[v], i, j;
    for (i = 0; i < g->nV; i++){
        Inbnd[i]=0;
        Outbnd[i]=0;
        score[i]=0;
        index[i]=i;
    }

    for (i = 0; i < g->nV; i++){
        for (j = 0; j < g->nV; j++){
            if (g->edges[j][i] != 0){
                //printf("Cnt for %d is :%d\n",i,cnt);
                Inbnd[i]=Inbnd[i]+1;
                //printf("Inbdn value %d is :%d\n",i,Inbnd[i]);

            }
        }
    }

     for (i = 0; i < g->nV; i++){
        for (j = 0; j < g->nV; j++){
            if (g->edges[i][j] != 0){
                Outbnd[i]=Outbnd[i]+1;
                score[i] = score[i] + Inbnd[j];
            }
        }
    }


insertionSort(Inbnd,Outbnd,score,index, v);
/*
     for (i = 0; i < g->nV; i++){
        printf("Inbound of %d is: %d\n", i, Inbnd[i]);
        //printf("Outbound of %d is: %d\n", i, Outbnd[i]);
        printf("Score of %d is: %d\n", i, Outbnd[i] + score[i]);
        
    }
*/
    printf("\nWebpage ranking:\n");
    for (i = 0; i <v; i++) {
        printf("%d has %d inbound links and scores %d on outbound links.\n", index[i], Inbnd[i], Outbnd[i]+score[i]);
    }

}



int main(){
    int v,k=0;
    printf("Enter the number of webpages: ");
    scanf("%d",&v);
    Graph graph = newGraph(v);
    Edge e; 

    while(k==0){
        printf("Enter a webpage: ");
        if((scanf("%d",&e.v)==1)&&(e.v>=0)){ 
            printf("Enter the number of links on webpage %d: ",e.v);
            scanf("%d",&e.weight);
            for(int i =0; i<e.weight;i++){
                printf("Enter a link on webpage %d:",e.v);
                scanf("%d",&e.w);
                insertEdge(graph,e);
            }
        }
        else{
            printf("Done.\n");
            k=1;
        }
    }
    pRanker(graph, e, v);
    //showGraph(graph);

    return 0; 
}