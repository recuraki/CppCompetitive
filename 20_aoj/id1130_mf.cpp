#include <bits/stdc++.h>

#include <algorithm>
#include <array>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder {

    namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
        int ceil_pow2(int n) {
            int x = 0;
            while ((1U << x) < (unsigned int)(n)) x++;
            return x;
        }

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
        int bsf(unsigned int n) {
#ifdef _MSC_VER
            unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
            return __builtin_ctz(n);
#endif
        }

    }  // namespace internal

}  // namespace atcoder



#include <utility>

namespace atcoder {

    namespace internal {

// @param m `1 <= m`
// @return x mod m
        constexpr long long safe_mod(long long x, long long m) {
            x %= m;
            if (x < 0) x += m;
            return x;
        }

// Fast modular multiplication by barrett reduction
// Reference: https://en.wikipedia.org/wiki/Barrett_reduction
// NOTE: reconsider after Ice Lake
        struct barrett {
            unsigned int _m;
            unsigned long long im;

            // @param m `1 <= m < 2^31`
            barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}

            // @return m
            unsigned int umod() const { return _m; }

            // @param a `0 <= a < m`
            // @param b `0 <= b < m`
            // @return `a * b % m`
            unsigned int mul(unsigned int a, unsigned int b) const {
                // [1] m = 1
                // a = b = im = 0, so okay

                // [2] m >= 2
                // im = ceil(2^64 / m)
                // -> im * m = 2^64 + r (0 <= r < m)
                // let z = a*b = c*m + d (0 <= c, d < m)
                // a*b * im = (c*m + d) * im = c*(im*m) + d*im = c*2^64 + c*r + d*im
                // c*r + d*im < m * m + m * im < m * m + 2^64 + m <= 2^64 + m * (m + 1) < 2^64 * 2
                // ((ab * im) >> 64) == c or c + 1
                unsigned long long z = a;
                z *= b;
#ifdef _MSC_VER
                unsigned long long x;
        _umul128(z, im, &x);
#else
                unsigned long long x =
                        (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
                unsigned int v = (unsigned int)(z - x * _m);
                if (_m <= v) v += _m;
                return v;
            }
        };

// @param n `0 <= n`
// @param m `1 <= m`
// @return `(x ** n) % m`
        constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
            if (m == 1) return 0;
            unsigned int _m = (unsigned int)(m);
            unsigned long long r = 1;
            unsigned long long y = safe_mod(x, m);
            while (n) {
                if (n & 1) r = (r * y) % _m;
                y = (y * y) % _m;
                n >>= 1;
            }
            return r;
        }

// Reference:
// M. Forisek and J. Jancina,
// Fast Primality Testing for Integers That Fit into a Machine Word
// @param n `0 <= n`
        constexpr bool is_prime_constexpr(int n) {
            if (n <= 1) return false;
            if (n == 2 || n == 7 || n == 61) return true;
            if (n % 2 == 0) return false;
            long long d = n - 1;
            while (d % 2 == 0) d /= 2;
            constexpr long long bases[3] = {2, 7, 61};
            for (long long a : bases) {
                long long t = d;
                long long y = pow_mod_constexpr(a, t, n);
                while (t != n - 1 && y != 1 && y != n - 1) {
                    y = y * y % n;
                    t <<= 1;
                }
                if (y != n - 1 && t % 2 == 0) {
                    return false;
                }
            }
            return true;
        }
        template <int n> constexpr bool is_prime = is_prime_constexpr(n);

// @param b `1 <= b`
// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
        constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
            a = safe_mod(a, b);
            if (a == 0) return {b, 0};

            // Contracts:
            // [1] s - m0 * a = 0 (mod b)
            // [2] t - m1 * a = 0 (mod b)
            // [3] s * |m1| + t * |m0| <= b
            long long s = b, t = a;
            long long m0 = 0, m1 = 1;

            while (t) {
                long long u = s / t;
                s -= t * u;
                m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b

                // [3]:
                // (s - t * u) * |m1| + t * |m0 - m1 * u|
                // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)
                // = s * |m1| + t * |m0| <= b

                auto tmp = s;
                s = t;
                t = tmp;
                tmp = m0;
                m0 = m1;
                m1 = tmp;
            }
            // by [3]: |m0| <= b/g
            // by g != b: |m0| < b/g
            if (m0 < 0) m0 += b / s;
            return {s, m0};
        }

// Compile time primitive root
// @param m must be prime
// @return primitive root (and minimum in now)
        constexpr int primitive_root_constexpr(int m) {
            if (m == 2) return 1;
            if (m == 167772161) return 3;
            if (m == 469762049) return 3;
            if (m == 754974721) return 11;
            if (m == 998244353) return 3;
            int divs[20] = {};
            divs[0] = 2;
            int cnt = 1;
            int x = (m - 1) / 2;
            while (x % 2 == 0) x /= 2;
            for (int i = 3; (long long)(i)*i <= x; i += 2) {
                if (x % i == 0) {
                    divs[cnt++] = i;
                    while (x % i == 0) {
                        x /= i;
                    }
                }
            }
            if (x > 1) {
                divs[cnt++] = x;
            }
            for (int g = 2;; g++) {
                bool ok = true;
                for (int i = 0; i < cnt; i++) {
                    if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                        ok = false;
                        break;
                    }
                }
                if (ok) return g;
            }
        }
        template <int m> constexpr int primitive_root = primitive_root_constexpr(m);

    }  // namespace internal

}  // namespace atcoder


#include <algorithm>

#include <vector>

namespace atcoder {

    namespace internal {

        template <class T> struct simple_queue {
            std::vector<T> payload;
            int pos = 0;
            void reserve(int n) { payload.reserve(n); }
            int size() const { return int(payload.size()) - pos; }
            bool empty() const { return pos == int(payload.size()); }
            void push(const T& t) { payload.push_back(t); }
            T& front() { return payload[pos]; }
            void clear() {
                payload.clear();
                pos = 0;
            }
            void pop() { pos++; }
        };

    }  // namespace internal

}  // namespace atcoder

#include <cassert>
#include <limits>
#include <queue>
#include <vector>

namespace atcoder {

    template <class Cap> struct mf_graph {
    public:
        mf_graph() : _n(0) {}
        mf_graph(int n) : _n(n), g(n) {}

        int add_edge(int from, int to, Cap cap) {
            assert(0 <= from && from < _n);
            assert(0 <= to && to < _n);
            assert(0 <= cap);
            int m = int(pos.size());
            pos.push_back({from, int(g[from].size())});
            int from_id = int(g[from].size());
            int to_id = int(g[to].size());
            if (from == to) to_id++;
            g[from].push_back(_edge{to, to_id, cap});
            g[to].push_back(_edge{from, from_id, 0});
            return m;
        }

        struct edge {
            int from, to;
            Cap cap, flow;
        };

        edge get_edge(int i) {
            int m = int(pos.size());
            assert(0 <= i && i < m);
            auto _e = g[pos[i].first][pos[i].second];
            auto _re = g[_e.to][_e.rev];
            return edge{pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};
        }
        std::vector<edge> edges() {
            int m = int(pos.size());
            std::vector<edge> result;
            for (int i = 0; i < m; i++) {
                result.push_back(get_edge(i));
            }
            return result;
        }
        void change_edge(int i, Cap new_cap, Cap new_flow) {
            int m = int(pos.size());
            assert(0 <= i && i < m);
            assert(0 <= new_flow && new_flow <= new_cap);
            auto& _e = g[pos[i].first][pos[i].second];
            auto& _re = g[_e.to][_e.rev];
            _e.cap = new_cap - new_flow;
            _re.cap = new_flow;
        }

        Cap flow(int s, int t) {
            return flow(s, t, std::numeric_limits<Cap>::max());
        }
        Cap flow(int s, int t, Cap flow_limit) {
            assert(0 <= s && s < _n);
            assert(0 <= t && t < _n);
            assert(s != t);

            std::vector<int> level(_n), iter(_n);
            internal::simple_queue<int> que;

            auto bfs = [&]() {
                std::fill(level.begin(), level.end(), -1);
                level[s] = 0;
                que.clear();
                que.push(s);
                while (!que.empty()) {
                    int v = que.front();
                    que.pop();
                    for (auto e : g[v]) {
                        if (e.cap == 0 || level[e.to] >= 0) continue;
                        level[e.to] = level[v] + 1;
                        if (e.to == t) return;
                        que.push(e.to);
                    }
                }
            };
            auto dfs = [&](auto self, int v, Cap up) {
                if (v == s) return up;
                Cap res = 0;
                int level_v = level[v];
                for (int& i = iter[v]; i < int(g[v].size()); i++) {
                    _edge& e = g[v][i];
                    if (level_v <= level[e.to] || g[e.to][e.rev].cap == 0) continue;
                    Cap d =
                            self(self, e.to, std::min(up - res, g[e.to][e.rev].cap));
                    if (d <= 0) continue;
                    g[v][i].cap += d;
                    g[e.to][e.rev].cap -= d;
                    res += d;
                    if (res == up) break;
                }
                return res;
            };

            Cap flow = 0;
            while (flow < flow_limit) {
                bfs();
                if (level[t] == -1) break;
                std::fill(iter.begin(), iter.end(), 0);
                while (flow < flow_limit) {
                    Cap f = dfs(dfs, t, flow_limit - flow);
                    if (!f) break;
                    flow += f;
                }
            }
            return flow;
        }

        std::vector<bool> min_cut(int s) {
            std::vector<bool> visited(_n);
            internal::simple_queue<int> que;
            que.push(s);
            while (!que.empty()) {
                int p = que.front();
                que.pop();
                visited[p] = true;
                for (auto e : g[p]) {
                    if (e.cap && !visited[e.to]) {
                        visited[e.to] = true;
                        que.push(e.to);
                    }
                }
            }
            return visited;
        }

    private:
        int _n;
        struct _edge {
            int to, rev;
            Cap cap;
        };
        std::vector<std::pair<int, int>> pos;
        std::vector<std::vector<_edge>> g;
    };

}  // namespace atcoder



#include <cassert>
#include <vector>


#include <algorithm>
#include <cassert>
#include <vector>


using namespace std;
using namespace atcoder;
#define ll long long
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

void solve(){
    int h, w;
    vector<vector<char>> maze;
    vector<int> dh = {-1, 0, 0, 1};
    vector<int> dw = {0, -1, 1, 0};
    int curh, curw;
    map<long, int> lst;
    char c;
    while(true){
        cin >> w >> h;
        lst.clear();
        if(h==0 && w==0) break;
        maze = vector<vector<char>>(h + 2, vector<char>(w + 2, '#'));
        REP(i, w) maze[0][i] = '#';
        FOR(hh, 1, h + 1){
            FOR(ww, 1, w + 1){
                cin >> c;
                if(c == '@'){
                    curh = hh;
                    curw = ww;
                    c = '.';
                }
                maze[hh][ww] = c;
            }
        }
        REP(i, w) maze[h+1][i] = '#';
        // ここからgraphを作る
        int nodenum = (w+2) * (h+2) + 2;
        int nodes = nodenum - 2;
        int nodet = nodenum - 1;
        auto hw2num = [&](int hh, int ww){ return hh * (w+2) + ww; };
        mf_graph<int> mf(nodenum);
        int edgenum = 0;
        REP(hh, h+2){
            REP(ww, w+2){
                if(maze[hh][ww] == '#') continue;
                mf.add_edge(hw2num(hh, ww), nodet, 1);
                lst[hh*1e12 + ww*1e9] = edgenum;
                ++edgenum;
                REP(di, dh.size()){
                    mf.add_edge(hw2num(hh, ww), hw2num(hh+dh[di], ww+dw[di]), h*w);
                    lst[hh*1e12 + ww*1e9 + (hh+dh[di]) * 1e6  + (ww+dw[di]) * 1e3] = edgenum;
                    ++edgenum;

                }
            }
            mf.add_edge(nodes, hw2num(curh, curw), h*w);
        }
        cout << mf.flow(nodes, nodet) << "\n";
        cout << mf.flow(nodes, nodet) << "\n";
        vector<int> dameh = {5, 5};
        vector<int> damew = {10, 11};
        REP(i, dameh.size()){
            auto hh = dameh.at(i);
            auto ww = damew.at(i);
            REP(di, dh.size()){
                auto targetedge = hh*1e12 + ww*1e9 + (hh+dh[di]) * 1e6  + (ww+dw[di]) * 1e3;
                cout << "change node" << targetedge << "\n";
                cout << flush;
                mf.change_edge(lst[targetedge], 0, 0);
            }
            cout << mf.flow(nodes, nodet) << "\n";

        }

    }

}

int main(int argc, char *argv[]) {
    solve();
    return 0;
}