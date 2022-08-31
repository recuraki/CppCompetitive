//
// Created by kanai on 2022/08/30.
//
#include <bits/stdc++.h>
//#include <chrono>
using namespace std;
using ll = long long int;
#define FASTIOpre() cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

// https://ei1333.github.io/algorithm/namori.html
/*
 * なもりグラフ
 * N頂点 N辺の無向グラフは１つの閉路を含むグラフである。これを閉路とそれ以外に分解する。
 * なもりグラフは閉路に木が繋がっていると見做せるので、solveした結果は、groupに
 * -1のとき: 閉路
 * それ以外の時: 各線のグループが所属する閉路のノード番号　を格納する。
 * 例えば、次のグラフを考える。
 * 0 -- 1 -- 2
 *      |    |
 *      3 -- 4 -- 5 -- 6
 *                |
 *                7
 *  この時、1,2,3,4は閉路をなすので group -1
 *  0は閉路のノード1に所属するとして group 1
 *  5,6,7は閉路のノード4に所属するとして group 4
 *  を返す。
 *
 * makeEdge2Way: 辺をu<->vで辺を張る
 */
struct Namori{
    int n;
    int alledgenum;
    bool solved;
    vector<vector<int>> g;
    vector<int> edgecnt;
    vector<int> group;

    Namori(int n) : n(n) {
        g = vector<vector<int>>(n, vector<int>());
        edgecnt = vector<int>(n);
        group = vector<int>(n, -1);
        alledgenum = 0;
        solved = false;
    }

    void makeEdge2Way(const int &u, const int &v){
        // u <-> v でedgeを張る
        assert(u != v);
        g.at(u).push_back(v);
        g.at(v).push_back(u);
        ++alledgenum;
        ++edgecnt.at(u); ++edgecnt.at(v);
    }

    void solve(){
        assert(solved == false); // 多重solve防止
        assert(alledgenum == n); // なもりグラフか？
        solved = true;
        vector<int> q;
        vector<bool> visited(n);
        // 最初に閉路を検出するDFS. 辺の数が1のノードを狩っていく。
        // 閉路ではない区間は一旦-2を設定しておく
        auto dfs = [&](auto &&self, int cur) -> void{
            if(edgecnt.at(cur) != 1) return;
            if(visited.at(cur)) return;
            group.at(cur) = -2;
            visited.at(cur) = true;
            for(auto &nxt: g.at(cur)){
                if(visited.at(nxt)) continue;
                --edgecnt.at(nxt);
                self(self, nxt);
            }
        };

        // 次数1のノードを探索
        REP(cur, n) dfs(dfs, cur);

        // これで、group = -1のノードは閉路を構成する要素になったので、
        // 今度は閉路側のノードを全てみる。
        auto dfs2 = [&](auto &&self, int cur, int loopParent) -> void{
            if(group.at(cur) == -2) group.at(cur) = loopParent;
            for(auto &nxt: g.at(cur)){
                if(group.at(nxt) != -2) continue;
                self(self, nxt, loopParent);
            }
        };
        // 閉路のノードだった場合、そこから閉路以外のノードを辿る
        REP(cur, n){
            if(group.at(cur) == -1) dfs2(dfs2, cur, cur);
        }
    }
    void dump_isloop(){
        cout << "Namori dump: isloop?" << endl;
        REP(i, n){
            if(group.at(i) == -1){
                cout << " node[" << i << "]: Loop" << endl;
            } else{
                cout << " node[" << i << "]: group " << group.at(i)<< endl;
            }
        }
    }
};

// https://atcoder.jp/contests/abc266/tasks/abc266_f
void abc266f(){
    int n; cin >> n;
    Namori namori(n);
    REP(i, n){
        int u, v; cin >> u >> v;
        --u; --v;
        namori.makeEdge2Way(u, v);
    }
    namori.solve();
    //namori.dump_isloop();
    int m; cin >> m;
    REP(i, m){
        int u, v; cin >> u >> v;
        --u; --v;
        // 両方が閉路である場合時計回り、半時計周りがあるのでNo
        if(namori.group[u] == -1 && namori.group[v] == -1) cout << "No" << endl;
        // 片方が閉路上のノードであるが、もう一方がその閉路から出ている木のノードならYes
        else if(namori.group[u] == -1 && namori.group[v] == u) cout << "Yes" << endl;
        else if(namori.group[v] == -1 && namori.group[u] == v) cout << "Yes" << endl;
        // 両方が(-1ではない)同じ木に所属するならYes
        else if(namori.group[u] == namori.group[v]) cout << "Yes" << endl;
        // これ以外というのは、閉路上の適当なノードと木のノード、　あるいは、　異なる閉路上のノード上の木なので、
        // 閉路上で時計回りと半時計周りを辿れてしまうのでNo
        else cout << "No" << endl;
    }

}

void test(){
    Namori namori(5);
    namori.makeEdge2Way(0,1);
    namori.makeEdge2Way(1,2);
    namori.makeEdge2Way(2,3);
    namori.makeEdge2Way(3,4);
    namori.makeEdge2Way(1, 3);
    namori.solve();
    namori.dump_isloop();
}
int main(){
    //test();
    abc266f();
    return 0;
}
