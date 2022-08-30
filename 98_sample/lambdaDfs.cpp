#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <stack>
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
using namespace std;
#define ll long long int

void simple(){
    auto test = [&](auto &&self, int x, int cur) -> int{
        if(x <= 0) return 0;
        cur += x + self(self, x-1, cur);
        return cur;
    };
    cout << test(test, 10, 0) << "\n";
}

// https://atcoder.jp/contests/abc204/tasks/abc204_c
// 根から配るDFS
void abc204_c(){
    int n, m; cin >> n>> m;
    int a, b;

    vector<int> path(n, 0);
    vector<bool> visited;
    vector<vector<int>> graph(n);

    REP(i, m){
        cin >> a >> b;
        --a; --b;
        graph.at(a).emplace_back(b);
    }
    auto dfs = [&](auto && self, int node) -> void{
        ++path.at(node);
        visited.at(node) = true;
        for(auto nextnode: graph.at(node)){
            if(!visited.at(nextnode)) self(self, nextnode);
        }
    };
    REP(i, n){
        visited = vector<bool>(n, false);
        dfs(dfs, i);
    }
    int res = 0;
    REP(i, n) res += path.at(i);
    cout << res << "\n";
}

int main(){
    //abc204_c();
    simple();
    return 0;
}