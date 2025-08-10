#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("1.txt", "r", stdin);
    int n;
    cin >> n;
    vector<string> process;
    vector<int> brustTime, CT(n), TAT(n), WT(n);
    for (int i = 0; i < n; i++)
    {
        int a;
        string s;
        cin >> s >> a;
        process.push_back(s);
        brustTime.push_back(a);
    }
    // for (auto x : process)
    //     cout << x << " ";cout<<endl;
    // for (auto x : brustTime)
    //     cout << x << " ";cout<<endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (brustTime[i] > brustTime[j])
            {
                swap(brustTime[i], brustTime[j]);
                swap(process[i], process[j]);
            }
        }
    }

    // for (auto x : process)
    //     cout << x << " ";
    // cout << endl;
    // for (auto x : brustTime)
    //     cout << x << " ";
    // cout << endl;
    CT[0] = brustTime[0];
    for (int i = 1; i < n; i++)
        CT[i] = CT[i - 1] + brustTime[i];

    // for (auto x : CT)
    //     cout << x << " ";
    // cout << endl;

    for (int i = 0; i < n; i++)
    {
        TAT[i] = CT[i];
        WT[i] = TAT[i] - brustTime[i];
    }

    for (auto p : process)
        cout << p << " => ";
    cout << "end" << endl;

    float aTAT = (accumulate(TAT.begin(), TAT.end(), 0.0)) / n;
    float aWT = (accumulate(WT.begin(), WT.end(), 0.0)) / n;

    cout << "Process " << "   Burst Time " << "   Completion Time" << "   Turn Around Time" << "  " << "Waiting Time" << endl;
    for (int i = 0; i < n; i++)
        cout << process[i] << "            " << brustTime[i] << "          " << CT[i] << "                      " << TAT[i] << "                 " << WT[i] << endl;

    cout << endl
         << "Total Turn Around Time: " << aTAT << endl;
    cout << endl
         << "Average waiting Time: " << aWT << endl;
}