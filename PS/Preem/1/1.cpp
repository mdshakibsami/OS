#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("1.txt", "r", stdin);

    int n;
    cin >> n;
    vector<string> process(n), gantt;
    vector<int> burstTime(n), remainingBT(n), priority(n), CT(n), TAT(n), WT(n);
    vector<bool> done(n, false);

    // Input: process name, priority, burst time
    for (int i = 0; i < n; i++)
    {
        cin >> process[i] >> priority[i] >> burstTime[i];
        remainingBT[i] = burstTime[i];
    }

    int completed = 0, currentTime = 0;

    while (completed < n)
    {
        int index = -1;
        int minPriority = INT_MAX;

        // Find process with highest priority (lowest priority number)
        for (int i = 0; i < n; i++)
        {
            if (!done[i] && priority[i] < minPriority)
            {
                minPriority = priority[i];
                index = i;
            }
        }

        if (index == -1)
        {
            // Should not happen as all processes are available from time 0
            break;
        }

        // Execute process for 1 unit of time (preemptive)
        remainingBT[index]--;
        currentTime++;
        gantt.push_back(process[index]);

        if (remainingBT[index] == 0)
        {
            done[index] = true;
            completed++;
            CT[index] = currentTime;
        }
    }

    // Calculate Turnaround Time and Waiting Time
    for (int i = 0; i < n; i++)
    {
        TAT[i] = CT[i];             // Arrival time = 0 for all
        WT[i] = TAT[i] - burstTime[i];
    }

    // Print Gantt Chart
    for (auto &p : gantt)
        cout << p << " -> ";
    cout << "end\n\n";

    // Output process info
    cout << "Process\tBurst\tPriority\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << process[i] << "\t" << burstTime[i] << "\t" << priority[i]
             << "\t\t" << CT[i] << "\t" << TAT[i] << "\t" << WT[i] << "\n";
    }

    // Calculate average TAT and WT
    float avgTAT = accumulate(TAT.begin(), TAT.end(), 0.0f) / n;
    float avgWT = accumulate(WT.begin(), WT.end(), 0.0f) / n;

    cout << "\nAverage Turnaround Time: " << avgTAT << "\n";
    cout << "Average Waiting Time: " << avgWT << "\n";

    return 0;
}
