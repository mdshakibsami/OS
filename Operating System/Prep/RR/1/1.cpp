#include <bits/stdc++.h>
using namespace std;

signed main()
{
    freopen("1.txt", "r", stdin);

    int n, quantum;
    cin >> n >> quantum;

    vector<string> process(n), gantt;
    vector<int> brustTime(n), rBrustTime(n), TAT(n), WT(n), CT(n);

    for (int i = 0; i < n; i++)
    {
        cin >> brustTime[i] >> process[i];
        rBrustTime[i] = brustTime[i];
    }

    int currentTime = 0;
    queue<int> Q;
    for (int i = 0; i < n; i++)
        Q.push(i);

    while (!Q.empty())
    {
        int i = Q.front();
        Q.pop();
        gantt.push_back(process[i]);

        if (rBrustTime[i] > quantum)
        {
            currentTime += quantum;
            rBrustTime[i] -= quantum;
            Q.push(i);
        }
        else
        {
            currentTime += rBrustTime[i];
            rBrustTime[i] = 0;
            CT[i] = currentTime;
        }
    }

    // Calculate TAT and WT after loop
    for (int i = 0; i < n; i++)
    {
        TAT[i] = CT[i]; // arrivalTime=0 assumed
        WT[i] = TAT[i] - brustTime[i];
    }

    // Print the execution sequence
    cout << "\nExecution Order:\n";
    for (auto p : gantt)
        cout << p << " => ";
    cout << "end" << endl;

    float aTAT = (accumulate(TAT.begin(), TAT.end(), 0.0)) / n;
    float aWT = (accumulate(WT.begin(), WT.end(), 0.0)) / n;

    cout << "Process " << "   Burst Time " << "   Waiting Time" << "  " << "Turn Around Time" << endl;
    for (int i = 0; i < n; i++)
        cout << process[i] << "            " << brustTime[i] << "          " << WT[i] << "                " << TAT[i] << endl;

    cout << endl
         << "Total Turn Around Time: " << aTAT << endl;
    cout << endl
         << "Average waiting Time: " << aWT << endl;
}