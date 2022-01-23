#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)

int n;
vector<vector<int>> dat;
int used = 0;
int ans = 0;
int f(const int &val, const int &low){
    if(used == pow(2, 2*n) - 1) {
        ans = max( ans, val);
    }
    int ans = 0;
    FOR(i, low,  2*n){
        if( ((used >> i) & 1) == 1 ) continue;
        used ^= 1 << i;
        FOR(j, i+1, 2* n){
            if( ((used >> j) & 1) == 1 ) continue;
            used ^= 1 << j;
            ans = max(ans, f( val^ dat[i][j-i-1], i+1));
            used ^= 1 << j;
        }
        used ^= 1 << i;
    }
    return ans;
}
using namespace std;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        unordered_set<int> ss;


        vector<vector<int>> ans;
        unordered_map<int, vector<int>> mp;

        for(int i = 0; i < nums.size(); ++i) mp[nums[i]].emplace_back(i);

        for(int i = 0; i < nums.size(); ++i){
            for(int j = i + 1; j < nums.size(); ++j){
                auto need = - (nums[i] + nums[j]);
                if(mp.count(need) == 0) continue;
                for(auto &k: mp[need]){
                    if(k < i) ans.push_back({nums[k], nums[i], nums[j]})
                    else if(k < i && k < j) ans.emplace_back({nums[i],nums[k], nums[j]})
                    else if(k < i && j < k) ans.emplace_back({nums[i],nums[j], nums[k]})
                }
            }
        }
        return ans;




    }
};

void solve(){
    cin >> n;
    dat.resize(2*n+1);
    int x;
    REP(i, 2*n-1){
        REP(j,2*n-1-i) {
            cin >> x;
            dat.at(i).emplace_back(x);
        }
    }
    f(0,  0);
    cout <<  ans << "\n";
}

int main() {
    FASTIO();
    solve();

}
