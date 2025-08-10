#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream file("rr_with_arrival.txt");
    int n, tq;
    file >> n >> tq;

    vector<string> pid(n);
    vector<int> at(n), bt(n), rt(n), ct(n);
    for (int i = 0; i < n; ++i) {
        file >> pid[i] >> at[i] >> bt[i];
        rt[i] = bt[i];
    }

    queue<int> q;
    vector<tuple<int, int, string>> gantt;
    int time = 0, done = 0;
    vector<bool> in_q(n, false);

    while (done < n) {
        for (int i = 0; i < n; ++i)
            if (!in_q[i] && at[i] <= time && rt[i] > 0)
                q.push(i), in_q[i] = true;

        if (q.empty()) { time++; continue; }

        int i = q.front(); q.pop();

        int slice = min(tq, rt[i]);
        if (gantt.empty() || get<2>(gantt.back()) != pid[i])
            gantt.emplace_back(time, time + slice, pid[i]);
        else
            get<1>(gantt.back()) += slice;

        time += slice;
        rt[i] -= slice;

        for (int j = 0; j < n; ++j)
            if (!in_q[j] && at[j] <= time && rt[j] > 0)
                q.push(j), in_q[j] = true;

        if (rt[i] > 0) q.push(i);
        else ct[i] = time, done++;
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    double sum_tat = 0, sum_wt = 0;
    for (int i = 0; i < n; ++i) {
        int tat = ct[i] - at[i], wt = tat - bt[i];
        sum_tat += tat; sum_wt += wt;
        cout << pid[i] << '\t' << at[i] << '\t' << bt[i] << '\t' << ct[i] << '\t' << tat << '\t' << wt << '\n';
    }

    cout << "\nGantt Chart:\n ";
    for (auto& [s, e, p] : gantt) cout << "------";
    cout << "\n|";
    for (auto& [s, e, p] : gantt) cout << setw(4) << p << " |";
    cout << "\n ";
    for (auto& [s, e, p] : gantt) cout << "------";
    cout << "\n" << get<0>(gantt[0]);
    for (auto& [s, e, p] : gantt) cout << setw(6) << e;

    cout << "\n\nAverage TAT: " << sum_tat / n << "\nAverage WT: " << sum_wt / n << "\n";
}
