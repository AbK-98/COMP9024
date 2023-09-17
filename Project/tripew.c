//2023 T2 9024 
// The objective is to write a program tripView.c 
// that generates an optimal trip on (a part of) Sydney's railway network based on user preferences.
#include <string.h> 
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "WGraph.h"
#define MAXTT 10

typedef struct Network {
    char name[16]; //name of a station
    int time; //the time – in minutes – it takes to transfer to a different train at that station.
}Network;

typedef struct Stop{
    char name[16]; //name of a station
    int hhmm; 
}Stop; 

struct Timetable {
    int numtt; // Number of timetable
    struct Stop stops[MAXTT]; // Array of stops for the route 

}Timetable;

int findStationIndex(Network net[], int numStations, const char* name);

int getEdgeWeight(Graph g, Network net[], const char* stationName) {
    int Index = findStationIndex(net, g->nV, stationName);
    if (Index == -1) {
        printf("Station '%s' not found in the network.\n", stationName);
        return -1;
    }

    for (int i = 0; i < g->nV; i++) {
        int weight = g->edges[i][Index];
        if (weight != 0) {
            //int destinationVertex = i;
            //printf("From: %s, To: %s, Weight: %d\n", net[destinationVertex].name, stationName, weight);
            return weight;
        }
    }

    //printf("No edge found from %s.\n", stationName);
    return -1;
}

bool dfsPathCheck(Graph g, int v, int dest, int visited[]) {
    if (v == dest) {
        return true;
    } else {
        for (int w = 0; w < g->nV; w++) {
            if (g->edges[v][w] != 0 && visited[w] == -1) {
                visited[w] = v;
                if (dfsPathCheck(g, w, dest, visited)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void findPath(Graph g, Network net[], int src, int dest) {
    int visited[g->nV];
    int narrary[g->nV];
    
    int narraryIdx = 0; // Index to keep track of the current position in narrary
    for (int i = 0; i < g->nV; i++) {
        visited[i] = -1;
    }
    visited[src] = src;
    narrary[narraryIdx] = src;
    if (dfsPathCheck(g, src, dest, visited)) {
        int v = dest;
        narrary[narraryIdx++] = v;
        while (v != src) {
            //printf("%s - ", net[v].name);
            v = visited[v];
            narrary[narraryIdx++] = v;
        }
        //printf("%s\n", net[src].name);
        int rnarrary[narraryIdx];
        int f = 0;
        for (int j = narraryIdx - 1; j >= 0; j--) { // Correct the loop condition here
            rnarrary[f] = narrary[j];
            f++;
        }

        int x = getEdgeWeight(g, net, net[rnarrary[0]].name);
        if ((x==-1))
        {
            printf("\nNo connection.");
            exit(1);
        }
        
        printf("\n%04d %s\n", x, net[rnarrary[0]].name); 

        for (int i = 0; i < narraryIdx - 1; i++) {
            int u = rnarrary[i];
            int v = rnarrary[i+1];

            if (g->edges[u][v] != 0) {
                printf("%04d %s\n", g->edges[u][v], net[rnarrary[i+1]].name); // Print the station names using net array
            }
        }
        printf("\n");
    } else {
        printf("No path from %s to %s\n", net[src].name, net[dest].name);
    }
}


void FindStops(Graph g, Network net[], int fstation, int tstation, int atime) {
    assert(g != NULL && validV(g, fstation) && validV(g, tstation));

    //printf("\nPossible Stops:\n");
    findPath(g, net, fstation, tstation);

}


int findStationIndex(Network net[], int numStations, const char* name) {
    for (int i = 0; i < numStations; i++) {
        if (strcmp(net[i].name, name) == 0) {
            return i; // Found the station, return its index
        }
    }
    return -1; // Station not found, return -1
}




int main(){
int i;
int n; // indicating the number of railway stations on the network
int m=20; //the number of trains on any day
int s=20; // the number of stops

char nam[16];

printf("Size of network: ");
scanf("%d",&n);
Graph graph = newGraph(n);
Edge e; 
Network net[n];

for(i=0;i<n;i++){
    scanf("%s",net[i].name);
    scanf("%d",&net[i].time);
}

/* Print the data stored in the net array
printf("\nNetwork Information:\n");
for (i = 0; i < n; i++) {
    printf("Station Name: %s\n", net[i].name);
    printf("Transfer Time: %d minutes\n", net[i].time);
    printf("-----------------------------\n");
}
*/
int arrivalTime;

printf("Number of timetables: ");
scanf("%d", &m);
for (i = 0; i < m; i++) {
    printf("Number of stops: ");
    scanf("%d", &s);
    int prevStationIndex = -1;
    for (int j = 0; j < s; j++) {
        scanf("%s", nam);
        e.w = findStationIndex(net, n, nam);
        if (e.w != -1) {
            scanf("%d", &arrivalTime);
            e.weight = arrivalTime;
            if (prevStationIndex != -1) {
                e.v = prevStationIndex;
                insertEdge(graph, e);
            }
            prevStationIndex = e.w;
        }
    }
}

char fromStation[16], toStation[16];
int ATime;
int k=0; 

//showGraph(graph);
//showMatrix(graph);

while(k==0){
    printf("\nFrom: ");
     if (scanf("%s", fromStation) == 1 && (strcmp(fromStation, "done") == 0 || strcmp(fromStation, "Done") == 0)) {
        k=1;
        exit(0);
     }
    printf("To: ");
    scanf("%s", toStation);
    printf("Arrive at or before: ");
    scanf("%d", &ATime);  
    int fs = findStationIndex(net, n, fromStation);
    int ts = findStationIndex(net, n, toStation);
    //printf("fstation is: %d", fs);
    //printf("\ntstation is: %d", ts);
    FindStops(graph, net,fs, ts,ATime);
}


freeGraph(graph);

return 0; 
}