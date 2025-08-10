#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream inputFile("1.txt");
    int n;
    inputFile >> n;

    // Each tuple: (processName, burstTime, originalIndex)
    vector<tuple<string, int, int>> processes(n);

    for (int i = 0; i < n; i++) {
        string processName;
        int burstTime;
        inputFile >> processName >> burstTime;
        processes[i] = make_tuple(processName, burstTime, i);
    }

    // Sort processes by burst time (SJF)
    sort(processes.begin(), processes.end(), [](auto &a, auto &b) {
        return get<1>(a) < get<1>(b);
    });

    vector<int> burstTimes(n);
    vector<int> completionTimes(n);
    vector<int> turnaroundTimes(n);
    vector<int> waitingTimes(n);
    vector<string> processNames(n);

    int currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    // Calculate completion, turnaround, waiting times in SJF order
    for (auto &proc : processes) {
        string name = get<0>(proc);
        int burst = get<1>(proc);
        int idx = get<2>(proc);

        currentTime += burst;
        completionTimes[idx] = currentTime;
        processNames[idx] = name;
        burstTimes[idx] = burst;

        turnaroundTimes[idx] = completionTimes[idx]; // arrival time = 0, so TAT = CT
        waitingTimes[idx] = turnaroundTimes[idx] - burst;

        totalWT += waitingTimes[idx];
        totalTAT += turnaroundTimes[idx];
    }

    // Print process details
    cout << "Process\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << processNames[i] << "\t" << burstTimes[i] << "\t"
             << completionTimes[i] << "\t" << turnaroundTimes[i] << "\t"
             << waitingTimes[i] << "\n";
    }

    // Gantt chart display
    cout << "\n\nGantt Chart:\n ";
    for (int i = 0; i < n; i++) cout << "-------";
    cout << "\n|";
    for (auto &proc : processes) {
        string name = get<0>(proc);
        cout << setw(4) << name << "  |";
    }
    cout << "\n ";
    for (int i = 0; i < n; i++) cout << "-------";
    cout << "\n0";
    for (auto &proc : processes) {
        int idx = get<2>(proc);
        cout << setw(7) << completionTimes[idx];
    }

    // Print averages
    cout << "\n\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << "\n";

    return 0;
}
