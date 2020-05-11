#include <bits/stdc++.h>
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)


//////////////////////////////////////
#include <iostream>
using namespace std;
#define dp(arg) do { cout << #arg << ":"; dprint(arg); } while(0)

template <typename T> void dprint(T arg) { cout << arg << "\n"; }
template <typename T> void dprint(const vector<T>& arg) { for_each(begin(arg), end(arg), [](T value){ cout << value << " "; }   ); cout << "\n";  }
template <typename T> void dprint(const vector<vector<T>>& arg) { for_each(begin(arg), end(arg), [=](vector<T> arg2){ dprint(arg2); cout << "\n";} );  }

// #define dprint(arg) ;
//////////////////////////////////////

using namespace std;
int main() {
    int c = 1;
    dp(c);
    std::vector<int> v = {1,2,3,4,5} ;
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


}
