#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <stack>
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)


template<class T> inline bool chmin(T& a, T b) {if (a > b) {a = b; return true;} return false;}
template<class T> inline bool chmax(T& a, T b) {if (a < b) {a = b; return true;} return false;}

//////////////////////////////////////
#include <iostream>
using namespace std;
#define dp(arg) do { cout << #arg << ":"; dprint(arg); } while(0)

template <typename T> void dprint(T arg) { cout << arg << "\n"; }
template <typename T> void dprint(const vector<T>& arg) { for_each(begin(arg), end(arg), [](T value){ cout << value << " "; }   ); cout << "\n";  }
template <typename T> void dprint(const vector<vector<T>>& arg) { for_each(begin(arg), end(arg), [=](vector<T> arg2){ dprint(arg2); cout << "\n";} );  }


//////////////////////////////////////
#define ll long long int


// https://atcoder.jp/contests/abc204/tasks/abc204_c
// 根から配るDFS
vector<int> path;
vector<bool> visited;
vector<vector<int>> graph;

void abc204_c_DSF(int node){
    ++path.at(node);
    visited.at(node) = true;
    for(auto nextnode: graph.at(node)){
        if(!visited.at(nextnode))  abc204_c_DSF(nextnode);
    }
}

void abc204_c(){
    int n, m; cin >> n>> m;
    int a, b;
    path = vector<int>(n, 0);
    graph = vector<vector<int>>(n);
    REP(i, m){
        cin >> a >> b;
        --a; --b;
        graph.at(a).emplace_back(b);
    }
    stack<int> q;
    REP(i, n){
        visited = vector<bool>(n, false);
        abc204_c_DSF(i);
    }
    int res = 0;
    REP(i, n) res += path.at(i);
    cout << res << "\n";
}

int main(){
    abc204_c();
    return 0;
}