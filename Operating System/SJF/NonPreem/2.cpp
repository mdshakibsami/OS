#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream inputFile("2.txt");
    int processCount;
    inputFile >> processCount;

    // Store process info: (ProcessName, ArrivalTime, BurstTime, OriginalIndex)
    vector<tuple<string, int, int, int>> processes(processCount);
    for (int i = 0; i < processCount; i++)
    {
        string processName;
        int arrivalTime, burstTime;
        inputFile >> processName >> arrivalTime >> burstTime;
        processes[i] = make_tuple(processName, arrivalTime, burstTime, i);
    }

    vector<int> completionTime(processCount), turnaroundTime(processCount), waitingTime(processCount);
    vector<bool> done(processCount, false);

    int currentTime = 0;
    int completed = 0;
    float totalTAT = 0, totalWT = 0;

    // For Gantt chart: vector of (startTime, endTime, processName)
    vector<tuple<int, int, string>> ganttChart;

    while (completed < processCount)
    {
        int idx = -1;
        int minBurst = INT_MAX;

        // Find process with shortest burst time that has arrived and not done
        for (int i = 0; i < processCount; i++)
        {
            int arrival = get<1>(processes[i]);
            int burst = get<2>(processes[i]);
            if (!done[i] && arrival <= currentTime)
            {
                if (burst < minBurst ||
                    (burst == minBurst && arrival < get<1>(processes[idx])) ||
                    (burst == minBurst && arrival == get<1>(processes[idx]) && i < idx))
                {
                    idx = i;
                    minBurst = burst;
                }
            }
        }

        if (idx == -1)
        {
            // CPU is idle
            ganttChart.push_back({currentTime, currentTime + 1, "Idle"});
            currentTime++;
            continue;
        }

        string procName = get<0>(processes[idx]);
        int arrival = get<1>(processes[idx]);
        int burst = get<2>(processes[idx]);
        int originalIndex = get<3>(processes[idx]);

        currentTime = max(currentTime, arrival);
        ganttChart.push_back({currentTime, currentTime + burst, procName});

        completionTime[originalIndex] = currentTime + burst;
        turnaroundTime[originalIndex] = completionTime[originalIndex] - arrival;
        waitingTime[originalIndex] = turnaroundTime[originalIndex] - burst;

        currentTime += burst;
        done[idx] = true;
        completed++;

        totalTAT += turnaroundTime[originalIndex];
        totalWT += waitingTime[originalIndex];
    }

    // Print process details
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < processCount; i++)
    {
        cout << get<0>(processes[i]) << "\t"
             << get<1>(processes[i]) << "\t"
             << get<2>(processes[i]) << "\t"
             << completionTime[get<3>(processes[i])] << "\t"
             << turnaroundTime[get<3>(processes[i])] << "\t"
             << waitingTime[get<3>(processes[i])] << "\n";
    }

    // Print Gantt Chart
    cout << "\n\nGantt Chart:\n ";
    for (auto &[start, end, name] : ganttChart)
        cout << "-------";
    cout << "\n|";
    for (auto &[start, end, name] : ganttChart)
        cout << setw(5) << name << " |";
    cout << "\n ";
    for (auto &[start, end, name] : ganttChart)
        cout << "-------";

    cout << "\n"
         << get<0>(ganttChart[0]);
    for (auto &[start, end, name] : ganttChart)
        cout << setw(7) << end;

    cout << "\n\nAverage Turnaround Time: " << totalTAT / processCount << endl;
    cout << "Average Waiting Time: " << totalWT / processCount << endl;

    return 0;
}
