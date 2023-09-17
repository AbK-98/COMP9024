#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define MAX_STATIONS 100
#define MAX_NAME_LENGTH 17
#define MAX_NODES 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int transfer_time;
} Station;

typedef struct {
    char station[MAX_NAME_LENGTH];
    char time[5];
} Timetable;

typedef struct {
    char from[MAX_NAME_LENGTH];
    char to[MAX_NAME_LENGTH];
    char time[5];
} UserQuery;

typedef int Vertex;

typedef struct {
   Vertex item[MAX_NODES];  // array of vertices currently in queue
   int    length;           // #values currently stored in item[] array
} PQueueT;

// Function to initialize an empty priority queue
void PQueueInit(PQueueT *PQueue) {
   PQueue->length = 0;
}

// Function to insert a vertex v into the priority queue
// No effect if v is already in the queue
void joinPQueue(PQueueT *PQueue, int v) {
   assert(PQueue->length < MAX_NODES);                // ensure queue ADO is not full
   int i = 0;
   while (i < PQueue->length && PQueue->item[i] != v)  // check if v already in queue
      i++;
   if (i == PQueue->length) {                         // v not found => add it at the end
      PQueue->item[PQueue->length] = v;
      PQueue->length++;
   }
}

// Function to remove the highest priority vertex from the priority queue
// Highest priority = lowest value priority[v]
// Returns the removed vertex
Vertex leavePQueue(PQueueT *PQueue, int priority[]) {
   assert(PQueue->length > 0);

   int i, bestIndex = 0, bestVertex = PQueue->item[0], bestWeight = INT_MAX;
   for (i = 0; i < PQueue->length; i++) {         // find i with min priority[item[i]]
      if (priority[PQueue->item[i]] < bestWeight) {
         bestIndex = i;
         bestWeight = priority[PQueue->item[i]];
         bestVertex = PQueue->item[i];            // vertex with lowest value so far
      }
   }
   PQueue->length--;
   PQueue->item[bestIndex] = PQueue->item[PQueue->length];  // replace dequeued node
                                                          // by last element in array
   return bestVertex;
}

// Function to check if priority queue PQueue is empty
bool PQueueIsEmpty(PQueueT *PQueue) {
   return (PQueue->length == 0);
}

// Function to find the connection between two stations
void findConnection(Station stations[], int num_stations, Timetable timetables[], int num_trains, UserQuery query) {
    char route[MAX_STATIONS][MAX_NAME_LENGTH];
    char arrive_time[MAX_STATIONS][5];
    char leave_time[MAX_STATIONS][5];
    int stops = 0;

    int start_index = -1, end_index = -1;
    for (int i = 0; i < num_stations; i++) {
        if (strcmp(stations[i].name, query.from) == 0) {
            start_index = i;
            strcpy(route[stops], stations[i].name);
            strcpy(arrive_time[stops], query.time);
            strcpy(leave_time[stops], query.time);
            stops++;
        }
    }

    if (start_index == -1) {
        printf("No connection.\n");
        return;
    }

    PQueueT pq;
    int priority[MAX_NODES];
    int previous[MAX_NODES];
    PQueueInit(&pq);

    for (int i = 0; i < num_stations; i++) {
        priority[i] = INT_MAX;
        previous[i] = -1;
    }

    priority[start_index] = 0;
    joinPQueue(&pq, start_index);

    while (!PQueueIsEmpty(&pq)) {
        int current = leavePQueue(&pq, priority);
        for (int i = 0; i < num_trains; i++) {
            if (strcmp(timetables[i].station, stations[current].name) == 0) {
                int prev_index = -1;
                for (int j = 0; j < num_stations; j++) {
                    if (strcmp(timetables[i].station, stations[j].name) == 0) {
                        end_index = j;
                        if (prev_index != -1) {
                            int transfer = stations[prev_index].transfer_time;
                            int arrive_hh, arrive_mm, leave_hh, leave_mm;
                            sscanf(arrive_time[stops - 1], "%2d%2d", &arrive_hh, &arrive_mm);
                            sscanf(timetables[i].time, "%2d%2d", &leave_hh, &leave_mm);
                            leave_mm += transfer;
                            leave_hh += leave_mm / 60;
                            leave_mm %= 60;
                            if (leave_hh < arrive_hh || (leave_hh == arrive_hh && leave_mm <= arrive_mm)) {
                                leave_hh = arrive_hh;
                                leave_mm = arrive_mm;
                            }
                            sprintf(leave_time[stops - 1], "%02d%02d", leave_hh, leave_mm);
                        }
                        strcpy(route[stops], stations[j].name);
                        strcpy(arrive_time[stops], timetables[i].time);
                        stops++;
                        prev_index = j;
                    }
                }
                if (strcmp(timetables[i].time, arrive_time[current]) <= 0) {
                    if (strcmp(timetables[i].time, leave_time[end_index]) < 0) {
                        priority[end_index] = (leave_time[end_index][0] - '0') * 60 + (leave_time[end_index][1] - '0') * 10 + 
                                              (leave_time[end_index][2] - '0') * 10 + (leave_time[end_index][3] - '0');
                        previous[end_index] = current;
                        joinPQueue(&pq, end_index);
                    }
                }
            }
        }
    }

    if (previous[end_index] == -1) {
        printf("No connection.\n");
        return;
    }

    int path[MAX_STATIONS];
    int path_len = 0;
    int current = end_index;
    while (current != -1) {
        path[path_len] = current;
        path_len++;
        current = previous[current];
    }

    for (int i = path_len - 1; i >= 0; i--) {
        printf("%s %s\n", route[path[i]], leave_time[path[i]]);
        if (i > 0) {
            printf("Change at %s\n", route[path[i]]);
            printf("%s %s\n", route[path[i]], arrive_time[path[i - 1]]);
        }
    }
}

int main() {
    int num_stations, num_trains;
    Station stations[MAX_STATIONS];
    Timetable timetables[MAX_STATIONS];
    UserQuery query;

    // Input railway stations
    printf("Size of network: ");
    scanf("%d", &num_stations);
    for (int i = 0; i < num_stations; i++) {
        scanf("%s", stations[i].name);
        scanf("%d", &stations[i].transfer_time);
    }

    // Input timetables
    printf("Number of timetables: ");
    scanf("%d", &num_trains);
    for (int i = 0; i < num_trains; i++) {
        int num_stops;
        scanf("%d", &num_stops);
        for (int j = 0; j < num_stops; j++) {
            scanf("%s", timetables[i].station);
            scanf("%s", timetables[i].time);
        }
    }

    // Input user queries
    printf("From: ");
    scanf("%s", query.from);
    while (strcmp(query.from, "done") != 0) {
        scanf("%s", query.to);
        scanf("%s", query.time);
        printf("To: %s\n", query.to);
        printf("Arrive at or before: %s\n", query.time);
        findConnection(stations, num_stations, timetables, num_trains, query);
        printf("From: ");
        scanf("%s", query.from);
    }

    printf("Bye\n");
    return 0;
}