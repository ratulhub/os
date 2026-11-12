#include <stdio.h>

int main() {
    int n, i, tq;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process[n], arrival[n], burst[n], remaining[n], completion[n];
    int waiting[n], turnaround[n];

    // ----- Input process details -----
    for (i = 0; i < n; i++) {
        process[i] = i + 1;
        printf("Enter arrival time of process %d: ", process[i]);
        scanf("%d", &arrival[i]);
        printf("Enter burst time of process %d: ", process[i]);
        scanf("%d", &burst[i]);

        remaining[i] = burst[i];   // remaining time initially burst time
        completion[i] = 0;         // will calculate later
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // ----- Initialization -----
    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;

    int visited[n];
    for (i = 0; i < n; i++)
        visited[i] = 0;

    // Add processes that arrive at time = 0
    for (i = 0; i < n; i++) {
        if (arrival[i] == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    // ----- Round Robin Execution -----
    while (completed < n) {

        // If queue is empty → jump to next arrival
        if (front == rear) {
            int next_arrival = 9999;

            for (i = 0; i < n; i++) {
                if (remaining[i] > 0 && arrival[i] > time && arrival[i] < next_arrival) {
                    next_arrival = arrival[i];
                }
            }

            time = next_arrival;

            // Add processes that have arrived now
            for (i = 0; i < n; i++) {
                if (arrival[i] <= time && remaining[i] > 0 && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
        }

        int idx = queue[front++];

        // Process execution
        if (remaining[idx] > tq) {
            time += tq;
            remaining[idx] -= tq;
        } else {
            time += remaining[idx];
            remaining[idx] = 0;
            completion[idx] = time;
            completed++;
        }

        // Add processes that have arrived during execution
        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // If current process is not finished → push back to queue
        if (remaining[idx] > 0) {
            queue[rear++] = idx;
        }
    }

    // ----- Calculate Waiting & Turnaround Time -----
    float total_wt = 0, total_tat = 0;

    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];

        total_wt += waiting[i];
        total_tat += turnaround[i];

        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               process[i], arrival[i], burst[i],
               completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
