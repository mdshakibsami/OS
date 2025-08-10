#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream inputFile("1.txt");
    int processCount;
    inputFile >> processCount;

    string processName[processCount];
    int burstTime[processCount], priority[processCount];
    int completionTime[processCount], waitingTime[processCount], turnaroundTime[processCount];

    // Read process data: name, burst time, and priority
    for (int i = 0; i < processCount; i++) {
        inputFile >> processName[i] >> burstTime[i] >> priority[i];
    }

    // Sort processes based on priority (lower number = higher priority)
    // If priorities are equal, sort by burst time (shorter burst first)
    for (int i = 0; i < processCount - 1; i++) {
        for (int j = 0; j < processCount - i - 1; j++) {
            if (priority[j] > priority[j + 1] ||
                (priority[j] == priority[j + 1] && burstTime[j] > burstTime[j + 1])) {
                swap(priority[j], priority[j + 1]);
                swap(burstTime[j], burstTime[j + 1]);
                swap(processName[j], processName[j + 1]);
            }
        }
    }

    // Calculate Completion Time (CT), Waiting Time (WT), and Turnaround Time (TAT)
    waitingTime[0] = 0;  // First process has no waiting time
    completionTime[0] = burstTime[0];

    for (int i = 1; i < processCount; i++) {
        completionTime[i] = completionTime[i - 1] + burstTime[i];
        waitingTime[i] = completionTime[i - 1];  // Waiting time = sum of burst times of previous processes
    }

    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    cout << "\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < processCount; i++) {
        turnaroundTime[i] = completionTime[i];  // Since arrival time = 0
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];

        cout << processName[i] << "\t" 
             << burstTime[i] << "\t\t" 
             << priority[i] << "\t\t" 
             << waitingTime[i] << "\t\t" 
             << turnaroundTime[i] << "\n";
    }

    // Print Gantt Chart
    cout << "\n\nGantt Chart:\n ";
    for (int i = 0; i < processCount; i++) cout << "-------";
    cout << "\n|";
    for (int i = 0; i < processCount; i++) cout << " " << setw(4) << processName[i] << " |";
    cout << "\n ";
    for (int i = 0; i < processCount; i++) cout << "-------";
    cout << "\n0";
    for (int i = 0; i < processCount; i++) cout << setw(7) << completionTime[i];

    cout << "\n\nAverage Waiting Time: " << fixed << setprecision(2) << totalWaitingTime / processCount;
    cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << totalTurnaroundTime / processCount << "\n";

    return 0;
}
