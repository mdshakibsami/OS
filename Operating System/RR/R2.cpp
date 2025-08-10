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

    vector<string> executionOrder;

    while (!q.empty())
    {
        int i = q.front();
        q.pop();

        executionOrder.push_back(process[i]); // store the process execution order

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

    // Print the execution sequence
    cout << "\nExecution Order:\n";
    for (int i = 0; i < executionOrder.size(); i++)
    {
        cout << executionOrder[i];
        if (i != executionOrder.size() - 1)
            cout << " => ";
    }
    cout << " => end\n\n";

    float avgWaitingTime = 0;
    for (int i = 0; i < n; i++)
        avgWaitingTime += waitingTime[i];
    avgWaitingTime /= n;

    cout << "Process " << "   Burst Time " << "   Waiting Time" << "  " << "Turn Around Time" << endl;
    for (int i = 0; i < n; i++)
        cout << process[i] << "            " << burstTime[i] << "          " << waitingTime[i] << "                " << turnAroundTime[i] << endl;

    cout << endl
         << "Total Time: " << time << endl;
    cout << "Average waiting Time: " << avgWaitingTime << endl;
}
