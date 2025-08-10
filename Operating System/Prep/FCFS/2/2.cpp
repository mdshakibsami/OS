#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("2.txt", "r", stdin);

    int n;
    cin >> n;
    vector<string> process, grantt;
    vector<int> brustTime, arrivalT, CT(n), TAT(n), WT(n);

    for (int i = 0; i < n; i++)
    {
        int x, y;
        string p;
        cin >> p >> x >> y;
        process.push_back(p);
        arrivalT.push_back(x);
        brustTime.push_back(y);
    }

    // for(auto x:process) cout<<x<<" ";
    // for(auto x:brustTime) cout<<x<<" ";
    // for (auto x : arrivalT) cout << x << " ";

    // sort
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arrivalT[i] > arrivalT[j])
            {
                swap(arrivalT[i], arrivalT[j]);
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
    // for (auto x : arrivalT)
    //     cout << x << " ";
    // cout << endl;

    if (arrivalT[0] != 0)
        grantt.push_back("idl");

    CT[0] = arrivalT[0] + brustTime[0];
    grantt.push_back(process[0]);

    for (int i = 1; i < n; i++)
    {
        if (CT[i - 1] >= arrivalT[i])
        {
            CT[i] = CT[i - 1] + brustTime[i];
            grantt.push_back(process[i]);
        }
        else
        {
            grantt.push_back("idl");
            CT[i] = arrivalT[i] + brustTime[i];
        }
    }

    // for (auto x : CT)
    //     cout << x << " ";

    for (int i = 0; i < n; i++)
    {
        TAT[i] = CT[i]- arrivalT[i];
        WT[i] = TAT[i] - brustTime[i];
    }
    for (auto p : grantt)
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