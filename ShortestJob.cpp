
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[100], bt[100], ct[100], tat[100], wt[100];
    int p[100], done[100] = {0};

    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
        cout << "Enter Arrival Time and Burst Time of P" << i + 1 << ": ";
        cin >> at[i] >> bt[i];
    }

    int time = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < n) {
        int index = -1;
        int shortest = 9999;

        // Find shortest available process
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && done[i] == 0) {
                if (bt[i] < shortest) {
                    shortest = bt[i];
                    index = i;
                }
            }
        }

        if (index == -1) {
            time++;
        }
        else {
            ct[index] = time + bt[index];
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];

            totalTAT += tat[index];
            totalWT += wt[index];

            time = ct[index];
            done[index] = 1;
            completed++;
        }
    }

    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << p[i] << "\t"
             << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t"
             << wt[i] << endl;
    }

    cout << "\nAverage TAT = " << totalTAT / n;
    cout << "\nAverage WT = " << totalWT / n;

    return 0;
}
