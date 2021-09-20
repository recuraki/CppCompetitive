#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
using ll = long long int;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
#define SZ(x) ((int)(x).size())

#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)

// chmax/min: if update a then true
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define ceil(a,b) ((a) + ((b) - 1)) / (b)

template <typename T1, typename T2> pair<T1, T2> operator+(const pair<T1, T2> &l, const pair<T1, T2> &r) { return make_pair(l.first + r.first, l.second + r.second); }
template <typename T1, typename T2> pair<T1, T2> operator-(const pair<T1, T2> &l, const pair<T1, T2> &r) { return make_pair(l.first - r.first, l.second - r.second); }

//////////////////////////////////////
#define dp(arg) if(KANAILOCAL) { cout << #arg << ":"; dprint(arg); }
template <typename T> void dprint(T arg) { cout << arg << "\n"; }
template <typename T> void dprint(const vector<T>& arg) { for_each(begin(arg), end(arg), [](T value){ cout << value << " "; }   ); cout << "\n";  }
template <typename T> void dprint(const vector<vector<T>>& arg) { for_each(begin(arg), end(arg), [=](vector<T> arg2){ dprint(arg2); cout << "\n";} );  }
template <typename T> void dprint(const unordered_set<T>& arg) { for_each(begin(arg), end(arg), [](T value){ cout << value << " "; }   ); cout << "\n";  }
template <typename T1, typename T2> void dprint(const unordered_map<T1,T2>& arg) { for_each(begin(arg), end(arg), [](auto & x){ cout << x.first << "_" << x.second << " "; }   ); cout << "\n";  }
//////////////////////////////////////
#define Yes std::cout << "Yes" << std::endl;
#define No std::cout << "No" << std::endl;
#define YES std::cout << "YES" << std::endl;
#define NO std::cout << "NO" << std::endl;
//////////////////////////////////////

using namespace std;
int main() {
    FASTIO();
    int n, k;
    cin >> n >> k;
    int x;
    unordered_map<int, int> buf;
    REP(i, n) { cin >> x; buf[x] ++; }
    int i = 0;
    int canPass;
    int res = 0;
    while(k > 0){
        canPass = min(buf[i], k);
        res += i * (k - canPass);
        k = canPass;
        ++i;
    }
    cout << res << "\n";

}
