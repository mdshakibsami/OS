#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream inputFile("1.txt"); // Open input file
    int n;
    inputFile >> n;

    vector<int> burstTime(n), completionTime(n), waitingTime(n), turnaroundTime(n);
    vector<string> processID(n);

    // Read process IDs and burst times
    for (int i = 0; i < n; i++) {
        inputFile >> processID[i] >> burstTime[i];
    }

    // First process waiting time is zero, completion time equals burst time
    waitingTime[0] = 0;
    completionTime[0] = burstTime[0];

    // Calculate completion and waiting times for other processes
    for (int i = 1; i < n; i++) {
        completionTime[i] = completionTime[i - 1] + burstTime[i];
        waitingTime[i] = completionTime[i - 1]; // Waiting time = completion time of previous process
    }

    // Turnaround time = completion time - arrival time (arrival time = 0 here)
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = completionTime[i];
    }

    // Calculate total waiting time for average
    float totalWaitingTime = accumulate(waitingTime.begin(), waitingTime.end(), 0);

    // Print process details
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << processID[i] << "\t" << burstTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime[i] << "\n";
    }

    // Print Gantt Chart
    cout << "\nGantt Chart:\n ";
    for (int i = 0; i < n; i++) cout << "-------";
    cout << "\n|";
    for (int i = 0; i < n; i++) cout << " " << setw(4) << processID[i] << " |";
    cout << "\n ";
    for (int i = 0; i < n; i++) cout << "-------";

    cout << "\n0";
    for (int i = 0; i < n; i++) cout << setw(7) << completionTime[i];

    cout << "\n\nAverage Waiting Time: " << totalWaitingTime / n << "\n";

    return 0;
}
