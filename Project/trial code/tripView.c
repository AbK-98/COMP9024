#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAX_STATIONS 100
#define MAX_NAME_LENGTH 17

typedef struct {
    char name[MAX_NAME_LENGTH];
    int transfer_time;
} Station;

typedef struct {
    char station[MAX_NAME_LENGTH];
    int time;
} Stop;

typedef struct {
    Stop stops[MAX_STATIONS];
    int num_stops;
} Timetable;

Station network[MAX_STATIONS];
Timetable timetables[MAX_STATIONS];
int num_stations, num_trains;

// Function prototypes
void readNetwork();
void readTimetables();
void readQuery(char from[], char to[], int *arrival_time);
void findConnection(char from[], char to[], int arrival_time);
void printConnection(Stop stops[], int num_stops);

int main() {
    readNetwork();
    readTimetables();

    char from[MAX_NAME_LENGTH], to[MAX_NAME_LENGTH];
    int arrival_time;

    while (true) {
        readQuery(from, to, &arrival_time);
        if (strcmp(from, "done") == 0) {
            printf("Bye\n");
            break;
        }

        findConnection(from, to, arrival_time);
    }

    return 0;
}

void readNetwork() {
    printf("Size of network: ");
    scanf("%d", &num_stations);

    for (int i = 0; i < num_stations; i++) {
        scanf("%s", network[i].name);
        scanf("%d", &network[i].transfer_time);
    }
}

void readTimetables() {
    printf("Number of timetables: ");
    scanf("%d", &num_trains);

    for (int i = 0; i < num_trains; i++) {
        int num_stops;
        scanf("%d", &num_stops);

        timetables[i].num_stops = num_stops;

        for (int j = 0; j < num_stops; j++) {
            scanf("%s", timetables[i].stops[j].station);
            scanf("%d", &timetables[i].stops[j].time);
        }
    }
}

void readQuery(char from[], char to[], int *arrival_time) {
    printf("\nFrom: ");
    scanf("%s", from);

    if (strcmp(from, "done") != 0) {
        printf("To: ");
        scanf("%s", to);
        printf("Arrive at or before: ");
        scanf("%d", arrival_time);
    }
}

void findConnection(char from[], char to[], int arrival_time) {
    Stop stops[MAX_STATIONS];
    int num_stops = 0;
    int last_departure_time = INT_MAX;

    for (int i = 0; i < num_trains; i++) {
        for (int j = 0; j < timetables[i].num_stops; j++) {
            if (strcmp(timetables[i].stops[j].station, from) == 0 && timetables[i].stops[j].time <= arrival_time) {
                stops[num_stops++] = timetables[i].stops[j];

                for (int k = j + 1; k < timetables[i].num_stops; k++) {
                    // Check if we have reached the destination "to"
                    if (strcmp(timetables[i].stops[k].station, to) == 0 && timetables[i].stops[k].time <= arrival_time) {
                        if (timetables[i].stops[k].time >= last_departure_time) {
                            num_stops = 0;
                            break;
                        }
                        stops[num_stops++] = timetables[i].stops[k];
                        printConnection(stops, num_stops);
                        return;
                    }

                    // Check if the current station allows a valid transfer
                    for (int l = 0; l < num_stations; l++) {
                        if (strcmp(network[l].name, timetables[i].stops[k].station) == 0) {
                            if (timetables[i].stops[k].time > last_departure_time) {
                                last_departure_time = timetables[i].stops[k].time;
                            }
                            stops[num_stops++] = timetables[i].stops[k];
                            break;
                        }
                    }
                }

                // Reset for the next search
                num_stops = 0;
                last_departure_time = INT_MAX;
            }
        }
    }

    printf("No connection.\n");
}

void printConnection(Stop stops[], int num_stops) {
    for (int i = 0; i < num_stops; i++) {
        printf("%d %s\n", stops[i].time, stops[i].station);
    }
}