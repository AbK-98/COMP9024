// Graph ADT
// Array of Edges Representation ... COMP9024 23T2
#include "Graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define ENOUGH 10000  // maximum number of edges

typedef struct GraphRep {
   Edge *edges; // array of edges
   int   nV;    // #vertices (numbered 0..nV-1)
   int   nE;    // #edges
   int   n;     // size of edge array
} GraphRep;

Graph newGraph(int V) {
   assert(V >= 0);

   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);

   g->nV = V;
   g->nE = 0;

   // allocate enough memory for edges
   g->n = ENOUGH;
   g->edges = malloc(g->n * sizeof(Edge));
   assert(g->edges != NULL);

   return g;
}

int numOfVertices(Graph g) {
   return g->nV;
}

// check if two edges are equal
bool eq(Edge e1, Edge e2) {
   return ( (e1.v == e2.v && e1.w == e2.w)
	    || (e1.v == e2.w && e1.w == e2.v) );
}

void insertEdge(Graph g, Edge e) {
   // ensure that g exists and array of edges isn't full
   assert(g != NULL && g->nE < g->n);

   int i = 0;
   while (i < g->nE && !eq(e, g->edges[i]))
      i++;
   if (i == g->nE)                     // edge e not found
      g->edges[g->nE++] = e;
}

void removeEdge(Graph g, Edge e) {
   assert(g != NULL);                 // ensure that g exists

   int i = 0;
   while (i < g->nE && !eq(e, g->edges[i]))
      i++;
   if (i < g->nE)                      // edge e found
      g->edges[i] = g->edges[--g->nE];
}

bool adjacent(Graph g, Vertex x, Vertex y) {
   assert(g != NULL);

   Edge e;
   e.v = x; e.w = y;

   int i = 0;
   while (i < g->nE) {
      if (eq(e, g->edges[i]))
	 return true;
      i++;
   }
   return false;
}

void showGraph(Graph g) {
    assert(g != NULL);

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    int i;
    for (i = 0; i < g->nE; i++)
       printf("Edge %d - %d\n", g->edges[i].v, g->edges[i].w);
}

void freeGraph(Graph g) {
   assert(g != NULL);

   free(g->edges);
   free(g);
}



Graph removeIncidentEdges(Graph g, Edge e)  // removes all edges from g that have at least one endpoint in common with e
{
    assert(g != NULL);
    
    int i = 0;
    while (i < g->nE) {
        if (g->edges[i].v == e.v || g->edges[i].w == e.w || g->edges[i].v == e.w || g->edges[i].w == e.v) {
            g->edges[i] = g->edges[--g->nE];
        } else {
            i++;
        }
    }
    return g;
}

Graph copyGraph(Graph g) { // returns a newly created graph that is an exact copy of g
    assert(g != NULL);
    
    Graph new = newGraph(g->nV);
    new->nE = g->nE;
    int i;
    for (i = 0; i < g->nE; i++) {
        new->edges[i] = g->edges[i];
    }
    return new;
}        

bool  graphIsEmpty(Graph g) {
    assert(g != NULL); 
    return g->nE == 0; // checks if graph g has no edges
}                
