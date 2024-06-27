#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 3  // Number of resources

void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    calculateNeed(need, max, allot);

    bool finish[P] = {0};  
    int safeSeq[P];
    int work[R];//represents the quantity of resources currently available 
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {  
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {  
                        break;
                    }
                }
                if (j == R) {  //As the available resources are sufficient,the process is successfully completed.
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[p][k]; //After completion of the process,the resources that were alloted to that process can be used to accomplish next process,so we add allot array to work
                    }
                    safeSeq[count++] = processes[p];
                    finish[p] = true;  // Mark this process as finished
                    found = true;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state\n");
            return false;
        }
    }
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};
    
    //avail represents resources that are available after allocation from each type
    int avail[] = {3, 3, 2};
   
   //max resources that can be allocated to each process , each index in this array contains the maximum amount of resources that it requires to perform the process from each type
   // example - in {7,5,3} - 7 represents the maximum resources required from type 1 resource list. Similarly 5 and 3 are the maximum resources required from type 2 and type 3 respectively,This {7,5,3}represents the 1st process
    int max[][R] = {{2, 2, 3}, 
                    {3, 2, 2},
                    {3, 0, 2},
                    {2, 2, 2},
                    {2, 3, 3}};

    int allot[][R] = {{0, 1, 0},
                      {2, 0, 0},
                      {3, 0, 2},
                      {2, 1, 1},
                      {0, 0, 2}};

    isSafe(processes, avail, max, allot);

    return 0;
}
