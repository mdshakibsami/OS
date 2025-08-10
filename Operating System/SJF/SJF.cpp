#include <bits/stdc++.h>
using namespace std;

signed main()
{
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;
    vector<int> burstTime, waitingTime, TurnAroundVec;
    int turnAroundTime = 0;
    vector<string> process;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        burstTime.push_back(x);
        string s;
        cin >> s;
        process.push_back(s);
    }

    // Sort by burst time (Shortest Job First)
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (burstTime[i] > burstTime[j])
            {
                swap(burstTime[i], burstTime[j]);
                swap(process[i], process[j]);
            }
        }
    }

    

    for (int i = 0; i < n; i++)
    {
        waitingTime.push_back(turnAroundTime);
        turnAroundTime += burstTime[i];
        TurnAroundVec.push_back(turnAroundTime);
    }

    float avgWaitingTime = 0;
    for (auto x : waitingTime)
        avgWaitingTime += x;
    avgWaitingTime /= n;
    cout << endl;

    for (int i = 0; i < n; i++)
        cout << process[i] << " => ";
    cout << "end" << endl
         << endl;

    cout << "Process " << "   Burst Time " << "   Waiting Time" << "  " << "Turn Around Time" << endl;
    for (int i = 0; i < n; i++)
        cout << process[i] << "            " << burstTime[i] << "          " << waitingTime[i] << "                " << TurnAroundVec[i] << endl;

    cout << endl
         << "Total Turn Around Time: " << turnAroundTime << endl;
    cout << endl
         << "Average waiting Time: " << avgWaitingTime << endl;
}
