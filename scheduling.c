#include <stdio.h>


void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    // Waiting time for the first process is 0
    wt[0] = 0;

    // Waiting time for each process is the sum of waiting time and burst time of the previous process
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i-1] + wt[i-1];
    }
}

//TurnAroundTime is the time taken to complete the process so it is the sum of waiting time and burst time of that process
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // Calculating turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}


void findAvgTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

   
    findWaitingTime(processes, n, bt, wt);

    findTurnAroundTime(processes, n, bt, wt, tat);

   
    printf("Processes  Burst time  Waiting time  Turn around time\n");

    // Calculate total waiting time and total turn around time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("   %d ", (i+1));
        printf("       %d ", bt[i]);
        printf("       %d", wt[i]);
        printf("       %d\n", tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n", (float)total_tat / (float)n);
}

int main() {
   
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);

    int burst_time[] = {10, 5, 8};

    findAvgTime(processes, n, burst_time);

    return 0;
}
