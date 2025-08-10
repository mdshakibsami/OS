#include <bits/stdc++.h>
using namespace std;

signed main()
{
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;
    vector<int> burstTime, priority, waitingTime, TurnAroundVec;
    int turnAroundTime = 0;
    vector<string> process;

    for (int i = 0; i < n; i++)
    {
        int bt, pr;
        string name;
        cin >> bt >> pr >> name;
        burstTime.push_back(bt);
        priority.push_back(pr);
        process.push_back(name);
    }

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
    cout << "end" << endl << endl;

    cout << "Process " << "   Burst Time " << "   Priority " << "   Waiting Time" << "  " << "Turn Around Time" << endl;
    for (int i = 0; i < n; i++)
        cout << process[i] << "            " << burstTime[i] << "          " << priority[i] << "           " << waitingTime[i] << "                " << TurnAroundVec[i] << endl;

    cout << endl
         << "Total Turn Around Time: " << turnAroundTime << endl;
    cout << endl
         << "Average waiting Time: " << avgWaitingTime << endl;
}
