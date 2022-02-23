
#include <bits/stdc++.h>
#include <chrono>

// #include <atcoder/all>
using namespace std;
using ll = long long int;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

/*
 * HeavyLightDecomposition(n)
 * dfs1(0)
 * hld
 */
/*
 * hldListは
 */
template<typename T>
struct HeavyLightDecomposition{
    int n;
    vector<vector<int>> g;
    vector<int> depth;
    vector<int> parent; //
    vector<int> childNum; // そのノードの重さ。
    vector<int> shallowNode; // あるノードに関して、その所属する列のもっとも浅いノード
    vector<int> hldList; // hld的なリスト。中身は従来のノード
    vector<int> realNode; // HDL上のidを実際のノードIDにマップする

    HeavyLightDecomposition(int n) : n(n) {
        g = vector<vector<int>>(n, vector<int>());
        depth = vector<int>(n, -1);
        parent = vector<int>(n, -1);
        childNum = vector<int>(n, 1); // ノードも重さは最初1
        shallowNode = vector<int>(n, 0);
        hldList.clear();
        realNode = vector<int>(n, -1);
    }

    void makeEdge(const int &u, const int &v){
        // u <-> v でedgeを張る
        assert(u != v);
        g.at(u).push_back(v);
        g.at(v).push_back(u);
    }

    /* rootを根としてそれぞれの要素数と深さを求める */
    void dfs1(int root){
        _dfs1(root, 0);
        parent[root] = 0;
    }


    void hld(int cur, int topNode){
        cout << "hld()" << cur << " " << topNode << "\n";
        realNode[cur] = hldList.size();
        hldList.push_back(cur); // HLDのリストに詰む(ここから新しいやつの開始)
        shallowNode.at(cur) = topNode; // このノードの所属する最も浅い（＝列の先頭)のノード

        // 葉なら終わり
        if(childNum.at(cur) == 1) {
            cout << cur << " is leaf." << "\n";
            return;
        }

        int maxVal = 0;
        int maxInd = -1;
        // ここはfor(nn)で回せそうだが、後半でこのノード以外の探索をするのでこうせざるを得ない
        for(int i = 0; i < (int)g.at(cur).size(); ++i){
            int nn = g.at(cur).at(i);
            if(nn == parent.at(cur)) continue; // 親は無視する
            if(childNum.at(nn) > maxVal){
                maxVal = childNum.at(nn);
                maxInd = i;
            }
        }
        cout << "heavy node:" << g[cur][maxInd] << " val: "<< maxVal << "\n";

        hld(g.at(cur).at(maxInd), topNode);

        for(int i = 0; i < (int)g.at(cur).size(); ++i){
            auto nn = g.at(cur).at(i);
            if(nn == parent.at(cur)) continue; // 親は無視する
            if(i == maxInd) continue;
            hld(nn, nn);
        }
    }

    // u,vの2点のパスを求める
    vector<pair<int, int>> query(int u, int v){
        vector<pair<int, int>> ans;
        while(shallowNode.at(u) != shallowNode.at(v)){ // 同じ列にいるかを確認する
            // u,vそれぞれの最も浅いノードの深さ　が　浅い方をuにする
            // u, v 自身の深さの比較でないことに注意する
            if(depth.at(shallowNode.at(u)) > depth.at(shallowNode.at(v))) swap(u, v);
            // 深い方は親をたどるので、{v, vの浅いノード} の区間を答えにする
            ans.push_back({realNode.at(shallowNode.at(v)), realNode.at(v)});

            v = parent.at(shallowNode.at(v));
        }
        // ここで、u, vは同じ列にいる。ただ、どっちが根側かわからない
        cout << "finally" << u << " " << v << " " << realNode.at(u) << " " << realNode.at(v)<<"\n";
        pair<int, int> lastEntry = {realNode.at(u), realNode.at(v)};
        if(lastEntry.first > lastEntry.second) swap(lastEntry.first, lastEntry.second);
        ans.push_back(lastEntry);
        return ans;
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
            cout << "childnum "  << childNum.at(i) << " ";
            cout << "depth " << depth.at(i) << " ";
            cout << "\n";
        }
    }

    void debugHLD(){
        // HLDの結果をdumpする
        cout << "Debug HLD" << "\n";
        cout << "HLD List: ";
        for(auto &x: hldList) cout << x << " ";
        cout << "\n";
        cout << "ReverseMap: ";
        for(auto &x: realNode) cout << x << " ";
        cout << "\n";
        cout << "Shallow Node: ";
        for(auto &x: shallowNode) cout << x << " ";
        cout << "\n";
    }



private:
    void _dfs1(const int &root, const int &d){
        depth.at(root) = d;
        cout << "call dfs " << root << "\n";
        for(const auto &nn: g.at(root)){ // 子ノードを見る
            if(parent[nn] != -1) continue; // 探索済みなら処理しない
            cout << " cocall " << root << "\n";
            parent[nn] = root; // 次のノードの親は自分
            _dfs1(nn, d + 1);
            // DFS後、そのノードのノード数を自分に足す
            childNum.at(root) += childNum.at(nn);
            cout << " agg node " << root << " " << nn << " " << childNum.at(nn) <<  "\n";
        }
        cout << "agg" << root << " " << childNum.at(root) << "\n";
    }
};

// https://qiita.com/Pro_ktmr/items/4e1e051ea0561772afa3#%E3%81%AA%E3%81%9C%E3%81%A9%E3%82%93%E3%81%AA%E3%83%91%E3%82%B9%E3%82%82-olog-n-%E5%80%8B%E3%81%AE%E9%80%A3%E7%B5%90%E6%88%90%E5%88%86%E3%82%92%E9%80%9A%E3%82%8B%E3%81%AE%E3%81%8B
void sample1(){
    int n = 12;
    vector<int> dat = {-1, 0, 1, 2, 2, 1, 0, 6, 7, 7, 0, 10};
    //int q = 1;
    vector<pair<int, int>> queries = {{4, 9}, {2, 10},{7,9}};
    HeavyLightDecomposition<int> st(n);
    for(int i = 0; i < (int)dat.size(); ++i){
        if(dat.at(i) == -1) continue;
        st.makeEdge(i, dat.at(i));
    }
    st.debugEdge();
    st.dfs1(0);
    st.debugDFS();
    st.hld(0, 0);
    st.debugHLD();
    for(const auto &[u, v]: queries) {
        auto ans = st.query(u, v);
        for (const auto &[a, b]: ans) {
            cout << "[" << a << ", " << b << "] ";
        }
        cout << "\n";
    }
}
void sample2(){
    int n = 4;
    vector<int> dat = {-1, 2, 0, 0};
    //int q = 1;
    vector<pair<int, int>> queries = {{1, 2}};
    HeavyLightDecomposition<int> st(n);
    for(int i = 0; i < (int)dat.size(); ++i){
        if(dat.at(i) == -1) continue;
        st.makeEdge(i, dat.at(i));
    }
    st.debugEdge();
    st.dfs1(0);
    st.debugDFS();
    st.hld(0, 0);
    st.debugHLD();
    for(const auto &[u, v]: queries) {
        auto ans = st.query(u, v);
        for (const auto &[a, b]: ans) {
            cout << "[" << a << ", " << b << "] ";
        }
        cout << "\n";
    }
}

int main(){
    sample2();
    return 0;
}