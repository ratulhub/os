#include <stdio.h>

int main() {
    int n, i, tq;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process[n], arrival[n], burst[n], remaining[n], completion[n];
    int waiting[n], turnaround[n];

    // --------- Input ---------
    for (i = 0; i < n; i++) {
        process[i] = i + 1;
        printf("Enter arrival time of process %d: ", process[i]);
        scanf("%d", &arrival[i]);
        printf("Enter burst time of process %d: ", process[i]);
        scanf("%d", &burst[i]);

        remaining[i] = burst[i];
        completion[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    // --------- Hybrid SRTF + Quantum ---------
    while (completed < n) {
        int min_index = -1;
        int min_remaining = 9999;

        // find shortest remaining time process among arrived ones
        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0 && remaining[i] < min_remaining) {
                min_remaining = remaining[i];
                min_index = i;
            }
        }

        // No process arrived → jump to next arrival time
        if (min_index == -1) {
            int next_arrival = 9999;
            for (i = 0; i < n; i++) {
                if (arrival[i] > time && arrival[i] < next_arrival)
                    next_arrival = arrival[i];
            }
            time = next_arrival;
            continue;
        }

        // Execute process for min(quantum, remaining)
        int exec_time = (remaining[min_index] > tq) ? tq : remaining[min_index];
        remaining[min_index] -= exec_time;
        time += exec_time;

        // If process finished
        if (remaining[min_index] == 0) {
            completion[min_index] = time;
            completed++;
        }
    }

    // --------- Calculate Times ---------
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
