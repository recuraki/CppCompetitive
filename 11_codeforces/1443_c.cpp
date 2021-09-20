#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

struct fast_ios { fast_ios(){ cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20); }; } fast_ios_;


#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
#define SZ(x) ((int)(x).size())

#define pb push_back
#define em emplace
#define mp make_pair
#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)

// chmax/min: if update a then true
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define ceil(a,b) ((a) + ((b) - 1)) / (b)


template <typename T1, typename T2> pair<T1, T2> operator+(const pair<T1, T2> &l, const pair<T1, T2> &r) { return make_pair(l.first + r.first, l.second + r.second); }
template <typename T1, typename T2> pair<T1, T2> operator-(const pair<T1, T2> &l, const pair<T1, T2> &r) { return make_pair(l.first - r.first, l.second - r.second); }


#ifndef KANAILOCAL
#define KANAILOCAL 1
#endif

//////////////////////////////////////
#define dp(arg) if(KANAILOCAL) { cout << #arg << ":"; dprint(arg); }
template <typename T> void dprint(T arg) { cout << arg << "\n"; }
template <typename T> void dprint(const vector<T>& arg) { for_each(begin(arg), end(arg), [](T value){ cout << value << " "; }   ); cout << "\n";  }
template <typename T> void dprint(const vector<vector<T>>& arg) { for_each(begin(arg), end(arg), [=](vector<T> arg2){ dprint(arg2); cout << "\n";} );  }
template <typename T> void dprint(const unordered_set<T>& arg) { for_each(begin(arg), end(arg), [](T value){ cout << value << " "; }   ); cout << "\n";  }
//#define dprint(arg) ;
//////////////////////////////////////
#define Yes std::cout << "Yes" << std::endl;
#define No std::cout << "No" << std::endl;
#define YES std::cout << "YES" << std::endl;
#define NO std::cout << "NO" << std::endl;
//////////////////////////////////////

using namespace std;

template <class T> struct cumSum1D{
public:
    vector<T> sdat;
    void load(vector<T> dat){
        this->sdat.resize(dat.size() + 1);
        this->sdat.at(0) = 0;
        for(int i = 0; i < dat.size(); i++){
            this->sdat.at(i + 1) = this->sdat.at(i) + dat.at(i);
        }
    };
    T query(int l, int r){
        /* Query [l, r)  //Close, Open */
        assert(l <= r);
        return(this->sdat[r] - this->sdat[l]);
    };
};

void cumSum1D_sample1(){
    vector<int> a = {1,2,3,4,5};
    cumSum1D<int> sum1D;
    sum1D.load(a);
    cout << sum1D.query(0,5) << endl;
    cout << sum1D.query(1,5) << endl;
    cout << sum1D.query(2,2) << endl;
    cout << sum1D.query(2,3) << endl;
    cout << sum1D.query(3,2) << endl;
}

ll solve(void){
    int n;
    cin >> n;
    ll x;
    vector<ll> data(n);
    vector<ll> datb(n);
    vector<tuple<ll, ll>> dat(n);
    vector<ll> buf(n);
    ll res = 10000000000000000;

    ll a,b;
    REP(i,n){ cin >> x; data.at(i) = x; }
    REP(i,n){ cin >> x; datb.at(i) = x; }
    REP(i,n){ dat.at(i) = tie(data.at(i), datb.at(i) ); }
    sort(ALL(dat));
    REP(i,n){ tie(a,b) = dat[i]; buf.at(i) = b;}

    cumSum1D<ll> sum1D;
    sum1D.load(buf);

    REP(i,n){
        tie(a,b) = dat[i];
        res = min(res, max(a, sum1D.query(i + 1, n)));
    }
    res = min(res, sum1D.query(0, n));
    return res;
}

int main() {
    fast_ios();
    int qq;
    cin >> qq;
    REP(i, qq){
        cout << solve() << endl;
    }

}