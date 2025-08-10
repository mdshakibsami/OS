#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("2.txt", "r", stdin);

    int n;
    cin >> n;
    vector<string> process(n), gantt;
    vector<int> brustTime(n), rBrustTime(n), arrivalTime(n), priority(n), CT(n), TAT(n), WT(n);
    vector<bool> done(n, false);

    for (int i = 0; i < n; i++)
    {
        cin >> process[i] >> arrivalTime[i] >> priority[i] >> brustTime[i];
        rBrustTime[i] = brustTime[i];
    }

    int completed = 0, currentTime = 0;
    while (completed < n)
    {
        int index = -1;
        int minPriority = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && arrivalTime[i] <= currentTime)
            {
                if (priority[i] < minPriority)
                {
                    minPriority = priority[i];
                    index = i;
                }
                else if (priority[i] == minPriority)
                {
                    if (arrivalTime[i] < arrivalTime[index])
                    {
                        index = i;
                    }
                }
            }
        }

        if (index == -1)
        {
            currentTime++;
            gantt.push_back("idle");
            continue;
        }

        rBrustTime[index]--;
        currentTime++;
        gantt.push_back(process[index]);

        if (rBrustTime[index] == 0)
        {
            completed++;
            done[index] = true;
            CT[index] = currentTime;
        }
    }

    for (int i = 0; i < n; i++)
    {
        TAT[i] = CT[i] - arrivalTime[i];
        WT[i] = TAT[i] - brustTime[i];
    }

    cout << "Gantt Chart:\n";
    for (auto &p : gantt)
        cout << p << " -> ";
    cout << "end\n\n";

    cout << "Process\tArrival\tBurst\tPriority\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << process[i] << "\t" << arrivalTime[i] << "\t" << brustTime[i] << "\t" << priority[i] << "\t\t"
             << CT[i] << "\t" << TAT[i] << "\t" << WT[i] << "\n";
    }

    float avgTAT = accumulate(TAT.begin(), TAT.end(), 0.0f) / n;
    float avgWT = accumulate(WT.begin(), WT.end(), 0.0f) / n;

    cout << "\nAverage Turn Around Time: " << avgTAT << endl;
    cout << "Average Waiting Time: " << avgWT << endl;

    return 0;
}
