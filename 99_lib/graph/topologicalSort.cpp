//
// Created by kanai on 2022/02/13.
//
#include <bits/stdc++.h>
//#include <chrono>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

// #include <atcoder/all>
using namespace std;

/*
 * トポロジカルソートをする。  0 - (n-1)を取り
 * トポロジカルソートされたvector<int>を返す
 */
struct topologicalSort{
public:
    int n;
    vector<vector<int>> g;
    vector<int> edgeNum;
    vector<int> ans;
    topologicalSort(int nin){
        n = nin;
        g = vector<vector<int>>(n, vector<int>());
        edgeNum = vector<int>(n);
    }
    void makeEdge(const int &u, const int &v){
        g[u].emplace_back(v);
        ++edgeNum[v]; // in-edgeを足す
    }
    void solve(){
        ans.clear();
        deque<int> q;
        // incount 0? then qにいれて、ansにいれる
        for(int i = 0; i < n; ++i){
            if(edgeNum[i] != 0) continue;
            q.push_front(i);
            ans.push_back(i);
        }
        while(q.size() > 0){
            auto cur = q.front(); q.pop_front();
            for(auto &next: g.at(cur)){
                --edgeNum.at(next);
                if(edgeNum.at(next) == 0){
                    ans.push_back(next);
                    q.push_back(next);
                }
            }

        }
    }
};

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B&lang=ja
void GRL4B(){
    int numv, nume; cin >> numv >> nume;
    topologicalSort ts(numv);
    for(int i = 0; i  < nume; ++i){
        int u, v; cin >> u >> v;
        ts.makeEdge(u, v);
    }
    ts.solve();
    for(auto &x: ts.ans){
        cout << x << "\n";
    }
    cout << endl;
}

int main(){
    GRL4B();
}