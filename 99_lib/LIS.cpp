#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)
#define FASTIOpre() cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);

template< typename T >
size_t longest_increasing_subsequence(const vector< T > &a, bool strict) {
    vector< T > lis;
    for(auto &p : a) {
        typename vector< T >::iterator it;
        if(strict) it = lower_bound(begin(lis), end(lis), p);
        else it = upper_bound(begin(lis), end(lis), p);
        if(end(lis) == it) lis.emplace_back(p);
        else *it = p;
    }
    return lis.size();
}

/*
 * {1,2,2,2,3}
 * cansame = true -> 1,2,2,2,3
 * cansame = false-> 1,2,3
 */
template<typename T>
struct LIS{
    vector<T> res;
    int longestlen;
    int INF = 1e9;

    void load(const vector<T> & l, const bool cansame = false){
        this->longestlen = -1;
        this->res = vector<T>(l.size(), this->INF);
        auto itr = lower_bound(this->res.begin(), this->res.end(), this->INF);
        for(T x: l){
            if(!cansame) itr = lower_bound(this->res.begin(), this->res.end(), x);
            else itr = upper_bound(begin(this->res), end(this->res), x);
            int ind = distance(begin(this->res), itr);
            this->longestlen = max(this->longestlen, ind + 1);
            this->res[ind] = x;
        }
        this->res.resize(this->longestlen);
    }
};


void test(){
    vector<int> l = {1,5,2,2,2,3,2,2,2,4,6};
    LIS<int> lis;
    // len: 5
    //1 2 3 4 6
    lis.load(l, false);
    cout << "len: " << lis.longestlen << "\n";
    for(auto x: lis.res) cout << x << " ";
    cout << "\n";

    // len: 9
    //1 2 2 2 2 2 2 4 6
    lis.load(l, true);
    cout << "len: " << lis.longestlen << "\n";
    for(auto x: lis.res) cout << x << " ";
    cout << "\n";
}

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D
void DPL_1_D(){
    int n; cin >> n;
    vector<ll> dat(n);
    REP(i, n) cin >> dat.at(i);

    LIS<ll> lis;
    lis.load(dat, false);
    cout << lis.longestlen << "\n";
}

using namespace std;
int main() {
    FASTIOpre();
    //test();
    DPL_1_D();
    int i=1;
    auto j = i;

}
