#include <bits/stdc++.h>
//#include <chrono>
#include <atcoder/all>
using namespace std;
using ll = long long int;
#define FASTIOpre() cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

// https://qiita.com/Pro_ktmr/items/4e1e051ea0561772afa3#%E3%81%AA%E3%81%9C%E3%81%A9%E3%82%93%E3%81%AA%E3%83%91%E3%82%B9%E3%82%82-olog-n-%E5%80%8B%E3%81%AE%E9%80%A3%E7%B5%90%E6%88%90%E5%88%86%E3%82%92%E9%80%9A%E3%82%8B%E3%81%AE%E3%81%8B
/*
 * HeavyLightDecomposition(n)
 * HL分解をします。
 * 1: この構造を(n)で呼びます。nはノード数です。0-indexed。make_edge()で木を作ります
 * 2: hdl()を投げると、vector<int>(n)が返ってきて、これは[i] = j
 *    入力したiのノードはHLDの配列のjにマッピングされたということを示します
 * 3: 呼んだ側で、このマッピングをもとにたとえばセグ木など区間クエリできる構造体を作っておきます
 * 4: query(u, v)を呼ぶとvector<pair<int, int>が返ってきます。
 *    各pairの[a,b]はHLDの配列での「閉区間」のクエリを返します。
 *    これら全てに対して、seg.prod(a, b+1) (pairは閉区間なので適度にクエリしてください)します
 *    これらの結果は適切に結合します。
 */
/*
 * コード中でreal, hld のid/nodeという表記がありますが、
 * real: 入力時点での木のノード番号
 * hld: HLDの配列上のindex
 * を示します。
 */

struct HeavyLightDecomposition{
    int n;
    vector<vector<int>> g;
    vector<int> depthRealnode; // 実ノードの深さ
    vector<int> parentRealnode; // 実IDでの親(実ID)
    vector<int> childNumRealnode; // そのノードの重さ＝部分木のノード数。そのノード自身を1としてカウントします。
    vector<int> shallowRealnode; // ある実ノードに関して、その所属する列のもっとも浅いノード(実ID)
    vector<int> realid2hldid; // 実際のリストがHLDのいくつにマップされたのか？
    vector<int> hldid2realid;  // HLDリストの何は実際に何か？
    vector<int> hldidEndSubtree; // そのindexの部分木がなんのindexまで続いているか。 [i] = j のとき、iの部分木はjまで(含む)

    HeavyLightDecomposition(int n) : n(n) {
        g = vector<vector<int>>(n, vector<int>());
        depthRealnode = vector<int>(n, -1);
        parentRealnode = vector<int>(n, -1);
        childNumRealnode = vector<int>(n, 1); // ノードも重さは最初1
        shallowRealnode = vector<int>(n, 0);
        realid2hldid = vector<int>(n, -1);
        hldid2realid.clear();
        hldidEndSubtree = vector<int>(n, -1);
    }

    void makeEdge(const int &u, const int &v){
        // u <-> v でedgeを張る
        assert(u != v);
        g.at(u).push_back(v);
        g.at(v).push_back(u);
    }

    // HL分解を行い、その結果の[real]=hldのマッピングを返します
    vector<int> hld(int rootRealnode){
        dfs(rootRealnode, 0);
        _hld(rootRealnode, 0);
        return realid2hldid;
    }

    // uRealnode,vの2点のパスを求めます。これはHLD上のIDで返されます。(何故なら、後で区間クエリ死体から)
    vector<pair<int, int>> query(int uRealnode, int vRealnode){
        vector<pair<int, int>> ansHldIDs;
        //同じ列状になるまで計算を続ける
        while(shallowRealnode.at(uRealnode) != shallowRealnode.at(vRealnode)){
            //cout << "real " << uRealnode << " " << vRealnode << " HLDworld: " << realid2hldid.at(uRealnode) << " " << realid2hldid.at(vRealnode) << "\n";
            //cout << " top(real):" << shallowRealnode.at(uRealnode) << "\n";
            // uRealnode,vそれぞれの最も浅いノードの深さ　が　浅い方をuにする
            // ※uRealnode, vRealnode 自身の深さの比較でないことに注意する
            // これによってrootの列にいるノードがさらに列を上らないようにします
            if(depthRealnode.at(shallowRealnode.at(uRealnode)) > depthRealnode.at(shallowRealnode.at(vRealnode))) swap(uRealnode, vRealnode);

            // 深い方は親をたどるので、{vRealnode, vの浅いノード} の区間を答えとして、vRealnodeを更新する
            ansHldIDs.push_back({realid2hldid.at(shallowRealnode.at(vRealnode)), realid2hldid.at(vRealnode)});
            vRealnode = parentRealnode.at(shallowRealnode.at(vRealnode));
        }
        // ここで、uRealnode, vはおなじ列に来たので、最後の処理を行う。区間クエリに備えて first <= secondで値を保存
        //cout << "finally real " << uRealnode << " " << vRealnode << " HLDworld: " << realid2hldid.at(uRealnode) << " " << realid2hldid.at(vRealnode) << "\n";
        //cout << " same top(real):" << shallowRealnode.at(uRealnode) << "\n";
        pair<int, int> lastEntry = {realid2hldid.at(uRealnode), realid2hldid.at(vRealnode)};
        if(lastEntry.first > lastEntry.second) swap(lastEntry.first, lastEntry.second);
        ansHldIDs.push_back(lastEntry);
        return ansHldIDs;
    }

    // HLDの前処理。各実ノードの深さと親を掘る
    // 計算量: O(N)
    void dfs(int root, int d) {
        depthRealnode.at(root) = d;
        for(int i = 0; i < (int)g.at(root).size(); ++i){
            auto nn = g.at(root).at(i);
        //for (const auto &nn: g.at(root)) { // 子ノードを見る
            if (parentRealnode[nn] != -1) continue; // 探索済みなら処理しない
            if (nn == parentRealnode[root]) continue; // 親には戻らない
            parentRealnode[nn] = root; // 次のノードの親は自分
            dfs(nn, d + 1);
            // DFS後、そのノードのノード数を自分に足す
            childNumRealnode.at(root) += childNumRealnode.at(nn);
        }
    }

    // HL分解をする。
    void _hld(int curRealnode, int topNode){
        //cout << "hld()" << curRealnode << " " << topNode << "\n";
        realid2hldid[curRealnode] = hldid2realid.size(); // 実際のノードの何がHLDリストの何番となるか？(次に配列に入るindexを得る)
        hldid2realid.push_back(curRealnode); // HLDID -> RealIDのマップ
        shallowRealnode.at(curRealnode) = topNode; // このノードの所属する最も浅い（＝列の先頭)のノード
        if(childNumRealnode.at(curRealnode) == 1) {
            hldidEndSubtree[realid2hldid.at(curRealnode)] = hldid2realid.size() - 1;
            return; // 葉ならこれで終わり
        }

        // ここから子の探索
        int maxVal = 0;
        int maxInd = -1;
        //for(auto nn: g.at(curRealnode)){ // 再帰が深いのでこの書き方はダメ
        for(int i = 0; i < (int)g.at(curRealnode).size(); ++i){
            auto nn = g.at(curRealnode).at(i);
            if(nn == parentRealnode.at(curRealnode)) continue; // 親は無視する
            if(childNumRealnode.at(nn) > maxVal){ // Heavyを探して更新。
                maxVal = childNumRealnode.at(nn);
                maxInd = nn;
            }
        }
        //cout << "heavy node:" << g[curRealnode][maxInd] << " val: "<< maxVal << "\n";
        _hld(maxInd, topNode);

        for(int i = 0; i < (int)g.at(curRealnode).size(); ++i){
            auto nn = g.at(curRealnode).at(i);
            if(nn == parentRealnode.at(curRealnode)) continue; // 親は無視する
            if(nn == maxInd) continue; // Heavyだった先も無視する
            _hld(nn, nn); // Lightを見ていく。この時、shallowNodeはそのノードとなる。
        }
        // ノードの探索が終わったので、このcurRealnodeの部分木の終わりのhldidを得る
        hldidEndSubtree[realid2hldid.at(curRealnode)] = hldid2realid.size() - 1;
    }

    void debugEdge(){
        cout << "Debug Edge" << "\n";
        for(int i = 0; i < n; ++i){
            cout << "[" << i << "]:";
            for(const auto &x: g.at(i)) cout << " " << x;
            cout << "\n";
        }
    }

    void debugDFS(){
        // DFSの結果をdumpする。そのノードの
        cout << "Debug DSF" << "\n";
        cout << "childnum means a number of sub-tree with itself" << "\n";
        for(int i = 0; i < n; ++i){
            cout << "node [" << i << "]: ";
            cout << "childnum " << childNumRealnode.at(i) << " ";
            cout << "depthRealnode " << depthRealnode.at(i) << " ";
            cout << "\n";
        }
    }

    void debugHLD(){
        // HLDの結果をdumpする
        cout << "Debug HLD" << "\n";
        cout << "Real List: ";
        for(auto &x: realid2hldid) cout << x << " ";
        cout << "\n";
        cout << "HLD List: ";
        for(auto &x: hldid2realid) cout << x << " ";
        cout << "\n";
        cout << "ReverseMap: ";
        for(auto &x: realid2hldid) cout << x << " ";
        cout << "\n";
        cout << "Shallow Node: ";
        for(auto &x: shallowRealnode) cout << x << " ";
        cout << "\n";
    }


};


void sample1(){
    int n = 12;
    vector<int> dat = {-1, 0, 1, 2, 2, 1, 0, 6, 7, 7, 0, 10};
    //int q = 1;
    vector<pair<int, int>> queries = {{4, 9}, {2, 10},{7,9}};
    HeavyLightDecomposition st(n);
    for(int i = 0; i < (int)dat.size(); ++i){
        if(dat.at(i) == -1) continue;
        st.makeEdge(i, dat.at(i));
    }
    st.debugEdge();

    st.hld(0);
    st.debugDFS();    st.debugHLD();
    for(const auto &[u, v]: queries) {
        auto ans = st.query(u, v);
        for (const auto &[a, b]: ans) {
            cout << "[" << a << ", " << b << "] ";
        }
        cout << "\n";
    }
}

// LCA
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=jp
void GRL_5_C(){
    int n; cin >> n;
    HeavyLightDecomposition st(n);
    // 辺を貼る
    REP(i, n){
        int k; cin >> k;
        int x;
        REP(j, k){
            cin >> x;
            st.makeEdge(i, x);
        }
    }
    const auto &hldmap = st.hld(0);
    //st.debugHLD();

    /*
     * HL分解を行ったあと、探索のリストの最後(ans.back)のfirstがLCAのノードである
     */
    int q; cin >> q;
    REP(i, q){
        int u, v; cin >> u >> v;
        //cout << "// " << u << ","<< v;
        auto ans = st.query(u, v);
        auto &[a, b] = ans.back();
        // ただし、HLD配列用のIndexになっているので戻して出力
        cout << st.hldid2realid[a] << "\n";
    }
};

// HL分解典型
// https://judge.yosupo.jp/problem/vertex_add_path_sum
long long op(long long a,long long b){ return a+b; }
long long e(){return 0;}
void vertex_add_path_sum(){
    int n, q; cin >> n >> q;
    vector<int> dat(n);
    REP(i, n) cin >> dat.at(i);

    HeavyLightDecomposition hld(n);
    // 区間クエリ、1点可算可能ならば良いのでBITでも良い
    atcoder::segtree<long long ,op, e> st(n);
    REP(i, n-1){
        int u, v; cin >> u >> v;
        hld.makeEdge(u, v);
    }
    auto hldmap = hld.hld(0);
    for(int i = 0; i < n; ++i) st.set(hldmap[i], dat[i]);
    while(q--){
        int type; cin >> type;
        if(type == 0) { // update p を x にする
            long long p, x; cin >> p >> x;
            // segtreeなのでp = [p, p+1) + xしている
            st.set(hldmap[p], st.prod(hldmap[p], hldmap[p]+1) + x);
        } else { // query
            int u, v; cin >> u >> v;
            auto ans = hld.query(u, v);
            long long ret = 0;
            for (const auto &[a, b]: ans) {
                // a,bはHLDのIDなのでそのまま食わせてよい
                ret += st.prod(a, b + 1);
            }
            cout << ret << "\n";
        }
    }
}

// https://atcoder.jp/contests/abc138/tasks/abc138_d
struct S138{
    long long value;
    int size;
};
// 区間可算、区間和クエリ
S138 op138(S138 a, S138 b){ return {a.value+b.value, a.size+b.size}; }
S138 e138(){ return {0, 0}; }
S138 mapping(long long f, S138 x){ return {x.value + f*x.size, x.size}; }
long long composition(long long f, long long g){ return f+g; }
long long id(){ return 0; }
void abc138d(){
    int n, q; cin >> n >> q;
    HeavyLightDecomposition hld(n);
    std::vector<S138> v(n, {0, 1});
    atcoder::lazy_segtree<S138, op138, e138, long long, mapping, composition, id> seg(v);
    // 辺を貼る
    REP(i, n - 1){
        int a, b;
        cin >> a >> b;
        --a; --b;
        hld.makeEdge(a, b);
    }
    hld.hld(0);
    // クエリに応える
    REP(i, q){
        int p; long long x;
        cin >> p >> x;
        --p;
        // l, rはp, pの部分木の最後のノード+1(開区間だから) にxを足す(mappintする)
        auto hldid = hld.realid2hldid.at(p); // hldidへマッピング
        seg.apply(hldid, hld.hldidEndSubtree.at(hldid) + 1, x);
    }
    // 結果はnode0からhldidに変換しながら回答
    REP(i, n) cout << seg.get(hld.realid2hldid.at(i)).value << " ";
    cout << "\n";
}


int main(){
    FASTIOpre();
    //sample1();
    //GRL_5_C();
    //vertex_add_path_sum();
    abc138d();

    return 0;
}