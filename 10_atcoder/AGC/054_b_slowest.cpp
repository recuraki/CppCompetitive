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

template <typename T1, typename T2> pair<T1, T2> operator+(const pair<T1, T2> &l, const pair<T1, T2> &r) { return make_pair(l.first + r.first, l.second + r.second); }
template <typename T1, typename T2> pair<T1, T2> operator-(const pair<T1, T2> &l, const pair<T1, T2> &r) { return make_pair(l.first - r.first, l.second - r.second); }

//////////////////////////////////////

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
//unordered_map<long long, int, custom_hash> safe_map;
//gp_hash_table<long long, int, custom_hash> safe_hash_table;

#define Yes std::cout << "Yes" << std::endl;
#define No std::cout << "No" << std::endl;
#define YES std::cout << "YES" << std::endl;
#define NO std::cout << "NO" << std::endl;

template <typename T> void resprint(const vector<T>& arg) { for(int i=0; i < (int)arg.size() - 1; ++i) {cout << arg.at(i) << " ";} cout << arg[arg.size()-1] << "\n";};
//////////////////////////////////////

ll mod = 998244353LL;

ll myfact(int n){
    ll x = 1;
    FOR(i, 1, n+1){
        x = (x * i) ;
        x %= mod;
    }
    return x;
}

using namespace std;
int main() {
    FASTIOpre();
    ll n;
    cin >> n;
    vector<ll> dat(n);
    ll total = 0;
    ll x;
    REP(i, n){
        cin >> x;
        total += x;
        dat.at(i) = x;
    }
    if(total % 2 == 1){
        cout << 0 << "\n";
        return 0;
    }
    vector<vector<vector<ll>>> dp(110, vector<vector<ll>>(10200, vector<ll>(110, 0LL)));
    dp.at(0).at(0).at(0) = 1LL;
    REP(i, n){
        REP(value, 5100){
            REP(cnt, i + 1){
                dp.at(i + 1).at(value).at(cnt) += dp.at(i).at(value).at(cnt);
                dp.at(i + 1).at(value).at(cnt) %= mod;
                if(value+dat[i] > 5100) continue;
                dp.at(i + 1).at(value + dat.at(i)).at(cnt + 1) += dp.at(i).at(value).at(cnt);
                dp.at(i + 1).at(value + dat.at(i)).at(cnt + 1) %= mod;
            }
        }
    }

    ll res = 0;
    ll tmp = 0;

    FOR(i, 0, n){
        if(dp.at(n).at(total / 2).at(i) != 0){
            tmp =  ((myfact(i) * myfact(n-i)) % mod) * dp.at(n).at(total / 2).at(i);
            res += tmp;
            res %= mod;
        }
    }
    cout << res % mod<< "\n";


}
