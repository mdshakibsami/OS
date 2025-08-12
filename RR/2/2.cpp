#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("2.txt", "r", stdin);

    int n, quantum;
    cin >> n >> quantum;

    vector<string> process(n);
    vector<int> arrivalTime(n), burstTime(n), remainingTime(n), CT(n), WT(n), TAT(n);
    vector<bool> inQueue(n, false);

    for (int i = 0; i < n; i++) {
        cin >> process[i] >> arrivalTime[i] >> burstTime[i];
        remainingTime[i] = burstTime[i];
    }

    int currentTime = 0;
    queue<int> Q;

    // Initially, add all processes that have arrivalTime = 0
    for (int i = 0; i < n; i++) {
        if (arrivalTime[i] == 0) {
            Q.push(i);
            inQueue[i] = true;
        }
    }

    int completed = 0;
    vector<string> gantt;

    while (completed < n) {
        if (Q.empty()) {
            // No process in queue, move time forward to next arriving process
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && arrivalTime[i] < nextArrival)
                    nextArrival = arrivalTime[i];
            }
            currentTime = nextArrival;
            for (int i = 0; i < n; i++) {
                if (arrivalTime[i] == currentTime && !inQueue[i]) {
                    Q.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int i = Q.front();
        Q.pop();
        gantt.push_back(process[i]);

        int runTime = min(quantum, remainingTime[i]);
        currentTime += runTime;
        remainingTime[i] -= runTime;

        // Add any newly arrived processes at currentTime
        for (int j = 0; j < n; j++) {
            if (!inQueue[j] && arrivalTime[j] <= currentTime) {
                Q.push(j);
                inQueue[j] = true;
            }
        }

        if (remainingTime[i] > 0) {
            Q.push(i); // Not finished, requeue
        } else {
            completed++;
            CT[i] = currentTime;
        }
    }

    // Calculate TAT and WT
    for (int i = 0; i < n; i++) {
        TAT[i] = CT[i] - arrivalTime[i];
        WT[i] = TAT[i] - burstTime[i];
    }

    // Output
    cout << "\nGantt Chart:\n";
    for (auto &p : gantt)
        cout << p << " -> ";
    cout << "end\n\n";

    cout << "Process\tArrival\tBurst\tCompletion\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << process[i] << "\t" << arrivalTime[i] << "\t" << burstTime[i] << "\t"
             << CT[i] << "\t\t" << TAT[i] << "\t" << WT[i] << "\n";
    }

    float avgTAT = accumulate(TAT.begin(), TAT.end(), 0.0) / n;
    float avgWT = accumulate(WT.begin(), WT.end(), 0.0) / n;

    cout << "\nAverage Turn Around Time: " << avgTAT << endl;
    cout << "Average Waiting Time: " << avgWT << endl;

    return 0;
}
