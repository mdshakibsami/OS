#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("2.txt", "r", stdin);

    int n;
    cin >> n;

    vector<string> process(n);
    vector<int> arrivalTime(n), burstTime(n), priority(n), CT(n), TAT(n), WT(n);
    vector<bool> done(n, false);

    for (int i = 0; i < n; i++)
    {
        cin >> process[i] >> arrivalTime[i] >> burstTime[i] >> priority[i];
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
            // CPU idle
            currentTime++;
            continue;
        }

        currentTime += burstTime[index];
        CT[index] = currentTime;
        TAT[index] = CT[index] - arrivalTime[index];
        WT[index] = TAT[index] - burstTime[index];
        done[index] = true;
        completed++;
    }
    cout << "Process\tArrival\tBurst\tPriority\tCompletion\tTurnAround\tWaiting\n";
    for (int i = 0; i < n; i++)
    {
        cout << process[i] << "\t" << arrivalTime[i] << "\t" << burstTime[i] << "\t"
             << priority[i] << "\t\t" << CT[i] << "\t\t" << TAT[i] << "\t\t" << WT[i] << "\n";
    }

    float avgTAT = accumulate(TAT.begin(), TAT.end(), 0.0f) / n;
    float avgWT = accumulate(WT.begin(), WT.end(), 0.0f) / n;

    cout << "\nAverage Turn Around Time: " << avgTAT << endl;
    cout << "Average Waiting Time: " << avgWT << endl;

    return 0;
}
