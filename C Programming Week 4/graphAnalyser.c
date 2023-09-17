#include "Graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define NODES 1000

typedef struct GraphRep {
   int  **edges;   // adjacency matrix
   int    nV;      // #vertices
   int    nE;      // #edges
} GraphRep;



void DegreeCount(Graph g) {
    assert(g != NULL);
    int a[NODES];
    for (int i = 0; i < g->nV; i++){
        a[i]=0;
    }

    for (int i = 0; i < g->nV; i++){
        //printf("i:%d\n",i);
        for (int j = 0; j < g->nV; j++){
            if (adjacent(g,i,j)){
                //printf("j:%d\n",j);
                a[i]++;
            } 
        }
    }
    printf("Vertex degrees:\n");
    for (int i = 0; i < g->nV; i++){
        printf("%d",a[i]);
        if (i < g->nV - 1) {
            printf(", ");
        }
    }

}


void Cliquer(Graph g){
    assert(g != NULL);
    int v1,v2,v3;
    printf("\nTriplets :\n");
    for (v1 = 0; v1 < g->nV; v1++){
        for (v2 = v1+1; v2 < g->nV; v2++){
            if(adjacent(g,v1,v2)){
                for (v3 = v2+1; v3 < g->nV; v3++){
                    if((adjacent(g,v1,v3))&&(adjacent(g,v2,v3))){
                        //printf("\nClique is Found");
                        printf("%d-%d-%d\n",v1,v2,v3); 
                        
                    }
            }
        }

    }

}
}


void Density(Graph g){
    assert(g != NULL);
    int Ecount=0;
    int v;
    float d;
    for (int i = 0; i < g->nV; i++){
        for (int j = 0; j < g->nV; j++){
            if(g->edges[i][j] == 1){
                Ecount++;
                v=i+1;
            }
        }
    }
Ecount=Ecount/2;
float top= 2 * abs(Ecount);
float bottom = abs(v*(v-1));
d=top/bottom;
printf("\nDensity:%f\n",d); 

}


int main(){
    int v,k=0;
    printf("Enter the number of vertices:");
    scanf("%d",&v);
    Graph graph = newGraph(v);
    Edge e;

    while(k==0){
        printf("Enter an edge (from):");
        if((scanf("%d",&e.v)==1)&&(e.v>=0)){ 
            printf("Enter an edge (to):");
            scanf("%d",&e.w);
            insertEdge(graph,e);
        }
        else{
            printf("Done.");
            k=1;
        }
    }

    //showGraph(graph);
    DegreeCount(graph);
    Cliquer(graph);
    Density(graph);
    freeGraph(graph);
    return 0;
}