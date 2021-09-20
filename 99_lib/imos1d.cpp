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

// chmax/min: if update a then true
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define ceil(a,b) (((a) + ((b) - 1)) / (b))

template<typename T> class zatsuClass{
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

    void makeTable(unordered_set<T>& dat){
        vector<T> tmp;
        // create zatsu source list
        for(T x: dat) tmp.emplace_back(x);
        sort(tmp.begin(), tmp.end());

        // Create zatsu Table
        REP(i, tmp.size()) this->zatsuTable[tmp.at(i)] = i;
        REP(i, tmp.size()) this->zatsuTableReverse[i] = tmp.at(i);
    }

    vector<T> restore(vector<T>& dat){
        vector<T> res;
        for(T x: dat) res.template emplace_back(this->zatsuTableReverse[x]);
        return res;
    }

};


//////////////////////////////////////////////////////////////////////////////

/*
 */
template<typename T>
class imos1d{
public:
    int nodeNum;
    vector<T> res;

    imos1d(int nodeNum){
        this->nodeNum = nodeNum;
        this->res = vector<T>(nodeNum);
    }

    void add(int ind, T val){
        this->res.at(ind) += val;
    }

    void solve(){
        for(int i = 1; i < (int)this->res.size(); ++i) this->res.at(i) += this->res.at(i-1);
    }
};




// https://atcoder.jp/contests/abc014/tasks/abc014_3
void abc014_3(){
    int n; cin >> n;
    int a, b;
    imos1d<int> imos(1e6 + 10);
    REP(i, n){
        cin >> a >> b;
        imos.add(a, 1);
        imos.add(b + 1, -1);
    }
    imos.solve();
    auto res = max_element(ALL(imos.res));
    cout << *res << "\n";
}

// snuke prime
// https://atcoder.jp/contests/abc188/tasks/abc188_d
void abc188_d(){
    int n; ll snuke; cin >> n >> snuke;
    ll a, b, c;
    unordered_set<ll> dat;
    vector<pair<ll, ll>> eventList;
    zatsuClass<ll> zatsu;
    REP(i, n) {
        cin >> a >> b >> c;
        ++b;
        dat.emplace(a);
        dat.emplace(b);
        eventList.emplace_back(a, c);
        eventList.emplace_back(b, -c);
    }
    zatsu.makeTable(dat);
    imos1d<ll> imos(zatsu.zatsuTable.size());
    for(auto x: eventList) imos.add(zatsu.zatsuTable[x.first], x.second);
    imos.solve();

    ll res = 0;
    ll prevDay = 0;
    ll prevCost = 0;
    REP(i, zatsu.zatsuTable.size()){
        ll today = zatsu.zatsuTableReverse[i];
        res += (today - prevDay) * min(prevCost, snuke);
        prevDay = today;
        prevCost = imos.res.at(i);
    }
    cout << res << "\n";

}


using namespace std;
int main() {
    FASTIOpre();
    //abc014_3();
    abc188_d(); // snuke prime
}
