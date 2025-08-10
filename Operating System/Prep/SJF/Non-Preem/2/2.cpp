#include <bits/stdc++.h>
using namespace std;

int main()
{

    freopen("2.txt", "r", stdin);

    int n;
    cin >> n;
    vector<string> process(n), grantt;
    vector<int> brustTime(n), arrivalTime(n), CT(n), TAT(n), WT(n);
    vector<bool> done(n, false);

    for (int i = 0; i < n; i++)
        cin >> process[i] >> arrivalTime[i] >> brustTime[i];

    // for (auto x : process)
    //     cout << x << " ";
    // cout << endl;
    // for (auto x : arrivalTime)
    //     cout << x << " ";
    // cout << endl;
    // for (auto x : brustTime)
    //     cout << x << " ";
    // cout << endl;

    int completed = 0, currentTime = 0;
    while (completed < n)
    {

        int index = -1;
        int minBT = INT_MAX;

        // Find process with shortest burst time among those that have arrived and not done
        for (int i = 0; i < n; i++)
        {
            if (!done[i] && arrivalTime[i] <= currentTime && brustTime[i] < minBT)
            {
                minBT = brustTime[i];
                index = i;
            }
        }

        if (index == -1)
        {
            // No process available right now, CPU is idle
            currentTime++;
            // Merge consecutive idle times
            if (grantt.empty() || grantt.back() != "Idle")
                grantt.push_back("Idle");
            continue;
        }

        // Process found, execute it completely
        currentTime += brustTime[index];
        CT[index] = currentTime;
        TAT[index] = CT[index] - arrivalTime[index];
        WT[index] = TAT[index] - brustTime[index];
        done[index] = true;
        completed++;
        grantt.push_back(process[index]);
    }

    // Print process order
    for (auto p : grantt)
        cout << p << " => ";
    cout << "end" << endl;

    float totalTAT = accumulate(TAT.begin(), TAT.end(), 0.0f);
    float totalWT = accumulate(WT.begin(), WT.end(), 0.0f);

    cout << "Process   Burst Time   Arrival Time   Completion Time   Turn Around Time   Waiting Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << process[i] << "         " << brustTime[i] << "             " << arrivalTime[i] << "               " << CT[i]
             << "                 " << TAT[i] << "                 " << WT[i] << "\n";
    }

    cout << "\nAverage Turn Around Time: " << totalTAT / n << endl;
    cout << "Average Waiting Time: " << totalWT / n << endl;
}
