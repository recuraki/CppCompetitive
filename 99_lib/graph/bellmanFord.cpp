#include <bits/stdc++.h>
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// #include <atcoder/all>
using namespace std;
using namespace __gnu_pbds;
using ll = long long int;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
#define SZ(x) ((int)(x).size())

#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)
#define FASTIOpre() cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);

// chmax/min: if update a then true
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define ceil(a,b) (((a) + ((b) - 1)) / (b))



/*
 * ダイクストラでコストを求める。
 * 未到達はINF
 * parentは s および 未到達が -1
 * findRouteはその前に実行したsolveの結果をもとに経路を返す
 * TODO: 現状、vectorにしているが、これはlistで返した方が早い(reverse分)
 */
template<typename T>
class bellmanFord{
public:
    struct edge{
        T cost;
        int nextnode;
    };

    const T INF = numeric_limits< T >::max();
    T mod = 1e9 + 7;

    vector<T> cost;
    using weight = pair<T, int>; // cost, nextNode = use edge and pq
    vector<vector<edge>> G;
    vector<int> parent;
    vector<int> pathnum;
    int nodeNum;
    int lastSource;

    bellmanFord(int nodeNum){
        this->G.resize(nodeNum);
        this->nodeNum = nodeNum;
        this->lastSource = -1;
    }

    void makeEdge(int curnode, int nextnode, T cost){
        this->G.at(curnode).emplace_back((edge){cost, nextnode});
    }
    bool solve(int nodeS, int nodeT){
        this->cost.resize(this->nodeNum, INF);
        this->cost[nodeS] = 0;
        REP(i, this->nodeNum){
            REP(curnode, this->nodeNum){
                for(edge &e: G.at(curnode)){
                    if(this->cost.at(curnode) == this->INF) continue;
                    auto nextCost = this->cost.at(curnode) + e.cost;
                    if(this->cost.at(e.nextnode) <= nextCost) continue;
                    this->cost.at(e.nextnode) = nextCost;
                    if(i == (this->nodeNum - 1) ) return false;
                }
            }
        }
        return true;
    }
};

// 標準
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=jp
void GRL_1_B(){
    int v, e, r; cin>>v>>e>>r;
    int s, t, d;
    bellmanFord<int> dj(v);
    REP(i, e){
        cin >>s>>t>>d;
        dj.makeEdge(s, t, d);
    }
    bool cansolve = dj.solve(r, r);
    if(!cansolve){
        cout << "NEGATIVE CYCLE" << "\n";
        return;
    }
    REP(i, v){
        if(dj.cost.at(i) == dj.INF) cout << "INF" << "\n";
        else cout << dj.cost.at(i) << "\n";
    }

}

using namespace std;
int main() {
    FASTIOpre();
    GRL_1_B();
}
