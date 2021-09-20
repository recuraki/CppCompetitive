#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

struct fast_ios { fast_ios(){ cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20); }; } fast_ios_;


#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)

// chmax/min: if update a then true
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define ceil(a,b) ((a) + ((b) - 1)) / (b)


#ifndef KANAILOCAL
#define KANAILOCAL 1
#endif


bool ABC219C(const std::string& l, const std::string& r) {

    unordered_map<char, int> d;
    auto ll = min(l.length(), r.length());
    char x, y;
    REP(i, ll){
        x = d[l[i]];
        y = d[r[i]];
        if(x == y) continue;
        if(x < y) return true;
        if(x > y) return false;
    }
    if(l.length() < r.length()) return true;
    if(l.length() > r.length()) return false;
    assert(1==0);
}

using namespace std;
int main() {

    // 例: 山がある。これの２番目に大きなindexを求めたい
    vector<int> mount = {10, 3, 15, 30, 100};
    vector<pair<int, int>> dat;
    REP(i, mount.size()) dat.emplace_back(mount.at(i), i);
    sort(ALL(dat), greater<pair<int,int>>());
    cout << "2nd mountain = index:" << dat.at(1).second << " height=" << dat.at(1).first << "\n";


    // テクニック
    vector<tuple<int,int,int>> v2;
    v2.emplace_back(make_tuple(1,20,20));
    v2.emplace_back(make_tuple(2,30,100));
    v2.emplace_back(make_tuple(3,20,30));
    sort(ALL(v2));
    sort(ALL(v2), greater<tuple<int,int,int>>());
    sort(ALL(v2), [](auto const& l, auto const &r){
        if(get<1>(l) < get<1>(r)) { return true; }
        if(get<1>(l) > get<1>(r)) { return false; }
        if(get<2>(l) < get<2>(r)) { return true; }
        // if(get<2>(l) > get<2>(r))
        return false;
    });
    for (auto x: v2){
        cout << get<0>(x) << " " << get<1>(x) << " "<< get<2>(x) << " ";
        cout << endl;
    }

}
