#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "GraphCC.h"

typedef struct GraphRep {
   int  **edges;   // adjacency matrix
   int    nV;      // #vertices
   int    nE;      // #edges
   int nC;
   int *cc;
} GraphRep;

void showComponents(Graph g) {
    assert(g != NULL);
    
    int nV = g->nV;
    int* cc = g->cc;
    
    printf("Connected components:\n");
    for (int i = 0; i < nV; i++) {
        printf("%d", cc[i]);
        if (i < nV - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

int main(void) {
   Edge e;
   int n;
   char c;

   printf("Enter the number of vertices: ");
   scanf("%d", &n);
   Graph g = newGraph(n);

   printf("[i]nsert or [r]emove an edge: ");
   while (scanf(" %c %d %d", &c, &e.v, &e.w) == 3) {
      if (c == 'i') {
         insertEdge(g, e);
      } else if (c == 'r') {
         removeEdge(g, e);
      }
      printf("[i]nsert or [r]emove an edge: ");
   }

   showComponents(g);
   freeGraph(g);
   return 0;
}