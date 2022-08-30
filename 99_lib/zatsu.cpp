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

/*
 * 座標圧縮を行う。
 * zatsu<T>の宣言に対して、load(vector<T>)を呼ぶと、
 * return: vector<T> 座標圧縮された後のvector<T>
 */
template<typename T> class zatsuClass{
public:
    unordered_set<T> zatsu;
    unordered_map<T, int> zatsuTable;
    unordered_map<int, T> zatsuTableReverse;
    vector<T> zatsuList;

    vector<T> load(const vector<T>& dat){

        vector<T> res;
        // create all value uniq set
        REP(i, dat.size()) this->zatsu.template emplace(dat[i]);

        // create zatsu source list
        for(T x: zatsu) zatsuList.emplace_back(x);
        sort(zatsuList.begin(), zatsuList.end());

        // Create zatsu Table
        REP(i, zatsuList.size()) this->zatsuTable[zatsuList.at(i)] = i;
        REP(i, zatsuList.size()) this->zatsuTableReverse[i] = zatsuList.at(i);
        REP(i, dat.size()) res.emplace_back(zatsuTable[dat.at(i)]);

        return res;
    }

    vector<T> restore(const vector<T>& dat){
        vector<T> res;
        for(T x: dat) res.template emplace_back(this->zatsuTableReverse[x]);
        return res;
    }

    int lower_bound(T val){
        return distance(zatsuList.begin(), std::lower_bound(zatsuList.begin(), zatsuList.end(), val));
    }
    int upper_bound(T val){
        return distance(zatsuList.begin(), std::upper_bound(zatsuList.begin(), zatsuList.end(), val));
    }

};


using namespace std;
int main() {
    FASTIOpre();
    vector<int> a = {3,1,25,16,34,2};
    zatsuClass<int> zatsu;

    auto res = zatsu.load(a);

    // 3 1 25 16 34 2
    cout << "init" << "\n";
    REP(i, a.size()) cout << a.at(i) << " ";
    cout << "\n";

    // 2 0 4 3 5 1
    cout << "zatsu" << "\n";
    REP(i, res.size()) cout << res.at(i) << " ";
    cout << "\n";

    // 34 = 5, 25 = 4, 16 = 3, 3 = 2, 2 = 1, 1 = 0,
    cout << "zatsuTable" << "\n";
    for(auto x: zatsu.zatsuTable) cout << x.first << " = " << x.second << ", ";
    cout << "\n";

    // 5 = 34, 4 = 25, 3 = 16, 2 = 3, 1 = 2, 0 = 1,
    cout << "zatsuTableReverse" << "\n";
    for(auto x: zatsu.zatsuTableReverse) cout << x.first << " = " << x.second << ", ";
    cout << "\n";

    // 3 1 25 16 34 2
    auto resReverse = zatsu.restore(res);
    cout << "zatsu(restore)" << "\n";
    REP(i, resReverse.size()) cout << resReverse.at(i) << " ";
    cout << "\n";

    cout << "lower_bound(5)" << "\n";
    cout << zatsu.lower_bound(5) << "\n";
    cout << "upper_bound(5)" << "\n";
    cout << zatsu.upper_bound(5) << "\n";
    cout << "lower_bound(16)" << "\n";
    cout << zatsu.lower_bound(16) << "\n";
    cout << "upper_bound(16)" << "\n";
    cout << zatsu.upper_bound(16) << "\n";

}
