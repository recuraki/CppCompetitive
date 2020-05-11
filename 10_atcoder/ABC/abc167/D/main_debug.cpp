/* ref: https://bondo.hateblo.jp/entry/2020/05/11/150305 のコードを元にcoutを入れました*/
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

int main(){
    long long N, K;
    cin >> N >> K;
    cout << N << "," << K << "\n";

    vector<int> A(N);
    REP(i,N){
        cin >> A[i];
        --A[i];
    }
    vector<vector<long long>> to(62, vector<long long>(N));
    REP(i,N) to[0][i] = A[i];

    cout << "init to: ";
    REP(i, N) cout << to[0][i] << " ";
    cout << "\n";

    REP(i,60) REP(j,N) to[i+1][j] = to[i][to[i][j]];

    cout << "init second: \n";
    REP(i, 60) {
        cout << "i[" << i << "]: ";
        REP(j, N) {
            cout << to[i][j] << " ";
        }
        cout << "\n";
    }


    cout << "k=" << bitset<60>(K) << "\n";
    cout << "final: \n";
    int cur = 0;
    REP(j,60){
        cout << "j[" << j << "]: K " << K << " j " << j << "K>>j " <<  ((K>>j)&1) << "\n";

        if((K >> j) & 1){
            cout << " > hit! > after: " << cur << " -> after" << to[j][cur] << "\n";
            cur = to[j][cur];
        }
    }

    cout << cur + 1 << endl;
}