#include "Graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_VERTICES 100 
#define ENOUGH 10000  // maximum number of edges
int k,h=0;
int unused[MAX_VERTICES];

typedef struct GraphRep {
   Edge *edges; // array of edges
   int   nV;    // #vertices (numbered 0..nV-1)
   int   nE;    // #edges
   int   n;     // size of edge array
} GraphRep;


Edge  randomEdge(Graph g) {
    assert(g != NULL);
    
    int i = rand() % g->nE;
    return g->edges[i];
}



void approxVertexCover(Graph g, int nV) { // for array of edges graph find vertex cover
    
    for (int i = 0; i < g->nV; i++){
        unused[i] = i;
    }
    //C=∅
    int C[g->nV];
    int coverSize = 0; 
    //while unusedE≠∅
    while(coverSize < nV){
    Edge e =randomEdge(g);
    C[coverSize] = e.v;
    C[coverSize++] = e.w;
    ++coverSize;
    int newUnusedSize = 0;
        for (int i = 0; i < g->nE; i++) {
            if (g->edges[i].v != e.v && g->edges[i].w != e.v &&
                g->edges[i].v != e.w && g->edges[i].w != e.w) {
                unused[newUnusedSize++] = i;
            }
        }
        g->nE = newUnusedSize;
    }
    printf("Approximate Vertex Cover:");
    for (int i = 0; i < coverSize; i++) {
        printf(" %d", C[i]);
    }
    printf("\n");
}



int main(int argc, char *argv[]){
    printf("Enter the number of vertices: ");
    int n;
    int seed = atoi(argv[1]);
    int repetitions = atoi(argv[2]);
    srand(seed);

    scanf("%d", &n);
    Graph g = newGraph(n);
    Edge e;
    while(k==0){
        printf("Enter an edge (from): ");
        if(scanf("%d", &e.v)==1){
            printf("Enter an edge (to): ");
            scanf("%d", &e.w);
            insertEdge(g,e);
        }
        else{
            printf("Done.\n");
            k=1;
        }
        

    }
    while(h <repetitions){
        approxVertexCover(g, n);
        h++;
    }
    freeGraph(g);

    return 0;
}