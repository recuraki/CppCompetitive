#include <bits/stdc++.h>
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)


//////////////////////////////////////
using namespace std;
#define dp(arg) do { cout << #arg << ":"; dprint(arg); } while(0)

template <typename T> void dprint(T arg) { cout << arg << "\n"; }
template <typename T> void dprint(const vector<T>& arg) { for_each(begin(arg), end(arg), [](T value){ cout << value << " "; }   ); cout << "\n";  }
template <typename T> void dprint(const vector<vector<T>>& arg) { for_each(begin(arg), end(arg), [=](vector<T> arg2){ dprint(arg2); cout << "\n";} );  }

// #define dprint(arg) ;
//////////////////////////////////////

using namespace std;
int main() {
    queue<pair<string, int>> jobs;
    int n, q;
    cin >> n >> q;
    string name;
    int t;
    REP(qq, n){
        cin >> name >> t;
        jobs.push(make_pair(name, t));
    }
    int keika = 0;
    pair<string , int> item;
    while(!jobs.empty()){
        item = jobs.front(); jobs.pop();
        name = item.first; t = item.second;
        if (t <= q) {
            keika += t;
            cout << name << " " << keika << "\n";
        } else {
            t -= q;
            keika += q;
            jobs.push(make_pair(name, t));
        }
    }
}
