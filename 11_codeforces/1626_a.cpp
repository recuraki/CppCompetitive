#include <bits/stdc++.h>
using namespace std;

void solve(){
    string s; cin >> s;
    unordered_map<char, int> mp;
    for(auto &c: s) ++mp[c];
    for(auto &[k, v]: mp){ if(v==2) cout << k;}
    for(auto &[k, v]: mp){ if(v==2) cout <<  k;}
    for(auto &[k, v]: mp){ if(v==1) cout << k;}
    cout << "\n";
}

int main(){
    int q; cin >> q;
    while(q--) solve();
    return 0;
}

