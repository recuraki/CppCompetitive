#include <bits/stdc++.h>
#include <unordered_map>
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
using namespace std;

int dat[10000];
using namespace std;
int sum;
int main() {
    int q;
    unordered_map<int, char> used;

    cin >> q;
    REP(qq, q){
        used.clear();

        sum = 0;
        int n;
        cin >> n;
        REP(j, n){
            cin >> dat[j];
        }

        REP(i, n){
            sum = dat[i];
            FOR(j, i+1, n){
                sum += dat[j];
                used[sum] = 0x00;
            }
        }
        int res = 0;
        REP(i, n){
            if ( used.find(dat[i]) != used.end() ) {
                res += 1;
            }
        }
        cout << res << "\n";
    }
}
