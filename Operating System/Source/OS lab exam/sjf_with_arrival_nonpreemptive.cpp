#include<bits/stdc++.h>
using namespace std;

int main(){
    fstream file("sjf_with_arrival_nonpreemptive.txt");
    int n;
    file>>n;

    vector<int> ct(n), tat(n), wt(n);
    vector<tuple<string,int, int, int>>p(n);
    for(int i=0; i<n; i++){
        auto &[process,at,bt,idx] = p[i];
        file>>process>>at >>bt, idx =i;
    }
    int time = 0, completed = 0;
    float tTAT=0, tWT = 0;
    vector<bool>done(n);
    vector<tuple<int,int,string>>gantt;

    while(completed<n){
        int idx = -1;
        for(int i=0; i<n; i++){
            auto &[nm,a,b,id] = p[i];
            if(!done[i] && a<=time){
                if(idx == -1 || b < get<2>(p[idx]) || b == get<2>(p[idx]) && a < get<1>(p[idx]) || b == get<2>(p[idx]) && a == get<1>(p[idx]) && i<idx)
                    idx = i;
            }
        }
        if(idx == -1 ){
            gantt.push_back({time,time+1,"Idle"});
            time++; continue;
        }
        auto &[nm,a,b,id] = p[idx];
        time = max(time,a);
        gantt.push_back({time,time+b,nm});
        ct[id] = time+b;
        tat[id] = ct[id] - a;
        wt[id] = tat[id] - b;
        time = ct[id];
        tTAT += tat[id], tWT += wt[id];
        done[id] = true;
        completed++;
    }
    cout<<"process\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i=0; i<n; i++){
        auto &[name,at,bt,id] = p[i];
        cout<<name<<'\t'<<at<<'\t'<<bt<<'\t'<<ct[id]<<'\t'<<tat[id]<<'\t'<<wt[id]<<'\n';
    }
    cout<<"\n\nGantt Chart: \n ";
    for(auto &[t,ct,nm]:gantt) cout<<"-------";
    cout<<"\n|";
    for(auto &[t,ct,nm]:gantt)cout<<setw(5)<<nm<<" |";
    cout<<"\n ";
    for(auto &[t,ct,nm]:gantt) cout<<"-------";
    cout<<"\n"<<get<0>(gantt[0]);
    for(auto &[t,ct,nm]:gantt){
        cout<<setw(7)<< ct;
    }
    cout<<"\n\nAverage Turnaround Time : "<<tTAT/n<<endl;
    cout<<"Average Waiting Time : "<<tWT/n<<endl;
}