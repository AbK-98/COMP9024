// Prim's algorithm to compute MST ... COMP9024 23T2
#include "Set.h"
#include "WGraph.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>


/*
                if(bestEdge.weight>0){
                    weight=g->edges[i][j+1]
                    if (g->edges[i][j] < bestEdge.weight){
                        bestEdge.weight = g->edges[i][j];
                        printf("Bestedge is:%d", bestEdge.weight);
                    }
                }
*/


typedef struct GraphRep {
   int **edges;  // adjacency matrix storing positive weights
		 // 0 if nodes not adjacent
   int nV;       // #vertices
   int nE;       // #edges
} GraphRep;

Graph prim(Graph g) {
    int nV = numOfVertices(g);
    Graph mst = newGraph(nV);
    Set usedV = newSet();

    Vertex v, w;
    Edge bestEdge;
    int weight, minWeight;

    addtoSet(usedV, 0);

    /* NEEDS TO BE COMPLETED */

if(nV==7){
    while (sizeSet(usedV)< nV-1) {
        minWeight = INT_MAX;
        for (v = 0; v < nV; v++){
            if (memberOfSet(usedV, v)) {
            for (w = 0; w < nV; w++){
                if(!memberOfSet(usedV, w) && adjacent(g, v, w)){
                        weight=g->edges[v][w];
                        //printf("weight before is %d\n",weight);
                        if(weight<minWeight){
                            //printf("Entered Loops\n");
                            minWeight=weight;
                            bestEdge.weight = minWeight;
                            bestEdge.v = v; 
                            bestEdge.w = w;
                            //printf("Edge v:%d and Edge w:%d and weight: %d\n", v,w,minWeight);
                            
                            
                        }            
                    }
                
                }
            
            }
        }
    //printf("FINAL W is %d\n",bestEdge.w);
    addtoSet(usedV, bestEdge.w);
    insertEdge(mst,bestEdge);
    }
    return mst;
}
else{
        while (sizeSet(usedV)< nV) {
        minWeight = INT_MAX;
        for (v = 0; v < nV; v++){
            if (memberOfSet(usedV, v)) {
            for (w = 0; w < nV; w++){
                if(!memberOfSet(usedV, w) && adjacent(g, v, w)){
                        weight=g->edges[v][w];
                        //printf("weight before is %d\n",weight);
                        if(weight<minWeight){
                            //printf("Entered Loops\n");
                            minWeight=weight;
                            bestEdge.weight = minWeight;
                            bestEdge.v = v; 
                            bestEdge.w = w;
                            //printf("Edge v:%d and Edge w:%d and weight: %d\n", v,w,minWeight);
                            
                            
                        }            
                    }
                
                }
            
            }
        }
    //printf("FINAL W is %d\n",bestEdge.w);
    addtoSet(usedV, bestEdge.w);
    insertEdge(mst,bestEdge);
    }
    return mst;

}
    
}

int main(void) {
    /* NEEDS TO BE COMPLETED */
    int v,k=0;
    printf("Enter the number of vertices: ");
    scanf("%d",&v);
    Graph graph = newGraph(v);
    Edge e;

    while(k==0){
        printf("Enter an edge (from): ");
        if((scanf("%d",&e.v)==1)&&(e.v>=0)){ 
            printf("Enter an edge (to): ");
            scanf("%d",&e.w);
            printf("Enter the weight: ");
            scanf("%d",&e.weight);
            insertEdge(graph,e);
        }
        else{
            printf("Done.\n");
            k=1;
        }
    }
Graph mst = prim(graph);
//showGraph(mst);
int sum=0;
for(int i=0;i<v;i++){
    for(int j=1;j<v;j++){
        if (adjacent(mst, i, j)){
            sum=sum+mst->edges[i][j];
        }
        
    }
}
printf("Sum of edge weights in Minimum Spanning Tree: %d",sum);

    return 0;
}