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
 * LISを求める. Decrementがほしければ-して計算すればいい
 * {1,2,2,2,3}
 * cansame = true -> 1,2,2,2,3
 * cansame = false-> 1,2,3
 *
 * longestlen: LIS長
 * longestlastindex: LIS長を更新した最後のindex
 *
 * loadOnlyLength(l, cansame): LIS長だけを求めます。resの中は復元したものとは限りませんO(NlogN)
 * loadWithResult(l, cansame): LIS長だけを求めます。resの中はあり得るLISの辞書順で最小のものです。O(NlogN)ですが定数倍が倍です。
 * loadWithResultLastest(l, cansame): LIS長だけを求めます。resの中はあり得るLISの辞書順で最大のものです。O(NlogN)
 *
 * 復元: resを読み込んでください
 * for(auto x: lis.res) cout << x << " ";
 * ★★★★★★★★★★★★★★★★★★★★★★★★嘘。最小ではないし壊れている
 */
template<typename T>
struct LIS{
    vector<T> res;
    int longestlen;
    int longestlastindex;
    int INF = 1e9;

    void loadOnlyLength(const vector<T> & l, const bool cansame) {
        loadSubRoutine(l, cansame, l.size());
    }
    void loadWithResult(const vector<T> & l, const bool cansame) {
        loadSubRoutine(l, cansame, l.size());
        loadSubRoutine(l, cansame, longestlastindex);
    }
    void loadWithResultLastest(const vector<T> & l, const bool cansame) {
        vector<T> newl = l;
        for(int i = 0; i < (int)l.size(); ++i) newl[i] = -newl[i];
        reverse(newl.begin(), newl.end());
        loadSubRoutine(newl, cansame, newl.size());
        loadSubRoutine(newl, cansame, longestlastindex);
        for(int i = 0; i < longestlen; ++i) res[i] = -res[i];
        reverse(res.begin(), res.end());
    }
    void loadSubRoutine(const vector<T> & l, const bool cansame, const int stopindex){
        this->longestlen = -1;
        this->res = vector<T>(l.size(), this->INF);
        auto itr = lower_bound(this->res.begin(), this->res.end(), this->INF);
        for(int i = 0; i < (int)l.size(); ++i){
            T x = l.at(i);
            if(!cansame) itr = lower_bound(this->res.begin(), this->res.end(), x);
            else itr = upper_bound(begin(this->res), end(this->res), x);
            int ind = distance(begin(this->res), itr);
            if( (ind + 1) >= longestlen) longestlastindex = i;
            this->longestlen = max(this->longestlen, ind + 1);
            this->res[ind] = x;
            if(i == stopindex) break;
        }
        this->res.resize(this->longestlen);
    }
};

// これこそ本当にLISの最小と最大
template<typename T>
struct LISminmax {
    vector<T> res; /* 最後に更新したvalue */
    vector<vector<T>> value; /* 各桁に積まれた値 */
    vector<vector<int>> index; /* 各桁に積まれた値の位置 */
    int longestlen;
    int longestlastindex;
    int INF = 1e9;

    void loadOnlyLength(const vector<T> & l, const bool cansame) {
        loadSubRoutine(l, cansame, l.size());
    }
    void loadWithResult(const vector<T> & l, const bool cansame) {
        loadSubRoutine(l, cansame, l.size());
        loadSubRoutine(l, cansame, longestlastindex);
    }
    void loadWithResultLastest(const vector<T> & l, const bool cansame) {
        vector<T> newl = l;
        for(int i = 0; i < (int)l.size(); ++i) newl[i] = -newl[i];
        reverse(newl.begin(), newl.end());
        loadSubRoutine(newl, cansame, newl.size());
        loadSubRoutine(newl, cansame, longestlastindex);
        for(int i = 0; i < longestlen; ++i) res[i] = -res[i];
        reverse(res.begin(), res.end());
    }
    void loadSubRoutine(const vector<T> & l, const bool cansame, const int stopindex){
        this->longestlen = -1;
        this->res = vector<T>(l.size(), this->INF);
        value = vector<vector<T>>(l.size(), vector<T>());
        index = vector<vector<int>>(l.size(), vector<int>());
        auto itr = lower_bound(this->res.begin(), this->res.end(), this->INF);
        for(int i = 0; i < (int)l.size(); ++i){
            T x = l.at(i);
            if(!cansame) itr = lower_bound(this->res.begin(), this->res.end(), x);
            else itr = upper_bound(begin(this->res), end(this->res), x);
            int ind = distance(begin(this->res), itr);
            if( (ind + 1) >= longestlen) longestlastindex = i;
            this->longestlen = max(this->longestlen, ind + 1);
            /* ここまでは完全にLISでよい */
            this->res[ind] = x;
            value.at(ind).template emplace_back(x);
            index.at(ind).template emplace_back(i);
            if(i == stopindex) break;
        }
        /* ここで復元パートをする */
        this->res.resize(this->longestlen); // LISの結果の長さは変わらない
        auto lastIndex = longestlastindex; // まず、最後の桁のindexを記憶する
        for(int i = longestlen - 2; i >= 0; --i){ // 後ろから見ていき
            auto itrind = lower_bound(index.at(i).begin(), index.at(i).end(), lastIndex); // より後ろの桁より手前の最後のindex
            int ind = distance(index.at(i).begin(), itrind);
            --ind; // lower boundなので、--した値がほしい
            lastIndex = index.at(i).at(ind);
            res.at(i) = value.at(i).at(ind);
        }
    }

};



auto vectorLeftIsSmall = [](const vector <int> &l, const vector<int> &r){
    assert(l.size() == r.size());
    REP(i, l.size()){
        if(l.at(i) > r.at(i)) return false;
    }
    return true;
};
auto vectorLeftIsLarge = [](const vector <int> &l, const vector<int> & r){
    assert(l.size() == r.size());
    REP(i, l.size()){
        if(l.at(i) < r.at(i)) return false;
    }
    return true;
};
auto isLIS(const vector<int> &l){
    REP(i, l.size() - 1){
        if(l.at(i) >= l.at(i+1) ) return false;
    }
    return true;
}
// toooooooooo heavy!
struct LISchecker {
    vector<int> resfirst;
    vector<int> reslast;
    vector<int> can;
    int lislen;
    void load(const vector<int> dat){
        reslast = {};
        resfirst = {};
        lislen = -1;

        assert(dat.size() < 25);
        FOR(pat, 1, pow(2, dat.size()) ){
            can.clear();
            REP(ind, dat.size()) if ( ((pat >> ind)  & 1) == 1 ) can.emplace_back(dat.at(ind));
            // IS?
            if(!isLIS(can)) continue;
            if((int)can.size() < lislen) continue;
            if((int)can.size() > lislen){
                resfirst = can;
                reslast = can;
                lislen = can.size();
                continue;
            }
            // 一緒の場合
            if(vectorLeftIsSmall(can, resfirst)) {
                resfirst = can;
            }
            if(vectorLeftIsLarge(can, reslast)) {
                reslast = can;
            }

        }


    };
};

using VI = vector<int>;
int inf = 1<<30;

// sortedな列から検索。0-indexed
// xの書き込み先を返す
ll index_of(VI& A, ll x){
    return distance(A.begin(), lower_bound(A.begin(), A.end(), x));
}
// 復元可能
// http://www.prefield.com/algorithm/dp/lis_fast.html
VI lislis(VI& a) {
    const int n = a.size();
    VI A(n, inf);
    VI id(n); // Aのどこに挿入したかの情報
    REP(i, n){
        id[i] = index_of(A, a[i]);
        A[ id[i] ] = a[i];
    }
    int m = *max_element(id.begin(), id.end());
    VI b(m+1);
    // 後ろから
    for (int i = n-1; i >= 0; --i)
        if (id[i] == m){
            b[m] = a[i];
            m--;
        }
    return b;
}

void test3() {
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    vector<int> l;
    LISchecker lisc;
    LISminmax<int> lis;
    REP(loop, 10000){
        l.clear();
        REP(i, 16) l.emplace_back(engine() % 20);
        auto lisl = lislis(l);
        //lisc.load(l);
        //cout << "\n";
        //cout << "\n";
        //cout << "\n";
        //for(auto x: l) cout << x << " ";
        //cout << "\nfofo---\n";
        //for(auto x: lisc.resfirst) cout << x << " ";
        //cout << "\n";
        //for(auto x: lisc.reslast) cout << x << " ";
        //cout << "\n";
        lis.loadWithResult(l, false);
        //for(auto x: lis.res) cout << x << " ";
        if(lisl != lis.res) cout <<"ng";
        //cout << "\n";
        //lis.loadWithResultLastest(l, false);
        //for(auto x: lis.res) cout << x << " ";
        //if(lisc.reslast != lis.res) cout <<"ng";
        //cout << "\n";
        cout << flush;
    }

}

void test2() {
    vector<int> l = {4,7,5,1,5,8,2,6,9,5,10,4,7,3,4};
    //vector<int> l = {1,2,6,9,5,10};
    LISchecker lisc;
    lisc.load(l);

    cout << lisc.lislen;
    cout << "\n";
    for(auto x: lisc.resfirst) cout << x << " ";
    cout << "\n";
    for(auto x: lisc.reslast) cout << x << " ";
    cout << "\n";

    LISminmax<int> lis;
    // len: 4
    // 4 5 6 7
    lis.loadWithResult(l, false);
    for(auto x: lis.res) cout << x << " ";
    cout << "\n";
    // 10

    // len: 5
    // 4 5 6 7
    lis.loadWithResultLastest(l, false);
    for(auto x: lis.res) cout << x << " ";
    cout << "\n";
    // 10


}

void test(){
    vector<int> l = {4,7,5,1,5,8,2,6,9,5,10,4,7,3,4};
    LIS<int> lis;
    // len: 4
    // 4 5 6 7
    lis.loadWithResult(l, false);
    cout << "len: " << lis.longestlen << "\n";
    for(auto x: lis.res) cout << x << " ";
    cout << "\n";
    // 10
    cout << "lastind" << lis.longestlastindex << "\n";

    // len: 5
    // 4 5 6 7
    lis.loadWithResultLastest(l, false);
    cout << "len: " << lis.longestlen << "\n";
    for(auto x: lis.res) cout << x << " ";
    cout << "\n";
    // 10
    cout << "lastind" << lis.longestlastindex << "\n";

    // len: 9
    // 4 4 5 5 5 5 5 7
    lis.loadWithResult(l, true);
    cout << "len: " << lis.longestlen << "\n";
    for(auto x: lis.res) cout << x << " ";
    cout << "\n";
    cout << "lastind" << lis.longestlastindex << "\n";

    l = {7,8,9,1,2,3};
    // len: 5
    //1 2 3 4 6
    lis.loadWithResultLastest(l, false);
    cout << "len: " << lis.longestlen << "\n";
    for(auto x: lis.res) cout << x << " ";
    cout << "\n";
    cout << "lastind" << lis.longestlastindex << "\n";

}

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D
void DPL_1_D(){
    int n; cin >> n;
    vector<ll> dat(n);
    REP(i, n) cin >> dat.at(i);

    LIS<ll> lis;
    lis.loadOnlyLength(dat, false);
    cout << lis.longestlen << "\n";
}

void mojaLISMin(){
    int n; cin >> n;
    vector<ll> dat(n);
    REP(i, n) cin >> dat.at(i);
    LISminmax<ll> st;
    st.loadWithResult(dat, false);
    REP(i, st.res.size() - 1) cout << st.res.at(i) << " ";
    cout << st.res.at(st.res.size() - 1)<< "\n";
}

using namespace std;
int main() {
    FASTIOpre();
    //test();
    //DPL_1_D();
    //test2();
    //test3();
    mojaLISMin();
}
