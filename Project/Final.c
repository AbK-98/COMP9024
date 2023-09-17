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
#define MAXTT 20
#define MAXSTATNAM 17

typedef struct Network {
    char name[17]; //name of a station
    int time; //the time – in minutes – it takes to transfer to a different train at that station.
}Network;

typedef struct Stop{
    char name[17]; //name of a station
    int hhmm; 
}Stop; 

struct Timetable {
    struct Stop stops[MAXTT]; // Array of stops for the route 
}Timetable;

int timet; //Number of timetable
int num_Stops;  // the number of stops
struct Timetable timetables[MAXTT];
int i,j;


bool isDirectPath(char fstation[MAXSTATNAM], char tstation[MAXSTATNAM], struct Timetable timetables[], int timet, int stoparr[], int atime) {
    int findex = -1;
    int tindex = -1;
    for (int i = 0; i < timet; i++) {
        for (int j = 0; j < stoparr[i]; j++) {
            if (strcmp(timetables[i].stops[j].name, fstation) == 0) {
                findex = j;
            }
            if (strcmp(timetables[i].stops[j].name, tstation) == 0) {
                tindex = j;
                if (timetables[i].stops[tindex].hhmm <= atime) {
                    break;
                }
            }
        }
        if (findex != -1 && tindex != -1 && findex <= tindex) {
            return true;
        }
    }
    return false;
}

int getIndex(const char stationName[],int n, Network net[] ) {
    for (int i = 0; i < n; i++) {
        if (strcmp(net[i].name, stationName) == 0) {
            return i;
        }
    }
    // Return -1 if the station name is not found
    return -1;
}

void findOptimalPath(char fstation[MAXSTATNAM], char tstation[MAXSTATNAM], int atime, int timet, int stoparr[], Network net[],int n) {
    int findex = -1;
    int tindex = -1;
    int maxIndex, maxTime;
    // Train change is required
        for (int j = 0; j < stoparr[i]; j++) {
            if (strcmp(timetables[i].stops[j].name, tstation) == 0 && timetables[i].stops[j].hhmm <= atime) {
                maxTime = timetables[i].stops[j].hhmm;
                maxIndex = j;
            }
        }

    // If no direct path, check for indirect path with train change
    int ffound = false;
    int tfound = false;

    for (int i = 0; i < timet; i++) {
        if (!ffound && isDirectPath(fstation, timetables[i].stops[0].name, timetables, timet, stoparr, atime)) {
            for (int j = 0; j < stoparr[i]; j++) {
                if (strcmp(timetables[i].stops[j].name, fstation) == 0 && timetables[i].stops[j].hhmm <= atime) {
                    ffound = true;
                    findex = j;
                    break;
                }
            }
        }
        if (!tfound && isDirectPath(timetables[i].stops[stoparr[i] - 1].name, tstation, timetables, timet, stoparr, atime)) {
            for (int j = 0; j < stoparr[i]; j++) {
                if (strcmp(timetables[i].stops[j].name, tstation) == 0 && timetables[i].stops[j].hhmm <= atime) {
                    tfound = true;
                    tindex = j;
                    break;
                }
            }
        }
        if (ffound && tfound) {
            break;
        }
    }

    if (ffound && tfound) {
        // Print the first leg of the journey
        for (int j = findex; j < stoparr[i]; j++) {
            printf("%04d %s\n", timetables[i].stops[j].hhmm, timetables[i].stops[j].name);
        }

        // Calculate the time for train change
        int transferTime = net[getIndex((timetables[i].stops[stoparr[i] - 1].name),n,net)].time;

        // Print the train change time and station
        printf("%04d %s\n", maxTime + transferTime, timetables[i].stops[maxIndex].name);

        // Find the second leg of the journey
        for (int j = maxIndex + 1; j <= tindex; j++) {
            printf("%04d %s\n", timetables[i].stops[j].hhmm + transferTime, timetables[i].stops[j].name);
        }

        return; // Indirect path with train change printed
    }

    // Print "No connection" if no path is found
    printf("No connection\n");
}

void findPath(char fstation[MAXSTATNAM], char tstation[MAXSTATNAM], int atime, int timet, int stoparr[], Network net[], int n) {
    bool foundDirectPath = false;
    printf("It is inside Findpath func");
    for (int i = 0; i < timet; i++) {
        if (!foundDirectPath && isDirectPath(fstation, tstation, timetables, timet, stoparr, atime)) {
            int findex = -1;
            int tindex = -1;
            printf("It is inside isDirectPath check");
            for (int j = 0; j < stoparr[i]; j++) {
                if (strcmp(timetables[i].stops[j].name, fstation) == 0) {
                    findex = j;
                }
                if (strcmp(timetables[i].stops[j].name, tstation) == 0) {
                    tindex = j;
                    if (timetables[i].stops[j].hhmm <= atime) {
                        break;
                    }
                }
            }

            if (findex != -1 && tindex != -1 && findex <= tindex) {
                if (timetables[i].stops[tindex].hhmm <= atime) {
                    for (int j = findex; j <= tindex; j++) {
                        printf("%04d %s\n", timetables[i].stops[j].hhmm, timetables[i].stops[j].name);
                    }
                    foundDirectPath = true;
                    break;
                } else if (!foundDirectPath) {
                        printf("\nNo direct path found between %s and %s.\n", fstation, tstation);
                        // Call the new findOptimalPath function to handle indirect paths
                        findOptimalPath(fstation, tstation, atime, timet, stoparr, net, n);
                    }else {
                    printf("No connection\n");
                    return;
                }
            }
        }
    }


}



int main(){
   int n; // indicating the number of railway stations on the network
    int stoparr[10];
   printf("Size of network: ");
   scanf("%d",&n); 
   Network net[n];
   for(i=0;i<n;i++){
       scanf("%s",net[i].name);
       scanf("%d",&net[i].time);
    }


   printf("Number of timetables: ");
   scanf("%d", &timet);
   for (i = 0; i < timet; i++) {
    printf("Number of stops: ");
    scanf("%d", &num_Stops);
    stoparr[i]=num_Stops;
    for (j = 0; j < num_Stops; j++)
    {
        scanf("\n%s",timetables[i].stops[j].name);
        scanf("\n%d",&timetables[i].stops[j].hhmm);
    }
   }
    char fromStation[17], toStation[17];
    int ATime;
    int k=0; 

    for (i = 0; i < timet; i++) {
        printf("Timetable %d:\n", i);
        for (j = 0; j < stoparr[i]; j++) {
            printf("Name: %s Time: %04d\n", timetables[i].stops[j].name, timetables[i].stops[j].hhmm);
        }
    }  



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
    findPath(fromStation,toStation, ATime, timet,stoparr,net,n);

}


return 0;
}
