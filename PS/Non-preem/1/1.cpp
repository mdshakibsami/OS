#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("1.txt", "r", stdin);

    int n;
    cin >> n;
    vector<int> burstTime(n), priority(n), CT(n), TAT(n), WT(n);
    vector<string> process(n);

    for (int i = 0; i < n; i++)
    {
        cin >> process[i] >> priority[i] >> burstTime[i];
    }

    // for (auto x : process)
    //     cout << x << " ";
    // cout << endl;
    // for (auto x : priority)
    //     cout << x << " ";
    // cout << endl;
    // for (auto x : burstTime)
    //     cout << x << " ";
    // cout << endl;

    // Sort by priority (lower value = higher priority)
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (priority[i] > priority[j])
            {
                swap(priority[i], priority[j]);
                swap(burstTime[i], burstTime[j]);
                swap(process[i], process[j]);
            }
        }
    }

    // for (auto x : process)
    //     cout << x << " ";
    // cout << endl;
    // for (auto x : priority)
    //     cout << x << " ";
    // cout << endl;
    // for (auto x : burstTime)
    //     cout << x << " ";
    // cout << endl;

    CT[0] = burstTime[0];
    for (int i = 1; i < n; i++)
    {
        CT[i] = CT[i - 1] + burstTime[i];
    }

    for (int i = 0; i < n; i++)
    {
        TAT[i] = CT[i];
        WT[i] = TAT[i] - burstTime[i];
    }

    float aTAT = accumulate(TAT.begin(), TAT.end(), 0.0) / n;
    float aWT = accumulate(WT.begin(), WT.end(), 0.0) / n;

    for (int i = 0; i < n; i++)
        cout << process[i] << " => ";
    cout << "end" << endl
         << endl;

    cout << "Process " << "   Burst Time " << "   Priority " << "   Waiting Time" << "  " << "Turn Around Time" << endl;
    for (int i = 0; i < n; i++)
        cout << process[i] << "            " << burstTime[i] << "          " << priority[i] << "           " << WT[i] << "                " << TAT[i] << endl;

    cout << endl
         << "Average Turn Around Time: " << aTAT << endl;
    cout << endl    
         << "Average waiting Time: " << aWT << endl;
}
