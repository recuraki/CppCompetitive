#include <bits/stdc++.h>
using namespace std;
using lint = long long int;
using pint = pair<int, int>;
using plint = pair<lint, lint>;
struct fast_ios { fast_ios(){ cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20); }; } fast_ios_;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)


template<class T> inline void amin(T &x, const T &y) { if (y<x) x=y; }


lint data[300100];
lint datb[300100];
void solve(){
    int n;
    lint x, y;
    cin >> n;
    REP(i, n){
        cin >> x >> y;
        data[i] = x;
        datb[i] = y;
    }
    data[n] = data[0];
    datb[n] = datb[0];
    int k;
    lint mi = 1LL << 60;
    REP(i, n){
        datb[i] = min(datb[i], data[k]);
        aint(mi, )
    }
    lint res = 0;
    res += accumulate(data[0], data[n-1], 0);
    res -= accumulate(datb[0], datb[n-1], 0);
    cout << res <<endl;
}

int main(){
    int q;
    cin >> q;
    REP(i, q) {solve();}

}

