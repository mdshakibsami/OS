#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream inputFile("2.txt");
    int n;
    inputFile >> n;

    // Store processes as tuples: (ProcessName, ArrivalTime, BurstTime, OriginalIndex)
    vector<tuple<string, int, int, int>> processes(n);

    for (int i = 0; i < n; i++) {
        auto & [processName, arrivalTime, burstTime, originalIndex] = processes[i];
        inputFile >> processName >> arrivalTime >> burstTime;
        originalIndex = i;  // Keep track of original input order
    }

    // Sort processes by arrival time (earliest first)
    sort(processes.begin(), processes.end(), [](auto& a, auto& b) {
        return get<1>(a) < get<1>(b);  // Compare arrival times
    });

    vector<int> completionTime(n);
    vector<int> turnaroundTime(n);
    vector<int> waitingTime(n);

    int currentTime = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Calculate completion, turnaround, and waiting times
    for (auto& [processName, arrivalTime, burstTime, originalIndex] : processes) {
        // If CPU is idle, jump currentTime forward to process arrival
        currentTime = max(currentTime, arrivalTime);

        completionTime[originalIndex] = currentTime + burstTime;
        currentTime = completionTime[originalIndex];

        turnaroundTime[originalIndex] = completionTime[originalIndex] - arrivalTime;
        waitingTime[originalIndex] = turnaroundTime[originalIndex] - burstTime;

        totalWaitingTime += waitingTime[originalIndex];
        totalTurnaroundTime += turnaroundTime[originalIndex];
    }

    // Print process info table
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (auto& [processName, arrivalTime, burstTime, originalIndex] : processes) {
        cout << processName << "\t"
             << arrivalTime << "\t"
             << burstTime << "\t"
             << completionTime[originalIndex] << "\t\t"
             << turnaroundTime[originalIndex] << "\t\t"
             << waitingTime[originalIndex] << "\n";
    }

    // Print Gantt chart top border
    cout << "\nGantt Chart:\n ";
    currentTime = 0;
    for (auto& [processName, arrivalTime, burstTime, originalIndex] : processes) {
        if (currentTime < arrivalTime) cout << "------- ";
        cout << "------- ";
        currentTime = max(currentTime, arrivalTime) + burstTime;
    }

    // Print Gantt chart process blocks with idle periods
    cout << "\n|";
    currentTime = 0;
    for (auto& [processName, arrivalTime, burstTime, originalIndex] : processes) {
        if (currentTime < arrivalTime) {
            cout << " Idle |";
            currentTime = arrivalTime;
        }
        cout << " " << setw(4) << processName << " |";
        currentTime += burstTime;
    }

    // Print Gantt chart bottom border
    cout << "\n ";
    currentTime = 0;
    for (auto& [processName, arrivalTime, burstTime, originalIndex] : processes) {
        if (currentTime < arrivalTime) cout << "------- ";
        cout << "------- ";
        currentTime = max(currentTime, arrivalTime) + burstTime;
    }

    // Print time markers below Gantt chart
    cout << "\n0";
    currentTime = 0;
    for (auto& [processName, arrivalTime, burstTime, originalIndex] : processes) {
        if (currentTime < arrivalTime) {
            cout << setw(7) << arrivalTime;
            currentTime = arrivalTime;
        }
        currentTime += burstTime;
        cout << setw(7) << currentTime;
    }

    // Print average waiting and turnaround times
    cout << "\n\nAverage Waiting Time: " << totalWaitingTime / n;
    cout << "\nAverage Turnaround Time: " << totalTurnaroundTime / n << "\n";

    return 0;
}
