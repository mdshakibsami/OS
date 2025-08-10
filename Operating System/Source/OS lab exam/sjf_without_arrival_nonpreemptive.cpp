#include<bits/stdc++.h>
using namespace std;
int main(){
    ifstream file("sjf_without_arrival_nonpreemptive.txt");
    int n;
    file>>n;
    vector<tuple<string,int,int>>p(n);
    for(int i=0;i<n;i++){
        auto &[process,bt,idx]=p[i];
        file>>process>>bt;
        idx=i;
    }
    vector<int>bt(n),ct(n),tat(n),wt(n);
    vector<string>name(n);
    int time =0;
    float tTAT=0, tWT =0;

    sort(p.begin(),p.end(), [](auto &a, auto &b){return get<1>(a) < get<1>(b);});

    for(auto &[num,b,idx]:p){
        time += b;
        ct[idx]=time;
        name[idx] = num;
        bt[idx] = b;
        tat[idx] = ct[idx];
        wt[idx] = tat[idx] - b;
        tWT += wt[idx], tTAT += tat[idx];
    }

    cout<<"process\tBT\tCT\tTAT\tWT\n";
    for(int i=0;i<n;i++){
        cout<<name[i]<<'\t'<<bt[i]<<'\t'<<ct[i]<<'\t'<<tat[i]<<'\t'<<wt[i]<<endl;
    }

    cout<<"\n\ngantt chart : \n ";
    for(int i=0;i<n;i++) cout<<"-------";
    cout<<"\n|";
    for(auto &[nm,b,idx]:p) cout<<setw(4)<<nm<<"  |";
    cout<<"\n ";
    for(int i=0;i<n;i++) cout<<"-------";
    cout<<"\n0";
    for(auto &[nm,b,idx]:p) cout<<setw(7)<<ct[idx];

    cout<<"\n\nAverage Turnaround Time : "<<(tTAT/n);
    cout<<"\nAverage Waiting Time : "<<(tWT/n);

}