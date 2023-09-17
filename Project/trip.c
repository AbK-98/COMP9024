// 2023 T2 9024
//  The objective is to write a program tripView.c
//  that generates an optimal trip on (a part of) Sydney's railway network based on user preferences.
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "WGraph.h"
#define MAXTT 20
#define MAXSTATNAM 17

typedef struct Network
{
    char name[17]; // name of a station
    int time;      // the time – in minutes – it takes to transfer to a different train at that station.
} Network;

typedef struct Stop
{
    char name[17]; // name of a station
    int hhmm;
} Stop;

struct Timetable
{
    struct Stop stops[MAXTT]; // Array of stops for the route
} Timetable;

int timet;     // Number of timetable
int num_Stops; // the number of stops
struct Timetable timetables[MAXTT];
int i, j;

int findStationIndex(Network net[], int numStations, const char *name)
{
    for (int i = 0; i < numStations; i++)
    {
        if (strcmp(net[i].name, name) == 0)
        {
            return i; // Found the station, return its index
        }
    }
    return -1; // Station not found, return -1
}

void addEdgesToGraph(Graph g, struct Timetable timetables[], int timet, int stoparr[], Network net[], int n)
{
    Edge e;
    for (int i = 0; i < timet; i++)
    {
        for (int j = 0; j < stoparr[i] - 1; j++)
        {
            // printf("It is adding edge %d-%d\n",j,j+1);
            e.v = findStationIndex(net, n, timetables[i].stops[j].name);
            e.w = findStationIndex(net, n, timetables[i].stops[j + 1].name);
            int destmm = (timetables[i].stops[j + 1].hhmm % 100) * 60;
            int desthh = (timetables[i].stops[j + 1].hhmm / 100) * 60 * 60;
            int srcmm = (timetables[i].stops[j].hhmm % 100) * 60;
            int srchh = (timetables[i].stops[j].hhmm / 100) * 60 * 60;
            int totdest = destmm + desthh;
            int totsrc = srcmm + srchh;
            e.weight = (totdest - totsrc) / 60; // weight is the time difference between two stations
            printf("It is adding weight %d\n", e.weight);
            insertEdge(g, e);
        }
    }
}
///////////////////////////////////////////////////////////////////////
int minDistance(int dist[], bool sptSet[], int V)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[], int pred[], int V, int dest, int src)
{

    printf("Vertex \t\t Distance from Source\n");
    printf("src  value: %d \t\t\t\t dest: %d\n", src, dest);
    printf("%d \t\t\t\t %d\n", dest, dist[dest]);
}

///////////////////////////////////////////////////////////////////////////////

void findPath(Graph g, char fstation[MAXSTATNAM], char tstation[MAXSTATNAM], int atime, int timet, int stoparr[], int n, Network net[], struct Timetable timetables[])
{
    int sumweights = 0;
    // int directarr[MAXTT];
    for ( i = 0; i < timet; i++)
    {

        int findex = -1;
        int tindex = -1;

        for ( j = 0; j < stoparr[i]; j++)
        {
            if (strcmp(timetables[i].stops[j].name, fstation) == 0)
            {
                findex = j;
            }
            if (strcmp(timetables[i].stops[j].name, tstation) == 0)
            {
                tindex = j;
                if (timetables[i].stops[j].hhmm <= atime)
                {
                    break;
                }
            }
        }

        if (findex != -1 && tindex != -1 && findex <= tindex && tindex <= atime)
        {
            if (timetables[i].stops[tindex].hhmm <= atime)
            {
                for (int j = findex; j <= tindex - 1; j++)
                {
                    int index1 = findStationIndex(net, n, timetables[i].stops[j].name);
                    int index2 = findStationIndex(net, n, timetables[i].stops[j + 1].name);
                    sumweights += g->edges[index1][index2];
                    printf("%04d %s\n", g->edges[index1][index2], timetables[i].stops[j].name);
                    // directarr[i] = g->edges[index1][index2];
                }
                printf("%04d\n", sumweights);

                break;
            }
            else
            {
                printf("No connection");
                return;
            }
        }
    }

    int V = n;
    int src = findStationIndex(net, n, fstation);
    int dest = findStationIndex(net, n, tstation);
    // dijistra algo
    //  Run Dijkstra's algorithm to find the shortest path
    int graph[V][V];
    for ( i = 0; i < V; i++)
    {
        for ( j = 0; j < V; j++)
        {
            graph[i][j] = g->edges[i][j];
        }
    }

    int dist[V];
    int pred[V]; // Array to store the predecessors
    bool sptSet[V];

    for ( i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        pred[i] = -1;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, sptSet, V);

        sptSet[u] = true;

        for (int v = 0; v < V; v++)
        {

            if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                pred[v] = u;
            }
        }
    }

    // Print the array of distances
    int fin[MAXTT], fin1[n], point = 0;
    fin[0] = dest;

    printSolution(dist, pred, V, dest, src);
    for ( i = 0; i < V; i++)
    {
        if (i == dest)
        {

            // printf("Dist value: %d \t\t\t\t %d\n", i, dist[i]);
            printf("Pred value: %d \t\t\t\t %d\n", i, pred[i]);
            int j = i;
            while (j != src)
            {
                j = pred[j];
                fin[++point] = j;
                printf("Pred value: %d \t\t\t\t %d\n", i, j);
            }
        }
    }
    j = 0;
    for ( i = point; i >= 0; i--)
    {
        fin1[j] = fin[i];
        printf("fin1 is: %d ", fin1[j]);
        j++;
    }
    int diji = dist[dest];
    int timetableindex[MAXTT];
    // printf("Before diji sum check\n");
    if (diji < sumweights && dist[dest] <= atime)
    {
        // printf("After diji sum check\n");
        for (int f = 0; f < sizeof(fin1) - 1; f++)
        {
            for ( i = 0; i < timet; i++)
            {
                for ( j = 0; j < stoparr[i]; j++)
                {
                    // printf("Inside diji sum check\n");
                    if ((strcmp(timetables[i].stops[j].name, net[fin1[f]].name) == 0) && (strcmp(timetables[i].stops[j + 1].name, net[fin1[f + 1]].name) == 0) && f + 1 < sizeof(fin1))
                    {
                        timetableindex[j] = i;
                        printf("Timetable Index is: %d", timetableindex[j]);
                    }
                    int trend = timetableindex[0];
                    for (int h = 1; h < sizeof(timetableindex); h++)
                    {
                        if (trend != timetableindex[h])
                        {
                            timetableindex[h + 1] = timetableindex[h];
                            timetableindex[h] = trend;
                            trend=timetableindex[h];
                        }
                    }
                }


            }
            for (int d = 0; d < sizeof(timetableindex); d++)
                {
                    printf("Timetable Index is: %d", timetableindex[d]);
                }

            // int  = findStationIndex(net, n, net[fin1[f]].name);
            // int  = findStationIndex(net, n, net[fin1[f + 1]].name);
            // printf("%04d %s\n", g->edges[index1][index2], net[fin1[f]].name);
        }
    }
}

int main()
{
    int n; // indicating the number of railway stations on the network
    int stoparr[10];
    printf("Size of network: ");
    scanf("%d", &n);
    Network net[n];
    for (i = 0; i < n; i++)
    {
        scanf("%s", net[i].name);
        scanf("%d", &net[i].time);
    }
    printf("Number of timetables: ");
    scanf("%d", &timet);
    for (i = 0; i < timet; i++)
    {
        printf("Number of stops: ");
        scanf("%d", &num_Stops);
        stoparr[i] = num_Stops;
        for (j = 0; j < num_Stops; j++)
        {
            scanf("\n%s", timetables[i].stops[j].name);
            scanf("\n%d", &timetables[i].stops[j].hhmm);
        }
    }
    char fromStation[17], toStation[17];
    int ATime;
    int k = 0;

    for (i = 0; i < timet; i++)
    {
        printf("Timetable %d:\n", i);
        for (j = 0; j < stoparr[i]; j++)
        {
            printf("Name: %s Time: %04d\n", timetables[i].stops[j].name, timetables[i].stops[j].hhmm);
        }
    }

    while (k == 0)
    {
        printf("\nFrom: ");
        if (scanf("%s", fromStation) == 1 && (strcmp(fromStation, "done") == 0 || strcmp(fromStation, "Done") == 0))
        {
            k = 1;
            printf("Bye");
            exit(0);
        }
        printf("To: ");
        scanf("%s", toStation);
        printf("Arrive at or before: ");
        scanf("%d", &ATime);
        Graph g = newGraph(n);
        addEdgesToGraph(g, timetables, timet, stoparr, net, n);
        showGraph(g);

        findPath(g, fromStation, toStation, ATime, timet, stoparr, n, net, timetables);
    }

    return 0;
}
