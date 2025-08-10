#include <bits/stdc++.h>
using namespace std;

int main() {
    fstream file("priority_with_arrival_nonpreemptive.txt");
    int n;
    file >> n;

    vector<tuple<string, int, int, int, int>> p(n); // name, arrival, burst, priority, index
    for (int i = 0; i < n; ++i) {
        auto &[name, at, bt, pri, idx] = p[i];
        file >> name >> at >> bt >> pri;
        idx = i;
    }
    vector<bool> done(n, false);
    vector<int> ct(n), tat(n), wt(n);
    vector<tuple<int, int, string>> gantt;
    int time = 0, completed = 0;
    float tTAT = 0, tWT = 0;

    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; ++i) {
            auto &[name, at, bt, pri, id] = p[i];
            if (!done[i] && at <= time) {
                if (idx == -1 || pri < get<3>(p[idx]) || (pri == get<3>(p[idx]) && at < get<1>(p[idx])) || (pri == get<3>(p[idx]) && at == get<1>(p[idx]) && id < get<4>(p[idx]))) 
                    idx = i;
            }
        }
        if (idx == -1) {
            gantt.push_back({time, time + 1, "Idle"});
            time++;
            continue;
        }
        auto &[name, at, bt, pri, id] = p[idx];
        gantt.push_back({time, time + bt, name});
        time += bt;
        ct[id] = time;
        tat[id] = ct[id] - at;
        wt[id] = tat[id] - bt;
        tTAT += tat[id];
        tWT += wt[id];
        done[idx] = true;
        completed++;
    }
    cout << "Process\tAT\tBT\tPri\tCT\tTAT\tWT\n";
    for (auto &[name, at, bt, pri, id] : p) {
        cout << name << '\t' << at << '\t' << bt << '\t' << pri << '\t'
             << ct[id] << '\t' << tat[id] << '\t' << wt[id] << '\n';
    }
    cout << "\n\nGantt Chart:\n ";
    for (auto &[st, et, name] : gantt) cout << "-------";
    cout << "\n|";
    for (auto &[st, et, name] : gantt) cout << setw(5) << name << " |";
    cout << "\n ";
    for (auto &[st, et, name] : gantt) cout << "-------";
    cout << "\n" << get<0>(gantt[0]);
    for (auto &[st, et, name] : gantt) cout << setw(7) << et;
    cout << "\n\nAverage Turnaround Time: " << tTAT / n << '\n';
    cout << "Average Waiting Time: " << tWT / n << '\n';
}
