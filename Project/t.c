#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "WGraph.h"
#define MAXTT 20
#define MAXSTATNAM 17
#define INF 99999

typedef struct Stop {
    char name[MAXSTATNAM];
    int hhmm;
} Stop;

typedef struct Timetable {
    Stop stops[MAXTT];
} Timetable;

typedef struct Network {
    char name[MAXSTATNAM];
    int time;
} Network;

int timet;
int num_Stops;
Timetable timetables[MAXTT];

bool isPath(char fstation[MAXSTATNAM], char tstation[MAXSTATNAM], Timetable timetables[], int timet, int stoparr[], int atime, Graph g) {
    // Implementing Dijkstra's Algorithm to find shortest path
    int dist[MAXTT], prev[MAXTT];
    bool visited[MAXTT];

    for (int i = 0; i < timet; i++) {
        dist[i] = INF;
        prev[i] = -1;
        visited[i] = false;
    }

    int findex = -1;
    int tindex = -1;

    // Find the index of the start station and target station in the graph
    for (int i = 0; i < timet; i++) {
        if (strcmp(timetables[i].stops[0].name, fstation) == 0) {
            findex = i;
        }
        if (strcmp(timetables[i].stops[stoparr[i] - 1].name, tstation) == 0) {
            tindex = i;
        }
    }

    if (findex == -1 || tindex == -1) {
        // Start or target station not found in the timetable
        return false;
    }

    dist[findex] = atime;
    for (int count = 0; count < timet - 1; count++) {
        int u = -1;
        // Find the vertex with the minimum distance
        for (int i = 0; i < timet; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        if (u == -1) {
            // All remaining vertices are inaccessible from the start station
            break;
        }

        visited[u] = true;

        for (int v = 0; v < timet; v++) {
            int weight = adjacent(g, u, v);
            if (weight != 0 && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
        }
    }

    // Backtrack to find the path from start to target station
    if (dist[tindex] != INF) {
        int path[MAXTT], pathLength = 0;
        int current = tindex;
        while (current != findex) {
            path[pathLength++] = current;
            current = prev[current];
        }
        path[pathLength++] = findex;

        // Print the path in reverse order
        for (int i = pathLength - 1; i >= 0; i--) {
            int timetableIndex = path[i];
            for (int j = 0; j < stoparr[timetableIndex]; j++) {
                printf("%04d %s\n", timetables[timetableIndex].stops[j].hhmm, timetables[timetableIndex].stops[j].name);
            }
            if (i != 0) {
                printf("Change at %s\n", timetables[path[i - 1]].stops[0].name);
            }
        }

        return true;
    }

    return false;
}

void findPath(char fstation[MAXSTATNAM], char tstation[MAXSTATNAM], int atime, int timet, int stoparr[], Graph g) {
    bool foundPath = isPath(fstation, tstation, timetables, timet, stoparr, atime, g);
    if (!foundPath) {
        printf("No connection\n");
    }
}

int main() {
    int n;
    printf("Size of network: ");
    scanf("%d", &n);
    Network net[n];
    for (int i = 0; i < n; i++) {
        scanf("%s", net[i].name);
        scanf("%d", &net[i].time);
    }

    printf("Number of timetables: ");
    scanf("%d", &timet);
    int stoparr[MAXTT];
    for (int i = 0; i < timet; i++) {
        printf("Number of stops: ");
        scanf("%d", &num_Stops);
        stoparr[i] = num_Stops;
        for (int j = 0; j < num_Stops; j++) {
            scanf("%s", timetables[i].stops[j].name);
            scanf("%d", &timetables[i].stops[j].hhmm);
        }
    }

    // Create a graph representation of the railway network
    int numVertices = n;
    Graph g = newGraph(numVertices);

    for (int i = 0; i < timet; i++) {
        for (int j = 0; j < num_Stops - 1; j++) {
            int srcIndex = -1;
            int destIndex = -1;

            // Find the index of the source and destination station in the network
            for (int k = 0; k < n; k++) {
                if (strcmp(net[k].name, timetables[i].stops[j].name) == 0) {
                    srcIndex = k;
                }
                if (strcmp(net[k].name, timetables[i].stops[j + 1].name) == 0) {
                    destIndex = k;
                }
            }

            int weight = timetables[i].stops[j].hhmm;
            insertEdge(g, (Edge){srcIndex, destIndex, weight});
        }
    }
    showGraph(g);
    char fromStation[MAXSTATNAM], toStation[MAXSTATNAM];
    int ATime;
    int k = 0;

while(k==0){
    printf("\nFrom: ");
     if (scanf("%s", fromStation) == 1 && (strcmp(fromStation, "done") == 0 || strcmp(fromStation, "Done") == 0)) {
        k=1;
        printf("Bye");
        exit(0);
     }
    printf("To: ");
    scanf("%s", toStation);
    printf("Arrive at or before: ");
    scanf("%d", &ATime);  
    findPath(fromStation,toStation, ATime, timet,stoparr,g);

}


return 0;
}
