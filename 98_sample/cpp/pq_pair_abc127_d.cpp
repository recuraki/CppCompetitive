

#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)



int main() {
    FASTIO();
    int n,m; cin >> n >> m;
    map<int, int> cards;
    int x;
    for(int i = 0; i < n; ++i) {
        cin >> x; ++cards[x];
    }
    priority_queue<pair<long long , long long >, vector<pair<long long , long long>>, greater<pair<long long, long long>>> pq;
    for(auto [val, cnt]: cards)
    {
        pq.push(make_pair(val, cnt));
    }

    vector<pair<long long, long long>> candidate;
    for(int i = 0; i < m; ++i) {
        long long newcnt, newval;
        cin >> newcnt >> newval;
        candidate.push_back(make_pair(newval, newcnt));
    }
    sort(candidate.begin(), candidate.end(), greater<pair<long, long>>());


    for(auto [newval, newcnt]: candidate){
        while(newcnt > 0){

            auto [qval, qcnt] = pq.top();
            if(qval >= newval) break;
            pq.pop();
            if(newcnt >= qcnt) {
                newcnt -= qcnt;
                pq.push({newval, qcnt});
            } else { // newcnt < qcnt
                pq.push(make_pair(newval, newcnt));
                pq.push(make_pair(qval,  qcnt - newcnt));
                newcnt = 0;
            }
        }
    }
    ll ans = 0;
    while(!pq.empty()){
        auto [val, cnt] = pq.top();
        pq.pop();
        ans += val * cnt;
    }
    cout << ans << "\n";
}
