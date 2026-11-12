
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[100], bt[100], ct[100], tat[100], wt[100];
    int p[100], temp;

    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
        cout << "Enter Arrival Time and Burst Time of P" << i + 1 << ": ";
        cin >> at[i] >> bt[i];
    }

    // Sort by Arrival Time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = p[i]; p[i] = p[j]; p[j] = temp;
            }
        }
    }

    // Completion Time
    for (int i = 0; i < n; i++) {
        if (i == 0)
            ct[i] = at[i] + bt[i];
        else {
            if (ct[i-1] > at[i])
                ct[i] = ct[i-1] + bt[i];
            else
                ct[i] = at[i] + bt[i];
        }

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    float totalTAT = 0, totalWT = 0;

    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << p[i] << "\t"
             << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t"
             << wt[i] << endl;

        totalTAT += tat[i];
        totalWT += wt[i];
    }

    cout << "\nAverage TAT = " << totalTAT / n;
    cout << "\nAverage WT = " << totalWT / n;

    return 0;
}
