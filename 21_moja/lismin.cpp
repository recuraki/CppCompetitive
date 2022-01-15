#include <bits/stdc++.h>
using namespace std;
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)

int INF = 1e9+10;

int main(){
    int n; cin >> n;
    vector<int> l(n);
    REP(i, n) cin >> l.at(i);

    vector<int> lisDP(n, INF);
    vector<int> indexList(n, -1);
    REP(i, n){
        int ind = (int)distance(lisDP.begin(), lower_bound(lisDP.begin(), lisDP.end(), l.at(i)));
        lisDP.at(ind) = l[i];
        indexList.at(i) = ind;
    }
    int targetIndex = *max_element(indexList.begin(), indexList.end());
    vector<int> ans(targetIndex + 1);
    IREP(i, n){
        if(indexList.at(i) == targetIndex){
            ans.at(targetIndex) = l.at(i);
            --targetIndex;
        }
    }

    REP(i, ans.size() - 1) cout << ans.at(i) << " ";
    cout << ans.at(ans.size() - 1) << "\n";

}

