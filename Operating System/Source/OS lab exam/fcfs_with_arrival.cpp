#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream file("fcfs_with_arrival.txt");
    int n; file >> n;
    vector<tuple<string, int, int, int>> p(n);
    for (int i = 0; i < n; i++) {
        auto &[name, at, bt, idx] = p[i];
        file >> name >> at >> bt; idx = i;
    }

    sort(p.begin(), p.end(), [](auto &a, auto &b) { return get<1>(a) < get<1>(b); });

    vector<int> CT(n), TAT(n), WT(n);
    int time = 0; float sumWT = 0, sumTAT = 0;

    for (auto &[name, at, bt, idx] : p) {
        time = max(time, at);
        CT[idx] = time + bt; time = CT[idx];
        TAT[idx] = CT[idx] - at; WT[idx] = TAT[idx] - bt;
        sumWT += WT[idx]; sumTAT += TAT[idx];
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &[name, at, bt, idx] : p)
        cout << name << "\t" << at << "\t" << bt << "\t" << CT[idx]
             << "\t" << TAT[idx] << "\t" << WT[idx] << "\n";

    // Gantt Chart
    cout << "\n\nGantt Chart:\n ";
    time = 0;
    for (auto &[name, at, bt, idx] : p)
        cout << (time < at ? "-------" : "") << "-------", time = max(time, at) + bt;

    cout << "\n|", time = 0;
    for (auto &[name, at, bt, idx] : p) {
        if (time < at) cout << " Idle |", time = at;
        cout << " " << setw(4) << name << " |"; time += bt;
    }

    cout << "\n "; time = 0;
    for (auto &[name, at, bt, idx] : p)
        cout << (time < at ? "-------" : "") << "-------", time = max(time, at) + bt;

    cout << "\n0", time = 0;
    for (auto &[name, at, bt, idx] : p) {
        if (time < at) cout << setw(7) << at, time = at;
        time += bt; cout << setw(7) << time;
    }

    cout << "\n\nAverage Waiting Time: " << sumWT / n;
    cout << "\nAverage Turnaround Time: " << sumTAT / n << "\n";
}
