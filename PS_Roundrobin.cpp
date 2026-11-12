
#include <stdio.h>

int main() {
    int n, i, tq;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Invalid number of processes");
        return 0;
    }

    int process[n], arrival[n], burst[n], remaining[n], completion[n];
    int waiting[n], turnaround[n];

    for (i = 0; i < n; i++) {
        process[i] = i + 1;

        printf("Enter arrival time of process %d: ", process[i]);
        scanf("%d", &arrival[i]);

        printf("Enter burst time of process %d: ", process[i]);
        scanf("%d", &burst[i]);

        if (arrival[i] < 0 || burst[i] <= 0) {
            printf("Invalid input");
            return 0;
        }

        remaining[i] = burst[i];
        completion[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    if (tq <= 0) {
        printf("Invalid time quantum");
        return 0;
    }

    int time = 0, completed = 0;
    int queue[100000], front = 0, rear = 0;

    int visited[n];

    for (i = 0; i < n; i++)
        visited[i] = 0;

    for (i = 0; i < n; i++) {
        if (arrival[i] == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {

        if (front == rear) {
            int next_arrival = 999999;

            for (i = 0; i < n; i++) {
                if (remaining[i] > 0 && !visited[i] &&
                    arrival[i] < next_arrival) {
                    next_arrival = arrival[i];
                }
            }

            time = next_arrival;

            for (i = 0; i < n; i++) {
                if (arrival[i] <= time && remaining[i] > 0 && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
        }

        int idx = queue[front++];

        if (remaining[idx] > tq) {
            time += tq;
            remaining[idx] -= tq;
        } else {
            time += remaining[idx];
            remaining[idx] = 0;
            completion[idx] = time;
            completed++;
        }

        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (remaining[idx] > 0) {
            queue[rear++] = idx;
        }
    }

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
