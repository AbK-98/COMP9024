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

bool isPath(char fstation[MAXSTATNAM], char tstation[MAXSTATNAM], struct Timetable timetables[], int timet, int stoparr[], int atime) {
    bool found_fstation = false;
    for (int i = 0; i < timet; i++) {
        for (int j = 0; j < stoparr[i]; j++) {
            if (strcmp(timetables[i].stops[j].name, fstation) == 0) {
                found_fstation = true;
                break;
            }
        }
        if (found_fstation)
            break;
    }
    if (!found_fstation)
        return false;

    int findex = -1;
    int tindex = -1;

    for (int i = 0; i < timet; i++) {
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
            return true;
        }
    }
    return false;
}

void findPath(char fstation[MAXSTATNAM], char tstation[MAXSTATNAM], int atime, int timet, int stoparr[]) {
    bool foundDirectPath = false;

    for (int i = 0; i < timet; i++) {
        if (isPath(fstation, tstation, timetables, timet, stoparr, atime)) {
            //printf("Direct path found in timetable %d:\n", i + 1);
            int findex = -1;
            int tindex = -1;

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
                if (timetables[i].stops[tindex].hhmm<=atime)
                {
                for (int j = findex; j <= tindex; j++) {
                    printf("%04d %s\n", timetables[i].stops[j].hhmm, timetables[i].stops[j].name);
                }
                foundDirectPath = true;
                break;
                }else{
                    printf("No connection");
                }
            }
        
        }
    }


    if (!foundDirectPath) {
        printf("\nNo direct path found between %s and %s.\n", fstation, tstation);
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
    findPath(fromStation,toStation, ATime, timet,stoparr);

}


return 0;
}
