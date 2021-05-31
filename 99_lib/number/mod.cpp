//
// Created by kanai on 2021/05/22.
//

#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

// https://nagiss.hateblo.jp/entry/2019/07/01/185421
// d,x,y : d = bx + (a mod b) y
// 解が存在しない場合はb,0,1を返す
ll egcd(ll a, ll b, ll &x, ll &y){
    if(a == 0){
        x = 0; y = 1;
        return b;
    }
    auto d = egcd(b % a, a, y, x);
    x = x - (b / a) * y;
    return d;
}


main(){
    ll x, y, d;
    d = egcd(111, 30, x, y);
    assert(d == 3);
    assert(x == 3);
    assert(y == -11);
    if(x == 0) cout << "no d\n";
    else cout << d << ": " << x << ", " << y << "\n";

    d = egcd(111, 7, x, y);
    assert(d == 1);
    assert(x == -1);
    assert(y == 16);
    if(x == 0) cout << "no d\n";
    else cout << d << ": " << x << ", " << y << "\n";

    // 解なし
    d = egcd(13, 1, x, y);
    assert(x==0);
    if(x == 0) cout << "no d\n";
    else cout << d << ": " << x << ", " << y << "\n";

}