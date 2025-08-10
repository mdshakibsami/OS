#include<bits/stdc++.h>
using namespace std;

int main(){
    fstream file("sjf_with_arrival_preemptive.txt");
    int n;
    file >> n;

    vector<int> ct(n), tat(n), wt(n);
    vector<tuple<string, int, int, int>> p(n); // name, arrival, burst, index
    for (int i = 0; i < n; i++) {
        auto &[process, at, bt, idx] = p[i];
        file >> process >> at >> bt;
        idx = i;
    }

    vector<int> rem_bt(n); // remaining burst time
    for (int i = 0; i < n; i++) rem_bt[i] = get<2>(p[i]);

    vector<tuple<int, int, string>> gantt;
    vector<bool> done(n);
    int completed = 0, time = 0;
    float tTAT = 0, tWT = 0;

    string prev = "";
    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            auto &[nm, a, b, id] = p[i];
            if (!done[i] && a <= time && rem_bt[i] > 0) {
                if (idx == -1 || rem_bt[i] < rem_bt[idx] ||
                    (rem_bt[i] == rem_bt[idx] && a < get<1>(p[idx])) ||
                    (rem_bt[i] == rem_bt[idx] && a == get<1>(p[idx]) && i < idx)) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            if (prev != "Idle")
                gantt.push_back({time, time + 1, "Idle"});
            else
                get<1>(gantt.back())++;
            prev = "Idle";
            time++;
            continue;
        }

        if (prev != get<0>(p[idx]))
            gantt.push_back({time, time + 1, get<0>(p[idx])});
        else
            get<1>(gantt.back())++;

        rem_bt[idx]--;
        time++;
        prev = get<0>(p[idx]);

        if (rem_bt[idx] == 0) {
            done[idx] = true;
            completed++;
            ct[get<3>(p[idx])] = time;
            tat[get<3>(p[idx])] = ct[get<3>(p[idx])] - get<1>(p[idx]);
            wt[get<3>(p[idx])] = tat[get<3>(p[idx])] - get<2>(p[idx]);
            tTAT += tat[get<3>(p[idx])];
            tWT += wt[get<3>(p[idx])];
        }
    }

    cout << "process\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        auto &[name, at, bt, id] = p[i];
        cout << name << '\t' << at << '\t' << bt << '\t' << ct[id] << '\t' << tat[id] << '\t' << wt[id] << '\n';
    }

    cout << "\n\nGantt Chart: \n ";
    for (auto &[t, ct, nm] : gantt) cout << "-------";
    cout << "\n|";
    for (auto &[t, ct, nm] : gantt) cout << setw(5) << nm << " |";
    cout << "\n ";
    for (auto &[t, ct, nm] : gantt) cout << "-------";
    cout << "\n" << get<0>(gantt[0]);
    for (auto &[t, ct, nm] : gantt) cout << setw(7) << ct;
    cout << "\n\nAverage Turnaround Time : " << tTAT / n << endl;
    cout << "Average Waiting Time : " << tWT / n << endl;
}
