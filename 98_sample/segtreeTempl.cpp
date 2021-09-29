#include <bits/stdc++.h>
#include <chrono>

// #include <atcoder/all>
using namespace std;
using ll = long long int;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)
#define FASTIOpre() cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);

template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }

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


    template <class S, S (*op)(S, S), S (*e)()> struct segtree {
    public:
        segtree() : segtree(0) {}
        segtree(int n) : segtree(std::vector<S>(n, e())) {}
        segtree(const std::vector<S>& v) : _n(int(v.size())) {
            log = internal::ceil_pow2(_n);
            size = 1 << log;
            d = std::vector<S>(2 * size, e());
            for (int i = 0; i < _n; i++) d[size + i] = v[i];
            for (int i = size - 1; i >= 1; i--) {
                update(i);
            }
        }

        void set(int p, S x) {
            assert(0 <= p && p < _n);
            p += size;
            d[p] = x;
            for (int i = 1; i <= log; i++) update(p >> i);
        }

        S get(int p) {
            assert(0 <= p && p < _n);
            return d[p + size];
        }

        S prod(int l, int r) {
            assert(0 <= l && l <= r && r <= _n);
            S sml = e(), smr = e();
            l += size;
            r += size;


            while (l < r) {
                if (l & 1) sml = op(sml, d[l++]);
                if (r & 1) smr = op(d[--r], smr);
                l >>= 1;
                r >>= 1;
            }
            return op(sml, smr);
        }

        S all_prod() { return d[1]; }

        template <bool (*f)(S)> int max_right(int l) {
            return max_right(l, [](S x) { return f(x); });
        }
        template <class F> int max_right(int l, F f) {
            assert(0 <= l && l <= _n);
            assert(f(e()));
            if (l == _n) return _n;
            l += size;
            S sm = e();
            do {
                while (l % 2 == 0) l >>= 1;
                if (!f(op(sm, d[l]))) {
                    while (l < size) {
                        l = (2 * l);
                        if (f(op(sm, d[l]))) {
                            sm = op(sm, d[l]);
                            l++;
                        }
                    }
                    return l - size;
                }
                sm = op(sm, d[l]);
                l++;
            } while ((l & -l) != l);
            return _n;
        }

        template <bool (*f)(S)> int min_left(int r) {
            return min_left(r, [](S x) { return f(x); });
        }
        template <class F> int min_left(int r, F f) {
            assert(0 <= r && r <= _n);
            assert(f(e()));
            if (r == 0) return 0;
            r += size;
            S sm = e();
            do {
                r--;
                while (r > 1 && (r % 2)) r >>= 1;
                if (!f(op(d[r], sm))) {
                    while (r < size) {
                        r = (2 * r + 1);
                        if (f(op(d[r], sm))) {
                            sm = op(d[r], sm);
                            r--;
                        }
                    }
                    return r + 1 - size;
                }
                sm = op(d[r], sm);
            } while ((r & -r) != r);
            return 0;
        }

    private:
        int _n, size, log;
        std::vector<S> d;

        void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    };

}  // namespace atcoder


template<typename T>
class zatsuClass{
public:
    unordered_set<T> zatsu;
    unordered_map<T, int> zatsuTable;
    unordered_map<int, T> zatsuTableReverse;
    vector<T> zatsuAfter;

    vector<T> load(vector<T>& dat){
        vector<T> tmp;
        vector<T> res;
        // create all value uniq set
        REP(i, dat.size()) this->zatsu.template emplace(dat[i]);

        // create zatsu source list
        for(T x: zatsu) tmp.emplace_back(x);
        sort(tmp.begin(), tmp.end());

        // Create zatsu Table
        REP(i, tmp.size()) this->zatsuTable[tmp.at(i)] = i;
        REP(i, tmp.size()) this->zatsuTableReverse[i] = tmp.at(i);
        REP(i, dat.size()) res.emplace_back(zatsuTable[dat.at(i)]);

        return res;
    }

    vector<T> restore(vector<T>& dat){
        vector<T> res;
        for(T x: dat) res.template emplace_back(this->zatsuTableReverse[x]);
        return res;
    }

};

using namespace atcoder;
using ll = long long;

// 乗せる型と、opと、単位元e。
// eはlambdaで書くことに注意
struct takoyaki{ long double a,b; };
auto op = [](takoyaki x, takoyaki y){ return takoyaki{x.a * y.a, x.b * y.a + y.b }; };
auto e = []{ return takoyaki{1, 0}; };
int main(){
    cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);
    long double resMax = 1L, resMin = 1L;

    ll n,m; cin>>n>>m;

    vector<ll> ptmp(m);
    vector<long double> a(m), b(m);
    segtree<takoyaki, op, e> st(m);
    REP(i, m) { cin >> ptmp.at(i) >> a.at(i) >> b.at(i); }

    // 座標圧縮する
    zatsuClass<ll> zatsu;
    auto p = zatsu.load(ptmp);

    REP(i, m){
        st.set(p.at(i), takoyaki{a.at(i), b.at(i)});
        auto resTakoyaki = st.all_prod();
        auto resValue = resTakoyaki.a + resTakoyaki.b;
        resMax = max(resMax, resValue);
        resMin = min(resMin, resValue);
    }

    cout << resMin << "\n";
    cout << resMax << "\n";

    return 0;
}