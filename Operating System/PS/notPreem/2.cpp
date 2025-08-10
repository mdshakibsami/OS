#include <bits/stdc++.h>
using namespace std;

int main()
{
    fstream inputFile("2.txt");
    int processCount;
    inputFile >> processCount;

    // Tuple: (ProcessName, ArrivalTime, BurstTime, Priority, OriginalIndex)
    vector<tuple<string, int, int, int, int>> processes(processCount);
    for (int i = 0; i < processCount; ++i)
    {
        auto &[name, arrival, burst, priority, index] = processes[i];
        inputFile >> name >> arrival >> burst >> priority;
        index = i;
    }

    vector<bool> isCompleted(processCount, false);
    vector<int> completionTime(processCount), turnaroundTime(processCount), waitingTime(processCount);
    vector<tuple<int, int, string>> ganttChart; // (startTime, endTime, processName)

    int currentTime = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < processCount)
    {
        int selectedIndex = -1;

        // Find highest priority process that has arrived and is not done
        for (int i = 0; i < processCount; ++i)
        {
            auto &[name, arrival, burst, priority, index] = processes[i];
            if (!isCompleted[i] && arrival <= currentTime)
            {
                if (selectedIndex == -1 || priority < get<3>(processes[selectedIndex]) || (priority == get<3>(processes[selectedIndex]) && arrival < get<1>(processes[selectedIndex])) || (priority == get<3>(processes[selectedIndex]) && arrival == get<1>(processes[selectedIndex]) && index < get<4>(processes[selectedIndex])))
                {
                    selectedIndex = i;
                }
            }
        }

        if (selectedIndex == -1)
        {
            // No process available, CPU idle for 1 unit
            ganttChart.push_back({currentTime, currentTime + 1, "Idle"});
            currentTime++;
            continue;
        }

        auto &[name, arrival, burst, priority, index] = processes[selectedIndex];
        ganttChart.push_back({currentTime, currentTime + burst, name});

        currentTime += burst;
        completionTime[index] = currentTime;
        turnaroundTime[index] = completionTime[index] - arrival;
        waitingTime[index] = turnaroundTime[index] - burst;

        totalTAT += turnaroundTime[index];
        totalWT += waitingTime[index];

        isCompleted[selectedIndex] = true;
        completed++;
    }

    cout << "Process\tAT\tBT\tPri\tCT\tTAT\tWT\n";
    for (auto &[name, arrival, burst, priority, index] : processes)
    {
        cout << name << '\t' << arrival << '\t' << burst << '\t' << priority << '\t'
             << completionTime[index] << '\t' << turnaroundTime[index] << '\t' << waitingTime[index] << '\n';
    }

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

    cout << "\n\nAverage Turnaround Time: " << totalTAT / processCount << '\n';
    cout << "Average Waiting Time: " << totalWT / processCount << '\n';

    return 0;
}
