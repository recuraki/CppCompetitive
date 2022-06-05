#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using pint = pair<int, int>;
using plint = pair<ll, ll>;
struct fast_ios { fast_ios(){ cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20); }; } fast_ios_;

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

// https://github.com/mendako1015/Library/blob/master/DataStructure/SparseTable.cpp


/*
USAGE:
 auto op = [] (int a, int b) {return min(a,b);};
 SparseTable<int> st(dat, op);
 区間: [a, b)を計算します
 結合法則, 冪等性を要求します
 */
template<typename T>
class SparseTable {
    vector<vector<T>> table;
    vector<int> lookup;
    function<T(T, T)> operation;
public:
    SparseTable(const vector<T> &v, function<T(T, T)> ope): operation(ope) {
        int log_len = 0;
        while((1 << log_len) <= (int)v.size()) ++log_len;
        table = vector<vector<T>>(log_len, vector<int>(1 << log_len));
        lookup = vector<int>((int)v.size() + 1);
        for(int i = 0; i < (int)v.size(); i++) table[0][i] = v[i];
        for(int i = 1; i < log_len; i++) {
            for(int j = 0; j + (1 << i) <= (1 << log_len); j++) {
                table[i][j] = operation(table[i-1][j], table[i - 1][j + (1 << (i - 1))]);
            }
        }
        for(int i = 2; i < (int)lookup.size(); i++) lookup[i] = lookup[i >> 1] + 1;
    }

    inline T query(const int l, const int r) {
        int b = lookup[r - l];
        return operation(table[b][l], table[b][r - (1 << b)]);
    }
};


int main(){
    auto op = [] (int a, int b) {return min(a,b);};
    vector<int> dat = {5, 4, 3, 2, 1};
    SparseTable<int> st(dat, op);
    cout << st.query(0, 3); // -> 3


    return 0;
}