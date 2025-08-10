#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream file("rr_without_arrival.txt");
    int tq,n;
    file >> tq >> n;

    vector<string> name(n);
    vector<int> bt(n), rt(n);
    for (int i = 0; i < n; ++i) {
        file >> name[i] >> bt[i];
        rt[i] = bt[i]; // Remaining time
    }

    vector<int> ct(n), tat(n), wt(n);
    vector<tuple<int, int, string>> gantt;

    queue<int> q;
    for (int i = 0; i < n; ++i)
        q.push(i);

    int time = 0;
    string prev = "";

    while (!q.empty()) {
        int idx = q.front(); q.pop();
        int exec_time = min(tq, rt[idx]);

        if (prev != name[idx])
            gantt.emplace_back(time, time + exec_time, name[idx]);
        else
            get<1>(gantt.back()) += exec_time;

        time += exec_time;
        rt[idx] -= exec_time;
        prev = name[idx];

        if (rt[idx] > 0)
            q.push(idx);
        else
            ct[idx] = time;
    }

    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; ++i) {
        tat[i] = ct[i]; // AT = 0
        wt[i] = tat[i] - bt[i];
        totalTAT += tat[i];
        totalWT += wt[i];
    }

    cout << "Process\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; ++i)
        cout << name[i] << '\t' << bt[i] << '\t' << ct[i] << '\t' << tat[i] << '\t' << wt[i] << '\n';

    // Gantt Chart
    cout << "\nGantt Chart:\n ";
    for (auto &[s, e, nm] : gantt) cout << "-------";
    cout << "\n|";
    for (auto &[s, e, nm] : gantt) cout << setw(5) << nm << " |";
    cout << "\n ";
    for (auto &[s, e, nm] : gantt) cout << "-------";
    cout << "\n" << get<0>(gantt[0]);
    for (auto &[s, e, nm] : gantt) cout << setw(7) << e;
    cout << "\n\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << '\n';
}
