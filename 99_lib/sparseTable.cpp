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

        for(int i = 0; i < (int)v.size(); i++) {
            table[0][i] = v[i];
        }
        for(int i = 1; i < log_len; i++) {
            for(int j = 0; j + (1 << i) <= (1 << log_len); j++) {
                table[i][j] = operation(table[i-1][j], table[i - 1][j + (1 << (i - 1))]);
            }
        }
        for(int i = 2; i < (int)lookup.size(); i++) {
            lookup[i] = lookup[i >> 1] + 1;
        }
    }

    inline T query(int l, int r) {
        int b = lookup[r - l];
        return operation(table[b][l], table[b][r - (1 << b)]);
    }
};

// https://qiita.com/drken/items/1b7e6e459c24a83bb7fd
template <class Abel> struct BIT {
    vector<Abel> dat;
    Abel UNITY_SUM = 0;                     // to be set

    /* [1, n] */
    BIT(int n) { init(n); }
    void init(int n) {
        dat.resize(n + 1);
        for (int i = 0; i < (int)dat.size(); ++i) dat[i] = UNITY_SUM;
    }

    /* a is 1-indexed */
    inline void add(int a, Abel x) {
        for (int i = a; i < (int)dat.size(); i += i & -i)
            dat[i] = dat[i] + x;
    }

    /* [1, a], a is 1-indexed */
    inline Abel sum(int a) {
        Abel res = UNITY_SUM;
        for (int i = a; i > 0; i -= i & -i)
            res = res + dat[i];
        return res;
    }

    /* [a, b), a and b are 1-indexed */
    inline Abel sum(int a, int b) {
        return sum(b - 1) - sum(a - 1);
    }

    /* k-th number (k is 0-indexed) */
    int get(int k) {
        ++k;
        int res = 0;
        int N = 1; while (N < (int)dat.size()) N *= 2;
        for (int i = N / 2; i > 0; i /= 2) {
            if (res + i < (int)dat.size() && dat[res + i] < k) {
                k = k - dat[res + i];
                res = res + i;
            }
        }
        return res + 1;
    }
};

int main(){
    return 0;
}