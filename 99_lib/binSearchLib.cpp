#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

// https://algo-method.com/submissions/92500
/*
 * 実数領域のbinsearch。l,rが1e-9の誤差になるまで回した答え
 */
template <class S,  bool (*binsearch)(const S&, const long double&)>
struct binsearchLongDouble {
    long double gosa = 1e-9;
    double solve(long double bsmin, long double bsmax, const S &argval){
        while( (bsmax - bsmin) > gosa){
            long double mid = (bsmax + bsmin) / 2.0L;
            if(binsearch(argval, mid)) bsmin = mid;
            else bsmax = mid;
        }
        return bsmin;
    }
};

template <class S,  bool (*binsearch)(const S&, const long long&)>
struct binsearchLongLong {
    // [ok, ng) for max value いける最大の値を求めたいとき
    // (ng, ok] for min value 可能となる最小の値を出したいとき
    // CATION: ok is result  (NOT mid)
    long long solve(long long ok, long long ng, const S &argval){
        while(abs(ok - ng) > 1){
            long long mid = (ok + ng) / 2;
            if(binsearch(argval, mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }
};
//////////////////////////////////////////////////////
struct abc146cargstruct{
    ll a, b, x;
};
bool abc146condition(const abc146cargstruct &arg, const long long &mid){
    string s = to_string(mid);
    ll val = arg.a * mid + arg.b * (ll)s.size();
    return(val <= arg.x);
}

void abc146(){
    // abc146_c
    cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);
    ll a, b, x;
    cin >> a >> b >> x;
    abc146cargstruct args = {a, b, x};
    binsearchLongLong<abc146cargstruct, abc146condition> bsll;
    cout << bsll.solve(0, 1e9+1, args) << "\n";
}
//////////////////////////////////////////////////////
struct abc207bargstruct{
    ll a, b, c, d;
};
bool abc207bcondition(const abc207bargstruct &arg, const long long &mid){
    return(arg.a+(arg.b*mid) <= (arg.c*mid)*arg.d);
}

void abc207b(){
    // abc146_c
    cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);
    ll a, b, c, d ;
    cin >> a >> b >> c >> d;
    abc207bargstruct args = {a, b, c, d};
    binsearchLongLong<abc207bargstruct, abc207bcondition> bsll;
    auto res = bsll.solve(1e6, 0, args);
    if(res == 1e6) cout << -1<< "\n";
    else cout << res << "\n";
}

//////////////////////////////////////////////////////
// https://algo-method.com/tasks/368
// binsearchにいろんな定数を渡せるように引数はargstructという構造体にする
struct algo368argstruct{ // 引数
    int n;
};

// binsearchで呼ばれる判断式。中で、arg.nをうまく使う
bool algo368condition(const algo368argstruct &arg, const long double &mid){
    return( (mid* (mid* (mid+ 1 ) + 2 ) + 3) < arg.n);
}

void algo368(){
    cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);
    int n; cin >>n;
    algo368argstruct x; x.n = n;
    binsearchLongDouble<algo368argstruct, algo368condition> bsd;
    cout << bsd.solve(0, 100, x) << "\n";

}
//////////////////////////////////////////////////////
int main() {
    //algo368();
    //abc146();
    abc207b();
}

