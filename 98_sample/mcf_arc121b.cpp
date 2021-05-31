#include <bits/stdc++.h>
#include <atcoder/all>
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define REP(i, n) FOR(i,0,n)
using namespace std;
using namespace atcoder;
const int numNode = 2*100000;
const int numColor = 4 * 100000;
const int numGraph = numNode + numColor + 100;
const int snode = numGraph - 3;
const int tnode = numGraph - 2;
using ll = long long;

// lからxに一番近い数字を探し距離(絶対値)を返す
// l, xはTを要求する
template <typename T>
T mindiffsearch(vector<T> &l, T x){
    auto sz = l.size();
    auto p = lower_bound(l.begin(), l.end(), x);
    auto indl = distance(l.begin(), p);
    if(indl == 0) return abs(x - l.at(0));
    if(indl == sz) return abs(x - l.at(sz-1));
    return min(abs(x - l.at(indl)), abs(x - l.at(indl - 1)));
}

int main(int argc, char *argv[]) {
    int n; cin >> n;
    vector<int> cnt(3);
    vector<vector<ll>> dat(3);
    REP(i, n*2){
        ll a; string b;
        cin >> a >> b;
        if(b.at(0) == 'R') {dat.at(0).emplace_back(a);      cnt.at(0)++; }
        else if(b.at(0) == 'G') {dat.at(1).emplace_back(a); cnt.at(1)++; }
        else if(b.at(0) == 'B') {dat.at(2).emplace_back(a); cnt.at(2)++; }
        else { assert(false); }
    }
    if( (cnt.at(0)%2 + cnt.at(1)%2 + cnt.at(2)%2) == 0){
        cout << 0 << "\n";
    }

    if(cnt.at(0)%2 == 0) {}
    else if(cnt.at(1)%2 == 0) {swap(cnt.at(0), cnt.at(1)); swap(dat.at(0), dat.at(1)); }
    else if(cnt.at(2)%2 == 0) {swap(cnt.at(0), cnt.at(2)); swap(dat.at(0), dat.at(2)); }
    else { assert(false); }
    // dat[0] = even

    ll res1 = 1e18;
    for(auto x: dat.at(1)) res1 = min(res1, mindiffsearch(dat.at(2), x));
    cout << res1 << "\n";


}

