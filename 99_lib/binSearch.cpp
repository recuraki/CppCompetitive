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

void basic(){

}

void abc146_c(){
    // abc146_c
    ll a, b, x, mid;
    cin >> a >> b >> x;
    auto func = [&](ll &trynum){
        string s = to_string(trynum);
        ll val = a * trynum + b * (ll)s.size();
        if(val <= x) return true;
        return false;
    };
    // [ok, ng) for max value いける最大の値を求めたいとき
    // (ng, ok] for min value 可能となる最小の値を出したいとき
    // CATION: ok is result  (NOT mid)
    ll ok = 0;
    ll ng = 1e9 + 1;
    while(abs(ok - ng) > 1){
        mid = (ok + ng) / 2;
        if(func(mid)) ok = mid;
        else ng = mid;
    }
    cout << ok << "\n";
}

bool abc146_c_2_func(ll &trynum, ll &a, ll &b, ll &x) {
    string s = to_string(trynum);
    ll val = a * trynum + b * (ll)s.size();
    if(val <= x) return true;
    return false;
}

void abc146_c_2(){
    // abc146_c
    ll a, b, x, mid;
    cin >> a >> b >> x;


    // [ok, ng) for max value いける最大の値を求めたいとき
    // (ng, ok] for min value 可能となる最小の値を出したいとき
    // CATION: ok is result  (NOT mid)
    ll ok = 0;
    ll ng = 1e9 + 1;
    while(abs(ok - ng) > 1){
        mid = (ok + ng) / 2;
        if(abc146_c_2_func(mid, a, b, x)) ok = mid;
        else ng = mid;
    }
    cout << ok << "\n";
}


void abc207_b(){
    ll a, b, c, d;
    ll mid;
    cin >> a >>b>>c>>d;
    auto func = [&](ll tryval){
        if(a+(b*tryval) <= (c*tryval)*d) return true;
        return false;
    };

    // [ok, ng) for max value いける最大の値を求めたいとき
    // (ng, ok] for min value 可能となる最小の値を出したいとき
    ll ng = 0;
    ll ok = 1e6;
    while(abs(ok - ng) > 1){
        mid = (ok + ng) / 2;
        if(func(mid)) ok = mid;
        else ng = mid;
    }
    if(ok == 1e6) cout << -1 << "\n";
    else cout << ok << "\n";

}

using namespace std;
int main() {
    //abc146_c();
    abc146_c_2();
    //abc207_b();
}
