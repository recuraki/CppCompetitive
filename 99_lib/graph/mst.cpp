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






namespace atcoder {

    // Implement (union by size) + (path compression)
    // Reference:
    // Zvi Galil and Giuseppe F. Italiano,
    // Data structures and algorithms for disjoint set union problems
    struct dsu {
    public:
        dsu() : _n(0) {}
        dsu(int n) : _n(n), parent_or_size(n, -1) {}

        int merge(int a, int b) {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            int x = leader(a), y = leader(b);
            if (x == y) return x;
            if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
            parent_or_size[x] += parent_or_size[y];
            parent_or_size[y] = x;
            return x;
        }

        bool same(int a, int b) {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            return leader(a) == leader(b);
        }

        int leader(int a) {
            assert(0 <= a && a < _n);
            if (parent_or_size[a] < 0) return a;
            return parent_or_size[a] = leader(parent_or_size[a]);
        }

        int size(int a) {
            assert(0 <= a && a < _n);
            return -parent_or_size[leader(a)];
        }

        std::vector<std::vector<int>> groups() {
            std::vector<int> leader_buf(_n), group_size(_n);
            for (int i = 0; i < _n; i++) {
                leader_buf[i] = leader(i);
                group_size[leader_buf[i]]++;
            }
            std::vector<std::vector<int>> result(_n);
            for (int i = 0; i < _n; i++) {
                result[i].reserve(group_size[i]);
            }
            for (int i = 0; i < _n; i++) {
                result[leader_buf[i]].push_back(i);
            }
            result.erase(
                    std::remove_if(result.begin(), result.end(),
                                   [&](const std::vector<int>& v) { return v.empty(); }),
                    result.end());
            return result;
        }

    private:
        int _n;
        // root node: -1 * component size
        // otherwise: parentRealnode
        std::vector<int> parent_or_size;
    };

}  // namespace atcoder



using namespace atcoder;
/*
 * クラシカル法: 最小全域木を作る(プリムより早い)
 * makeedgeで木を作った後に
 */
struct edge{
    int nodeS;
    int nodeT;
    int cost;
    bool used;
    bool operator < (const edge& b) const{
        return cost < b.cost;
    }
};
template<typename T>
class kruskal{
public:
    int nodeNum;
    vector<edge> edges;
    kruskal(int nodeNum){
        this->nodeNum = nodeNum;
    }
    void makeEdge(int curnode, int nextnode, T cost){
        edges.template emplace_back((edge){curnode, nextnode, cost, false});
    }
    T solve(){
        sort(edges.begin(), edges.end());
        dsu uf(this->nodeNum);
        T res = (T)0;

        for(edge &e: this->edges){
            if(uf.same(e.nodeS, e.nodeT)) continue;
            res += e.cost;
            uf.merge(e.nodeS, e.nodeT);
            e.used = true;
        }
        return res;
    }
};

//GRL_2_A
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja
void GRL_2_A(){
    int v, e; cin >> v >> e;
    int s, t, w;
    kruskal<int> mst(v);
    REP(i, e){
        cin >>s>>t>>w;
        mst.makeEdge(s,t,w);
    }
    auto res = mst.solve();
    cout << res << "\n";
    /*
    for( edge &e: mst.edges){
        if(e.used) cout << e.nodeS << "->" << e.nodeT << " cost: " << e.cost << "\n";
    }
     */
}

using namespace std;
int main() {
    FASTIOpre();
    GRL_2_A();
}
