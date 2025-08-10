#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("2.txt");
    int processCount;
    file >> processCount;

    vector<string> processName(processCount);
    vector<int> arrivalTime(processCount), burstTime(processCount), priority(processCount), remainingTime(processCount);

    for (int i = 0; i < processCount; ++i)
    {
        file >> processName[i] >> arrivalTime[i] >> burstTime[i] >> priority[i];
        remainingTime[i] = burstTime[i];
    }

    vector<int> completionTime(processCount), turnaroundTime(processCount), waitingTime(processCount);
    vector<tuple<int, int, string>> ganttChart; // (startTime, endTime, processName)

    int time = 0, completed = 0;
    float totalTurnaround = 0, totalWaiting = 0;
    string prevProcess = "";

    while (completed < processCount)
    {
        int idx = -1;

        // Find process with highest priority that has arrived and still has remaining time
        for (int i = 0; i < processCount; ++i)
        {
            if (arrivalTime[i] <= time && remainingTime[i] > 0)
            {
                if (idx == -1 || priority[i] < priority[idx] ||
                    (priority[i] == priority[idx] && arrivalTime[i] < arrivalTime[idx]) ||
                    (priority[i] == priority[idx] && arrivalTime[i] == arrivalTime[idx] && i < idx))
                {
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            // CPU idle if no process available
            if (prevProcess != "Idle")
                ganttChart.emplace_back(time, time + 1, "Idle");
            else
                get<1>(ganttChart.back())++; // extend last idle block
            time++;
            prevProcess = "Idle";
            continue;
        }

        // Process execution in Gantt chart
        if (prevProcess != processName[idx])
            ganttChart.emplace_back(time, time + 1, processName[idx]);
        else
            get<1>(ganttChart.back())++; // extend current process block

        remainingTime[idx]--;
        time++;
        prevProcess = processName[idx];

        // Process completion
        if (remainingTime[idx] == 0)
        {
            completionTime[idx] = time;
            turnaroundTime[idx] = completionTime[idx] - arrivalTime[idx];
            waitingTime[idx] = turnaroundTime[idx] - burstTime[idx];
            totalTurnaround += turnaroundTime[idx];
            totalWaiting += waitingTime[idx];
            completed++;
        }
    }

    // Print results
    cout << "Process\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
    for (int i = 0; i < processCount; ++i)
    {
        cout << processName[i] << '\t' << arrivalTime[i] << '\t' << burstTime[i] << '\t' << priority[i] << '\t'
             << completionTime[i] << '\t' << turnaroundTime[i] << '\t' << waitingTime[i] << '\n';
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

    cout << fixed << setprecision(2);
    cout << "\n\nAverage Turnaround Time: " << totalTurnaround / processCount;
    cout << "\nAverage Waiting Time: " << totalWaiting / processCount << '\n';

    return 0;
}
