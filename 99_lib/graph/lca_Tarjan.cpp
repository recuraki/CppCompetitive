/*
 * オフラインなLCAクエリ https://www.geeksforgeeks.org/tarjans-off-line-lowest-common-ancestors-algorithm/
 * Tarjan’s off-line lowest common ancestors algorithm
 *
 * Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=jp
 */


#include <bits/stdc++.h>
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
using namespace std;
using ll = long long int;

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
        // otherwise: parent
        std::vector<int> parent_or_size;
    };

}  // namespace atcoder


/****************************************************/
int main(int argc, char *argv[]) {
    int n; cin >> n;
    vector<vector<int>> g(n, vector<int>());
    vector<pair<int, int>> queries;
    vector<vector<int>> sakiyomi(n);
    vector<map<int, int>> ans(n);
    vector<int> topnode(n, -1);

    REP(i, n){
        int k; cin >> k;
        REP(j, k){
            int c;
            cin >> c;
            g.at(i).push_back(c);
        }
    }

    int q; cin >> q;
    REP(i, q){
        int u, v; cin >> u >> v;
        queries.push_back({u, v});
        sakiyomi.at(u).push_back(v); sakiyomi.at(v).push_back(u);
    }

    atcoder::dsu uf(n);

    auto dfs = [&](auto && self, int curnode, int parent) -> void{
        // まずは子のノードを辿る
        for(auto nextnode: g.at(curnode)) self(self, nextnode, curnode);

        // pairのグラフが先に帰りがけの処理をされていた場合はそのノードのtopがLCA
        for(auto pairnode: sakiyomi.at(curnode)){
            ans.at(curnode)[pairnode] = topnode.at(uf.leader(pairnode));
            ans.at(pairnode)[curnode] = topnode.at(uf.leader(pairnode));
        }

        // 戻り掛けの処理
        if(parent != -1) {
            // 今いるノードと親をmergeする。この際、今いるノードの部分木のtopは全てparentに変更する。
            uf.merge(curnode, parent);
            topnode.at(uf.leader(curnode)) = parent;
        }

    };
    dfs(dfs, 0, -1);

    REP(i, n) ans.at(i)[i] = i; // u == vのとき
    for(auto &[u, v]: queries) cout << ans.at(u)[v] << "\n";
}


