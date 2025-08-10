#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream file("priority_with_arrival_preemptive.txt");
    int n;
    file >> n;

    vector<string> name(n);
    vector<int> at(n), bt(n), pri(n), rt(n);
    for (int i = 0; i < n; ++i) {
        file >> name[i] >> at[i] >> bt[i] >> pri[i];
        rt[i] = bt[i];
    }
    vector<int> ct(n), tat(n), wt(n);
    vector<tuple<int, int, string>> gantt;
    int time = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;
    string prev = "";

    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; ++i) {
            if (at[i] <= time && rt[i] > 0) {
                if (idx == -1 || pri[i] < pri[idx] || (pri[i] == pri[idx] && at[i] < at[idx]) || (pri[i] == pri[idx] && at[i] == at[idx] && i < idx)) 
                    idx = i;
            }
        }
        if (idx == -1) {
            if (prev != "Idle")
                gantt.emplace_back(time, time + 1, "Idle");
            else
                get<1>(gantt.back())++;
            time++;
            prev = "Idle";
            continue;
        }
        if (prev != name[idx])
            gantt.emplace_back(time, time + 1, name[idx]);
        else
            get<1>(gantt.back())++;

        rt[idx]--;
        time++;
        prev = name[idx];

        if (rt[idx] == 0) {
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            totalTAT += tat[idx];
            totalWT += wt[idx];
            completed++;
        }
    }
    cout << "Process\tAT\tBT\tPri\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; ++i) {
        cout << name[i] << '\t' << at[i] << '\t' << bt[i] << '\t' << pri[i] << '\t'
             << ct[i] << '\t' << tat[i] << '\t' << wt[i] << '\n';
    }
    cout << "\n\nGantt Chart:\n ";
    for (auto &[st, et, nm] : gantt) cout << "-------";
    cout << "\n|";
    for (auto &[st, et, nm] : gantt) cout << setw(5) << nm << " |";
    cout << "\n ";
    for (auto &[st, et, nm] : gantt) cout << "-------";
    cout << "\n" << get<0>(gantt[0]);
    for (auto &[st, et, nm] : gantt) cout << setw(7) << et;
    cout << "\n\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << '\n';
}