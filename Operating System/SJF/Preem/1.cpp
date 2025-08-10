#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream inputFile("1.txt");
    int n;
    inputFile >> n;

    vector<string> processNames(n);
    vector<int> burstTimes(n), remainingBurst(n);
    for (int i = 0; i < n; i++)
    {
        inputFile >> processNames[i] >> burstTimes[i];
        remainingBurst[i] = burstTimes[i];
    }

    vector<int> completionTime(n, 0), turnaroundTime(n, 0), waitingTime(n, 0);
    vector<bool> done(n, false);

    int completed = 0;
    int currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    vector<tuple<int, int, string>> ganttChart; // (startTime, endTime, processName)
    string prevProcess = "";

    while (completed < n)
    {
        int idx = -1;
        int minRemaining = INT_MAX;

        // Find process with minimum remaining burst time that is not done
        for (int i = 0; i < n; i++)
        {
            if (!done[i] && remainingBurst[i] > 0)
            {
                if (remainingBurst[i] < minRemaining ||
                    (remainingBurst[i] == minRemaining && i < idx))
                {
                    idx = i;
                    minRemaining = remainingBurst[i];
                }
            }
        }

        if (idx == -1)
        {
            // No process left (should not happen if completed<n), but just in case
            currentTime++;
            continue;
        }

        // Gantt chart update
        if (prevProcess != processNames[idx])
            ganttChart.push_back({currentTime, currentTime + 1, processNames[idx]});
        else
            get<1>(ganttChart.back())++; // extend current process execution

        remainingBurst[idx]--;
        currentTime++;
        prevProcess = processNames[idx];

        if (remainingBurst[idx] == 0)
        {
            done[idx] = true;
            completed++;
            completionTime[idx] = currentTime;
            turnaroundTime[idx] = completionTime[idx]; // arrival time = 0
            waitingTime[idx] = turnaroundTime[idx] - burstTimes[idx];
            totalTAT += turnaroundTime[idx];
            totalWT += waitingTime[idx];
        }
    }

    // Print process info
    cout << "Process\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << processNames[i] << "\t" << burstTimes[i] << "\t"
             << completionTime[i] << "\t" << turnaroundTime[i] << "\t" << waitingTime[i] << "\n";
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
    cout << "\n0";
    for (auto &[start, end, name] : ganttChart)
        cout << setw(7) << end;

    cout << "\n\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "Average Waiting Time: " << totalWT / n << endl;

    return 0;
}
