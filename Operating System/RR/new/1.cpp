#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream file("1.txt");
    int timeQuantum, processCount;
    file >> timeQuantum >> processCount;

    vector<string> processNames(processCount);
    vector<int> burstTimes(processCount), remainingTimes(processCount);

    for (int i = 0; i < processCount; ++i) {
        file >> processNames[i] >> burstTimes[i];
        remainingTimes[i] = burstTimes[i]; // Initialize remaining times
    }

    vector<int> completionTime(processCount), turnaroundTime(processCount), waitingTime(processCount);
    vector<tuple<int, int, string>> ganttChart;  // (startTime, endTime, processName)

    queue<int> readyQueue;
    for (int i = 0; i < processCount; ++i)
        readyQueue.push(i);

    int currentTime = 0;
    string previousProcess = "";

    // Round Robin simulation
    while (!readyQueue.empty()) {
        int idx = readyQueue.front();
        readyQueue.pop();

        int execTime = min(timeQuantum, remainingTimes[idx]);

        // Update Gantt chart: add new block or extend last block if same process
        if (previousProcess != processNames[idx])
            ganttChart.emplace_back(currentTime, currentTime + execTime, processNames[idx]);
        else
            get<1>(ganttChart.back()) += execTime;

        currentTime += execTime;
        remainingTimes[idx] -= execTime;
        previousProcess = processNames[idx];

        if (remainingTimes[idx] > 0)
            readyQueue.push(idx);
        else
            completionTime[idx] = currentTime;
    }

    // Calculate TAT and WT, assuming arrival time = 0
    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < processCount; ++i) {
        turnaroundTime[i] = completionTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTimes[i];
        totalTAT += turnaroundTime[i];
        totalWT += waitingTime[i];
    }

    // Print process info
    cout << "Process\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < processCount; ++i)
        cout << processNames[i] << '\t' << burstTimes[i] << '\t' << completionTime[i] << '\t'
             << turnaroundTime[i] << '\t' << waitingTime[i] << '\n';

    // Print Gantt chart
    cout << "\nGantt Chart:\n ";
    for (auto &[start, end, name] : ganttChart) cout << "-------";
    cout << "\n|";
    for (auto &[start, end, name] : ganttChart) cout << setw(5) << name << " |";
    cout << "\n ";
    for (auto &[start, end, name] : ganttChart) cout << "-------";

    cout << "\n" << get<0>(ganttChart[0]);
    for (auto &[start, end, name] : ganttChart) cout << setw(7) << end;

    cout << "\n\nAverage Turnaround Time: " << totalTAT / processCount;
    cout << "\nAverage Waiting Time: " << totalWT / processCount << '\n';

    return 0;
}
