#include <bits/stdc++.h>
using namespace std;
using ll = long long int;


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
//#define dprint(arg) ;
//////////////////////////////////////

using namespace std;
int main() {

    // 改行まで読み込む
    /*
    std::string s;
    while (     std::getline( std::cin, s ) )
    {
        // do anything
    }
     */

    int c = 1;
    dp(c);
    std::vector<int> v = {5,2,3,1,4} ;
    dp(v);
    // 昇順
    sort(ALL(v), [](auto const &l, auto  const &r){
        if(l < r){
            return true;
        } else { return false; }
    });
    dp(v);


    int cnt = 1;
    vector<vector<int>> dat;
    REP(i, 5){
        vector<int> item;
        REP(j, 5){
            item.push_back(cnt);
            cnt += 1;
        }
        dat.push_back(item);
    }
    dp(dat);

    map<int, string> m;
    m[100] = "hoge";
    m[200] = "moge";
    cout << m[100] << "\n";

    int ai=2, bi=5;
    chmax(ai, bi);
    dp(ai);

    pair<int, int> p1, p2, p3;
    p1 = make_pair(10, 20);
    p2 = make_pair(30, 40);
    p3 = p1 + p2;
    dp(p3.first);
    dp(p3.second);

    // mapのk, v取り出し
    unordered_map<int, string > m2;
    m2 = { {1, "a"}, {2, "b"}};
    for (auto [k, v]: m2) cout << k << ": " << v << endl;

    unordered_map<int, tuple<int,int,int>> m3;
    m3[100] = make_tuple(1,2,3);
    m3[200] = make_tuple(3,2,1);
    m3[300] = make_tuple(3,2,1);
    for (auto [k, v]: m3) cout << k << ":" << get<2>(v) <<endl;

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

    cout << "stdout" << endl;
    cerr << "stderr" << endl;

    vector vi1 {1,2,3,4,5};
    for_each(ALL(vi1),
             [](auto x) { cout << x*x << " "; });

    vector vi2 {2,4,6,8};
    vector vi3 {1,2,3,4};
    auto isodd = [](auto x) { if(x&1){return true;} else { return false; } };
    auto iseven = [&](auto x) { return(!isodd(x)); };
    dp(all_of(ALL(vi2), iseven));
    dp(all_of(ALL(vi3), iseven));
    dp(any_of(ALL(vi2), isodd));
    dp(any_of(ALL(vi3), isodd));

    // find is find iter(not index)
    dp(*find(ALL(vi2), 8));
    //dp(find(ALL(vi3), 8));

    std::vector<int> vi4 = {1,2,1,1,3,3} ;
    dp(count(ALL(vi4), 1));


    vector vi5 {0,0,1,0};
    vector vi6 {2,4,3,6};
    vector vi7 {2,4,3,6};
    dp(equal(ALL(vi6), ALL(vi7)));
    dp(equal(ALL(vi6), ALL(vi5)));
    dp(equal(ALL(vi6), ALL(vi5), [](auto a, auto b){return a%2 == b%2;}));

    std::vector<int> v11 = {1,2,3,4,5,6,7,8,9} ;
    std::vector<int> v12 = {4,5,6} ;
    std::vector<int> v13 = {1,3,5} ;
    // search can return:  bool res = search()
    dp(*search(ALL(v11), ALL(v12)));
    dp(*search(ALL(v11), ALL(v13)));

    // transform: map & copy
    vector<int> v21 = {1,2,3,4,5};
    vector<int> v22(v21.size());
    transform(ALL(v21), v22.begin(),
              [](auto x) {return pow(x,2); });
    dp(v22);

    vector<int> v23 = {1,2,2,2,3};
    dp(v23);
    replace(ALL(v23), 2, 0);
    dp(v23);

    vector<int> v24 = {1,2,2,2,3,4,2,2,2,2,5,2,6};
    auto v24newlast = remove(ALL(v24), 2);
    dp("v24");
    for(auto v24p = v24.begin(); v24p != v24newlast; v24p++){
        cout << *v24p << " ";
    }
    cout << endl;
    v24.resize(distance(v24.begin(), v24newlast));
    dp(v24);

}
