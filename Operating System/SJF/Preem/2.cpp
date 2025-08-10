#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream inputFile("2.txt");
    int processCount;
    inputFile >> processCount;

    // Each process: (name, arrivalTime, burstTime, originalIndex)
    vector<tuple<string, int, int, int>> processes(processCount);
    for (int i = 0; i < processCount; i++)
    {
        string name;
        int arrivalTime, burstTime;
        inputFile >> name >> arrivalTime >> burstTime;
        processes[i] = make_tuple(name, arrivalTime, burstTime, i);
    }

    vector<int> remainingBurstTime(processCount);
    for (int i = 0; i < processCount; i++)
    {
        remainingBurstTime[i] = get<2>(processes[i]);
    }

    vector<int> completionTime(processCount), turnaroundTime(processCount), waitingTime(processCount);
    vector<bool> done(processCount, false);

    vector<tuple<int, int, string>> ganttChart; // (startTime, endTime, processName)

    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0;
    string prevProcess = "";

    while (completed < processCount)
    {
        int idx = -1;
        for (int i = 0; i < processCount; i++)
        {
            string name = get<0>(processes[i]);
            int arrival = get<1>(processes[i]);
            int remBurst = remainingBurstTime[i];
            if (!done[i] && arrival <= currentTime && remBurst > 0)
            {
                if (idx == -1 || remBurst < remainingBurstTime[idx] ||
                    (remBurst == remainingBurstTime[idx] && arrival < get<1>(processes[idx])) ||
                    (remBurst == remainingBurstTime[idx] && arrival == get<1>(processes[idx]) && i < idx))
                {
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            // CPU idle
            if (prevProcess != "Idle")
                ganttChart.push_back({currentTime, currentTime + 1, "Idle"});
            else
                get<1>(ganttChart.back())++; // extend idle block
            prevProcess = "Idle";
            currentTime++;
            continue;
        }

        string currProcessName = get<0>(processes[idx]);
        if (prevProcess != currProcessName)
            ganttChart.push_back({currentTime, currentTime + 1, currProcessName});
        else
            get<1>(ganttChart.back())++; // extend current process block

        remainingBurstTime[idx]--;
        currentTime++;
        prevProcess = currProcessName;

        if (remainingBurstTime[idx] == 0)
        {
            done[idx] = true;
            completed++;

            int originalIndex = get<3>(processes[idx]);
            completionTime[originalIndex] = currentTime;
            turnaroundTime[originalIndex] = completionTime[originalIndex] - get<1>(processes[idx]);
            waitingTime[originalIndex] = turnaroundTime[originalIndex] - get<2>(processes[idx]);

            totalTAT += turnaroundTime[originalIndex];
            totalWT += waitingTime[originalIndex];
        }
    }

    // Print process info
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

    // Print Gantt chart
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

    cout << "\n\nAverage Turnaround Time : " << totalTAT / processCount << endl;
    cout << "Average Waiting Time : " << totalWT / processCount << endl;

    return 0;
}
