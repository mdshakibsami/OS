#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream file("1.txt");
    int n;
    file >> n;

    vector<string> processName(n);
    vector<int> burstTime(n), priority(n), remainingTime(n);

    for (int i = 0; i < n; ++i) {
        file >> processName[i] >> burstTime[i] >> priority[i];
        remainingTime[i] = burstTime[i];
    }

    vector<int> completionTime(n), turnaroundTime(n), waitingTime(n);
    vector<tuple<int, int, string>> ganttChart; // start, end, processName

    int time = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;
    string prevProcess = "";

    while (completed < n) {
        int idx = -1;
        // Choose process with highest priority that still has remaining burst
        for (int i = 0; i < n; ++i) {
            if (remainingTime[i] > 0) {
                if (idx == -1 || priority[i] < priority[idx] || 
                   (priority[i] == priority[idx] && i < idx)) {
                    idx = i;
                }
            }
        }

        if (idx == -1) break; // all done (should not happen due to loop condition)

        // For Gantt chart
        if (prevProcess != processName[idx])
            ganttChart.emplace_back(time, time + 1, processName[idx]);
        else
            get<1>(ganttChart.back())++; // extend current process block

        remainingTime[idx]--;
        time++;
        prevProcess = processName[idx];

        if (remainingTime[idx] == 0) {
            completionTime[idx] = time;
            turnaroundTime[idx] = completionTime[idx]; // arrival = 0
            waitingTime[idx] = turnaroundTime[idx] - burstTime[idx];
            totalTAT += turnaroundTime[idx];
            totalWT += waitingTime[idx];
            completed++;
        }
    }

    cout << "Process\tBT\tPriority\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; ++i) {
        cout << processName[i] << '\t' << burstTime[i] << '\t' << priority[i] << '\t'
             << completionTime[i] << '\t' << turnaroundTime[i] << '\t' << waitingTime[i] << '\n';
    }

    cout << "\n\nGantt Chart:\n ";
    for (auto& [start, end, name] : ganttChart) cout << "-------";
    cout << "\n|";
    for (auto& [start, end, name] : ganttChart) cout << setw(5) << name << " |";
    cout << "\n ";
    for (auto& [start, end, name] : ganttChart) cout << "-------";
    cout << "\n" << get<0>(ganttChart[0]);
    for (auto& [start, end, name] : ganttChart) cout << setw(7) << end;

    cout << fixed << setprecision(2);
    cout << "\n\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << '\n';

    return 0;
}
