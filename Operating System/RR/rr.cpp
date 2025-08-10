#include <bits/stdc++.h>
using namespace std;

signed main()
{
    freopen("input.txt", "r", stdin);

    int n, quantum;
    cin >> n >> quantum;

    vector<int> burstTime(n), remainingTime(n), waitingTime(n, 0), turnAroundTime(n, 0);
    vector<string> process(n);
    for (int i = 0; i < n; i++)
    {
        cin >> burstTime[i] >> process[i];
        remainingTime[i] = burstTime[i];
    }

    int time = 0;
    queue<int> q;
    for (int i = 0; i < n; i++)
        q.push(i);

    while (!q.empty())
    {
        int i = q.front();
        q.pop();
        

        if (remainingTime[i] > quantum)
        {
            time += quantum;
            remainingTime[i] -= quantum;
            q.push(i);
        }
        else
        {
            time += remainingTime[i];
            waitingTime[i] = time - burstTime[i];
            remainingTime[i] = 0;
            turnAroundTime[i] = time;
        }
    }

    float avgWaitingTime = 0;
    for (int i = 0; i < n; i++)
        avgWaitingTime += waitingTime[i];
    avgWaitingTime /= n;

    cout << endl;
    for (int i = 0; i < n; i++)
        cout << process[i] << " => ";
    cout << "end" << endl << endl;

    cout << "Process " << "   Burst Time " << "   Waiting Time" << "  " << "Turn Around Time" << endl;
    for (int i = 0; i < n; i++)
        cout << process[i] << "            " << burstTime[i] << "          " << waitingTime[i] << "                " << turnAroundTime[i] << endl;

    cout << endl
         << "Total Time: " << time << endl;
    cout << "Average waiting Time: " << avgWaitingTime << endl;
}
