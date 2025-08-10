#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("2.txt");
    int n, timeQuantum;
    file >> n >> timeQuantum;

    vector<string> processId(n);
    vector<int> arrivalTime(n), burstTime(n), remainingTime(n), completionTime(n);

    // Read process info
    for (int i = 0; i < n; ++i)
    {
        file >> processId[i] >> arrivalTime[i] >> burstTime[i];
        remainingTime[i] = burstTime[i];
    }

    queue<int> readyQueue;
    vector<tuple<int, int, string>> ganttChart; // (startTime, endTime, processName)
    int currentTime = 0, completedProcesses = 0;
    vector<bool> inQueue(n, false);

    while (completedProcesses < n)
    {
        // Enqueue processes that have arrived and not in queue
        for (int i = 0; i < n; ++i)
        {
            if (!inQueue[i] && arrivalTime[i] <= currentTime && remainingTime[i] > 0)
            {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        // If queue empty, increment time (CPU idle)
        if (readyQueue.empty())
        {
            currentTime++;
            continue;
        }

        int idx = readyQueue.front();
        readyQueue.pop();

        // Execute for min(timeQuantum, remainingTime)
        int execTime = min(timeQuantum, remainingTime[idx]);

        // Update Gantt chart: add new block or extend if same process
        if (ganttChart.empty() || get<2>(ganttChart.back()) != processId[idx])
            ganttChart.emplace_back(currentTime, currentTime + execTime, processId[idx]);
        else
            get<1>(ganttChart.back()) += execTime;

        currentTime += execTime;
        remainingTime[idx] -= execTime;

        // Enqueue newly arrived processes during this time slice
        for (int i = 0; i < n; ++i)
        {
            if (!inQueue[i] && arrivalTime[i] <= currentTime && remainingTime[i] > 0)
            {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        // If process not finished, enqueue again; else mark completion
        if (remainingTime[idx] > 0)
            readyQueue.push(idx);
        else
        {
            completionTime[idx] = currentTime;
            completedProcesses++;
        }
    }

    // Calculate Turnaround and Waiting times and print results
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    double totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; ++i)
    {
        int tat = completionTime[i] - arrivalTime[i];
        int wt = tat - burstTime[i];
        totalTAT += tat;
        totalWT += wt;
        cout << processId[i] << '\t' << arrivalTime[i] << '\t' << burstTime[i] << '\t'
             << completionTime[i] << '\t' << tat << '\t' << wt << '\n';
    }

    // Print Gantt chart
    cout << "\nGantt Chart:\n ";
    for (auto &[start, end, p] : ganttChart)
        cout << "------";
    cout << "\n|";
    for (auto &[start, end, p] : ganttChart)
        cout << setw(4) << p << " |";
    cout << "\n ";
    for (auto &[start, end, p] : ganttChart)
        cout << "------";
    cout << "\n"
         << get<0>(ganttChart[0]);
    for (auto &[start, end, p] : ganttChart)
        cout << setw(6) << end;

    cout << "\n\nAverage TAT: " << totalTAT / n;
    cout << "\nAverage WT: " << totalWT / n << "\n";

    return 0;
}
