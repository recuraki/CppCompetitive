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

//////////////////////////////////////
#define dp(arg) if(KANAILOCAL) { cerr << #arg << ":"; dprint(arg); }
template <typename T> void dprint(T arg) { cout << arg << "\n"; }
template <typename T> void dprint(const vector<T>& arg) { for_each(begin(arg), end(arg), [](T value){ cout << value << " "; }   ); cout << "\n";  }
template <typename T> void dprint(const vector<vector<T>>& arg) { for_each(begin(arg), end(arg), [=](vector<T> arg2){ dprint(arg2); cout << "\n";} );  }
template <typename T> void dprint(const unordered_set<T>& arg) { for_each(begin(arg), end(arg), [](T value){ cout << value << " "; }   ); cout << "\n";  }
template <typename T1, typename T2> void dprint(const unordered_map<T1,T2>& arg) { for_each(begin(arg), end(arg), [](auto & x){ cout << x.first << ":" << x.second << " "; }   ); cout << "\n";  }
template <typename T1, typename T2> void dprint(const vector<pair<T1,T2>>& arg) { for_each(begin(arg), end(arg), [](auto & x){ cout << x.first << ":" << x.second << " "; }   ); cout << "\n";  }
//////////////////////////////////////
#define Yes std::cout << "Yes" << std::endl;
#define No std::cout << "No" << std::endl;
#define YES std::cout << "YES" << std::endl;
#define NO std::cout << "NO" << std::endl;

template <typename T> void resprint(const vector<T>& arg) { for(int i=0; i < (int)arg.size() - 1; ++i) {cout << arg.at(i) << " ";} cout << arg[arg.size()-1] << "\n";};
//////////////////////////////////////

void inputSample(){
#if 0
    string s; cin.ignore();
    getline(cin, s);
    int n,c;
    cin >> n >> c;
    int x; vector<int> dat(n); REP(i, n){cin >> x; dat.at(i) = x;}
    //   vector<vector<int>> data(3, vector<int>(4));
#endif
}

using namespace std;
int main() {
    FASTIOpre();


}
