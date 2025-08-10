#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream file("priority_without_arrival_nonpreemptive.txt");
    int n;
    file >> n;

    string process[n];
    int BT[n], priority[n], CT[n], WT[n], TAT[n];
    for (int i = 0; i < n; i++) {
        file >> process[i] >> BT[i] >> priority[i];
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (
                priority[j] > priority[j + 1] ||
                (priority[j] == priority[j + 1] && BT[j] > BT[j + 1])
            ) {
                swap(priority[j], priority[j + 1]);
                swap(BT[j], BT[j + 1]);
                swap(process[j], process[j + 1]);
            }
        }
    }
    WT[0] = 0;
    CT[0] = BT[0];
    for (int i = 1; i < n; i++) {
        CT[i] = CT[i - 1] + BT[i];
        WT[i] = CT[i] - BT[i];
    }
    float totalWT = 0, totalTAT = 0;
    cout << "\nProcess\tBT\tPriority\tWT\tTAT\n";
    for (int i = 0; i < n; i++) {
        TAT[i] = CT[i];
        totalWT += WT[i];
        totalTAT += TAT[i];
        cout << process[i] << "\t" << BT[i] << "\t" << priority[i] << "\t\t" << WT[i] << "\t" << TAT[i] << "\n";
    }
    // Gantt Chart
    cout << "\n\nGantt Chart:\n ";
    for (int i = 0; i < n; i++) cout << "-------";
    cout << "\n|";
    for (int i = 0; i < n; i++) cout << " " << setw(4) << process[i] << " |";
    cout << "\n ";
    for (int i = 0; i < n; i++) cout << "-------";
    cout << "\n0";
    for (int i = 0; i < n; i++) cout << setw(7) << CT[i];
    cout << "\n\nAverage Waiting Time: " << fixed << setprecision(2) << totalWT / n;
    cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << totalTAT / n << "\n";
}
