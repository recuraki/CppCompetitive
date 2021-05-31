#include <bits/stdc++.h>
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define REP(i, n) FOR(i,0,n)
using namespace std;
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
    vector<ll> l = {1, 5, 10, 100, 200};
    cout << mindiffsearch(l, -10LL) << "\n"; // 11
    cout << mindiffsearch(l, 3LL) << "\n";   // 2
    cout << mindiffsearch(l, 40LL) << "\n";  // 30
}

