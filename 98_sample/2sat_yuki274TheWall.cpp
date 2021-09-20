#include <bits/stdc++.h>
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define ALL(x) (x).begin(), (x).end()
#define REP(i, n) FOR(i,0,n)
#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)

namespace atcoder {
    namespace internal {

        template<class E>
        struct csr {
            std::vector<int> start;
            std::vector<E> elist;

            csr(int n, const std::vector<std::pair<int, E>> &edges)
                    : start(n + 1), elist(edges.size()) {
                for (auto e : edges) {
                    start[e.first + 1]++;
                }
                for (int i = 1; i <= n; i++) {
                    start[i] += start[i - 1];
                }
                auto counter = start;
                for (auto e : edges) {
                    elist[counter[e.first]++] = e.second;
                }
            }
        };

// Reference:
// R. Tarjan,
// Depth-First Search and Linear Graph Algorithms
        struct scc_graph {
        public:
            scc_graph(int n) : _n(n) {}

            int num_vertices() { return _n; }

            void add_edge(int from, int to) { edges.push_back({from, {to}}); }

            // @return pair of (# of scc, scc id)
            std::pair<int, std::vector<int>> scc_ids() {
                auto g = csr<edge>(_n, edges);
                int now_ord = 0, group_num = 0;
                std::vector<int> visited, low(_n), ord(_n, -1), ids(_n);
                visited.reserve(_n);
                auto dfs = [&](auto self, int v) -> void {
                    low[v] = ord[v] = now_ord++;
                    visited.push_back(v);
                    for (int i = g.start[v]; i < g.start[v + 1]; i++) {
                        auto to = g.elist[i].to;
                        if (ord[to] == -1) {
                            self(self, to);
                            low[v] = std::min(low[v], low[to]);
                        } else {
                            low[v] = std::min(low[v], ord[to]);
                        }
                    }
                    if (low[v] == ord[v]) {
                        while (true) {
                            int u = visited.back();
                            visited.pop_back();
                            ord[u] = _n;
                            ids[u] = group_num;
                            if (u == v) break;
                        }
                        group_num++;
                    }
                };
                for (int i = 0; i < _n; i++) {
                    if (ord[i] == -1) dfs(dfs, i);
                }
                for (auto &x : ids) {
                    x = group_num - 1 - x;
                }
                return {group_num, ids};
            }

            std::vector<std::vector<int>> scc() {
                auto ids = scc_ids();
                int group_num = ids.first;
                std::vector<int> counts(group_num);
                for (auto x : ids.second) counts[x]++;
                std::vector<std::vector<int>> groups(ids.first);
                for (int i = 0; i < group_num; i++) {
                    groups[i].reserve(counts[i]);
                }
                for (int i = 0; i < _n; i++) {
                    groups[ids.second[i]].push_back(i);
                }
                return groups;
            }

        private:
            int _n;
            struct edge {
                int to;
            };
            std::vector<std::pair<int, edge>> edges;
        };

    }  // namespace internal

    struct scc_graph {
    public:
        scc_graph() : internal(0) {}

        scc_graph(int n) : internal(n) {}

        void add_edge(int from, int to) {
            int n = internal.num_vertices();
            assert(0 <= from && from < n);
            assert(0 <= to && to < n);
            internal.add_edge(from, to);
        }

        std::vector<std::vector<int>> scc() { return internal.scc(); }

    private:
        internal::scc_graph internal;
    };

    struct two_sat {
    public:
        two_sat() : _n(0), scc(0) {}

        two_sat(int n) : _n(n), _answer(n), scc(2 * n) {}

        void add_clause(int i, bool f, int j, bool g) {
            assert(0 <= i && i < _n);
            assert(0 <= j && j < _n);
            scc.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
            scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
        }

        bool satisfiable() {
            auto id = scc.scc_ids().second;
            for (int i = 0; i < _n; i++) {
                if (id[2 * i] == id[2 * i + 1]) return false;
                _answer[i] = id[2 * i] < id[2 * i + 1];
            }
            return true;
        }

        std::vector<bool> answer() { return _answer; }

    private:
        int _n;
        std::vector<bool> _answer;
        internal::scc_graph scc;
    };
}

using namespace std;
using namespace atcoder;

// No.274 The Wall
// https://yukicoder.me/problems/no/274
int main(){
    int n, m; cin >> n >> m;
    two_sat ts(n);
    struct block{
        int l, r;
    };

    vector<block> dat(n);
    int l, r;
    REP(i, n){ cin >> l >> r; dat.at(i) = (block){l, r}; }

    // blockを横幅mの盤面でひっくり返す
    auto rotBlock = [&](block const b) {return (block {m - 1 - b.r, m - 1 - b.l});};
    // block1とblock2が重なるかを判定する
    auto isSafe = [](block const b1, block  const b2){
        return ((b1.r < b2.l) || (b2.r < b1.l));
    };

    REP(i, n){
        auto blockI = dat.at(i);
        FOR(j, i+1, n){
            auto blockJ = dat.at(j);
            // 例えば、true/trueでNGのとき、 false OR falseでないといけない。というような制約を列挙する。
            // 例えば、false/trueでNGのとき、 true OR falseでないといけないと制約する
            if(!isSafe(blockI, blockJ))                     ts.add_clause(i, false, j, false);
            if(!isSafe(rotBlock(blockI), blockJ))           ts.add_clause(i, true, j, false);
            if(!isSafe(blockI, rotBlock(blockJ)))           ts.add_clause(i, false, j, true);
            if(!isSafe(rotBlock(blockI), rotBlock(blockJ))) ts.add_clause(i, true, j, true);
        }
    }
    if(ts.satisfiable()) cout << "YES" << "\n";
    else cout << "NO" << "\n";
    return 0;
}

# if 0
int main(){

    int n, m; cin >> n >> m;
    int l, r;
    vector<pair<int, int>> dat(n);
    two_sat ts(n);
    REP(i, n){
        cin >> l >> r;
        dat.at(i) = make_pair(l, r);
    }
    bool canmake = true;
    REP(i, n){
        FOR(j, i+1, n){
            cout << "i:" << i << ",j:"<<j << "\n";
            if(!isSafe(dat.at(i).first, dat.at(i).second, dat.at(j).first, dat.at(j).second)){ // そのまま
                // そのままで衝突するなら
                if(isSafe((m-1) - dat.at(i).first, (m-1) - dat.at(i).second, dat.at(j).first, dat.at(j).second)){
                    // そのままではだめで、どちらかをひっくり返さないといけないのだから、
                    // 1:i, j のどっちかはそのままで AND 2:iかjのどっちかはひっくりかえっていないといけない
                    ts.add_clause(i, true, j, true); // 1
                    ts.add_clause(i, false, j, false); // 2
                    cout << "add ^i,j and i,^j" << "\n";
                } else {
                    // ひっくり返してもだめなら、だめな編を張る
                    canmake = false;
                    cout << "FALSE!";
                }
            } else {
                // そのままでOKの場合しないなら、
                if(!isSafe((m - 1) - dat[i].first, (m - 1) - dat[i].second, dat[j].first, dat[j].second)){
                    // そのままでOKで、ひっくり返すとだめならひっくり返してはならないのだから、
                    cout << "add i,j and ^i,^j" << "\n";
                    // 1: iか
                    ts.add_clause(i, true, j, false);
                    ts.add_clause(i, false, j, true);
                } else{
                    cout << "pass" << "\n";
                    // なにもしない(どうしても通るんだから制約はない)
                }
            }
        }
    }
    if(canmake){
        cout << "YES" << "\n";
    } else {
        cout << "NO" << "\n";
    }
    return 0;
}
#endif