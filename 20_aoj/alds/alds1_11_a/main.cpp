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

    int n;
    cin >> n;

    int adj[n][n];
    memset(adj, 0, sizeof(int) * n * n);

    int v, k;
    int a;
    REP(i, n) {
        cin >> v >> k;
        REP(j, k){
            cin >> a;
            adj[v-1][a-1] = 1;
        }
    }

    REP(i, n) {
        REP(j, n - 1) {
            cout << adj[i][j] << " ";
        }
        cout << adj[i][n-1] << "\n";
    }

}
