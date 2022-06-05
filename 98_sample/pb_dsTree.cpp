#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll = long long int;
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define REP(i, n) FOR(i,0,n)
#define FASTIOpre() cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);

// https://atcoder.jp/contests/abc241/tasks/abc241_d
void abc241_d() {
    FASTIOpre();
    // treeはsetでmultisetでないため、int64をmultisetとして使うなら、__int128に乗せて<<18 + i + 1などする
    // 　取得した値を使うときは、 >> 18する。このtreeから取得した値を再度クエリするときは >> 18 と << 18する。
    // 以下のクエリはless<T>で問題ない
    // order_of_key(x) x以上が何個存在するか？
    // find_by_order(x) x番目に大きな要素(0-indexedに注意) の イテレータ
    // 順位   6  5    4   3   2   1 (1indexed)
    // 順位   5  4    3   2   1   0 (0indexed)
    // order 5  4    3   2   1    0 (で返す値。つまり、順位を返している)
    // 値    a1  a2  a3  a4  a5  a6 (が、昇順に並んでいるとする)

    tree<__int128, null_type, less<__int128>, rb_tree_tag, tree_order_statistics_node_update> dat;
    int q; cin >> q;
    vector<ll> l;
    REP(i, q){
        ll t; cin >> t;
        int target = -1; // 何番目の数がほしい？
        if(t == 1){
            ll x; cin >> x;
            dat.insert(((__int128)x << 18) + i + 1);
            continue;
        } else if(t == 2) {
            ll x, k; cin >> x >> k;
            auto tmp = dat.order_of_key((__int128)(x+1) << 18); // xよりも大きい数
            target = tmp - k; // x以上の数はtmp - 1からなので、 -k したのがほしい番号
        } else if(t == 3){
            ll x, k; cin >> x >> k;
            auto tmp = dat.order_of_key((__int128)x << 18); // x以上の数
            target = tmp + k - 1; // x以上の数はtmpから始まっているので-1する
        }
        if(target < 0) cout << -1 << "\n";
        else if(target >= dat.size()) cout << -1 << "\n";
        else {
            // __int128はostreamに<<できないのでlong longにキャストする。この際、__128の間に>>18すること
            cout << (long long)(*dat.find_by_order(target) >> 18)<< "\n";
        }
    }
}

// https://hogloid.hatenablog.com/entry/2014/09/23/132440
void sample(){

    vector<long long> data = {3, 5,6,7,8,9};
    tree<long long, null_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> treeless;
    for(auto &x: data) treeless.insert(x);
    // find_by_order(k) で【昇順で】k番目（0-indexed）のiteratorを返します。
    cout << *treeless.find_by_order(0) << "\n"; // > 3
    cout << *treeless.find_by_order(5) << "\n"; // > 9
    cout << *treeless.find_by_order(6) << "\n"; // > 0 Cation
    cout << *treeless.find_by_order(100) << "\n"; // > 0 Cation
    cout << "-" << "\n";
    // order_of_key(key) でkey【以上】の最初の要素が、treeの中で【下から】何番目(0-indexed)か返します。(inclusive)
    cout << treeless.order_of_key(3) << "\n"; // > 0
    cout << treeless.order_of_key(1) << "\n"; // > 0
    cout << treeless.order_of_key(9) << "\n"; // > 5
    cout << treeless.order_of_key(10) << "\n"; // > 6 == size()
    cout << "-" << "\n";
    // 普通のlower_boundです
    cout << *treeless.lower_bound(1) << "\n"; // 3
    cout << *treeless.lower_bound(2) << "\n"; // 3
    cout << *treeless.lower_bound(3) << "\n"; // 3
    cout << *treeless.lower_bound(4) << "\n"; // 5
    cout << "----------" << "\n";
    // key【以上】の最初の要素が、treeの中で【上から】何番目(0-indexed)か返します。(inclusive)
    // この数を+1すると、”key以上の数が何個あるか？”になります
    auto order_of_key_from_big = [&](long long r_key){
        return treeless.size() - 1 - treeless.order_of_key(r_key);
    };


    cout << "----------+" << "\n";

    // Greaterはlower_bound, upper_boundが直観と反するので気を付けた方が良い
    tree<long long, null_type, greater<long long>, rb_tree_tag, tree_order_statistics_node_update> treegreater;
    for(auto &x: data) treegreater.insert(x);
    // find_by_order(k) で【降順で】k番目（0-indexed）のiteratorを返します。
    cout << *treegreater.find_by_order(0) << "\n"; // > 9
    cout << *treegreater.find_by_order(5) << "\n"; // > 3
    cout << *treegreater.find_by_order(6) << "\n"; // > 0 Cation
    cout << *treegreater.find_by_order(100) << "\n"; // > 0 Cation
    // order_of_key(key) でkey【以下】の最初の要素が、treeの中で何番目か返します。(inclusive)
    cout << treegreater.order_of_key(3) << "\n"; // > 5
    cout << treegreater.order_of_key(4) << "\n"; // > 5
    cout << treegreater.order_of_key(1) << "\n"; // > 6
    cout << treegreater.order_of_key(9) << "\n"; // > 0
    cout << treegreater.order_of_key(10) << "\n"; // > 0
    cout << "-" << "\n";
    cout << *treegreater.lower_bound(1) << "\n"; // 0
    cout << *treegreater.lower_bound(2) << "\n"; // 0
    cout << *treegreater.lower_bound(3) << "\n"; // 3
    cout << *treegreater.lower_bound(4) << "\n"; // 3


}
int main(){
    sample();
    //abc241_d();
}