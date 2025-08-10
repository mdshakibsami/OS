#include <bits/stdc++.h>
using namespace std;

int main()
{

    freopen("1.txt", "r", stdin);
    int n;
    cin >> n;
    vector<string> process(n), gantt;
    vector<int> brustTime(n), rBrustTime(n), CT(n), TAT(n), WT(n);

    for (int i = 0; i < n; i++)
    {
        cin >> process[i] >> brustTime[i];
        rBrustTime[i] = brustTime[i];
    }

    // for (auto x : process)
    //     cout << x << " ";
    // cout << endl;
    // for (auto x : brustTime)
    //     cout << x << " ";
    // cout << endl;

    int completed = 0, currentTime = 0;
    while (completed < n)
    {
        int index = -1;
        int minRbt = INT_MAX;

        // Find process with shortest remaining burst time which is not finished
        for (int i = 0; i < n; i++)
        {
            if (rBrustTime[i] > 0 && rBrustTime[i] < minRbt)
            {
                minRbt = rBrustTime[i];
                index = i;
            }
        }

        // All done or no process to run (shouldn't happen without arrival time)
        if (index == -1)
            break;

        // Run process for 1 unit time
        rBrustTime[index]--;
        currentTime++;
        gantt.push_back(process[index]);

        if (rBrustTime[index] == 0)
        {
            completed++;
            CT[index] = currentTime;
        }
    }

    // Calculate TAT and WT
    for (int i = 0; i < n; i++)
    {
        TAT[i] = CT[i]; // Arrival time = 0, so TAT = CT - 0 = CT
        WT[i] = TAT[i] - brustTime[i];
    }

    // Print Gantt chart
    cout << "Gantt Chart (process execution order):\n";
    for (auto &p : gantt)
        cout << p << " -> ";
    cout << "end\n\n";

    // keep only the single process
    gantt.erase(unique(gantt.begin(), gantt.end()), gantt.end());
    // Print table
    cout << "Process   Burst Time   Completion Time   Turn Around Time   Waiting Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << gantt[i] << "            " << brustTime[i] << "             " << CT[i] << "                 " << TAT[i] << "                 " << WT[i] << "\n";
    }

    float avgTAT = accumulate(TAT.begin(), TAT.end(), 0.0f) / n;
    float avgWT = accumulate(WT.begin(), WT.end(), 0.0f) / n;

    cout << "\nAverage Turn Around Time: " << avgTAT << endl;
    cout << "Average Waiting Time: " << avgWT << endl;

    return 0;
}
