#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <stack>
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)


template<class T> inline bool chmin(T& a, T b) {if (a > b) {a = b; return true;} return false;}
template<class T> inline bool chmax(T& a, T b) {if (a < b) {a = b; return true;} return false;}

//////////////////////////////////////
#include <iostream>
using namespace std;
#define dp(arg) do { cout << #arg << ":"; dprint(arg); } while(0)

template <typename T> void dprint(T arg) { cout << arg << "\n"; }
template <typename T> void dprint(const vector<T>& arg) { for_each(begin(arg), end(arg), [](T value){ cout << value << " "; }   ); cout << "\n";  }
template <typename T> void dprint(const vector<vector<T>>& arg) { for_each(begin(arg), end(arg), [=](vector<T> arg2){ dprint(arg2); cout << "\n";} );  }


//////////////////////////////////////
#define ll long long int

struct qdata{
    int curNode = 0;
    int curDepth = 0;
};

/*
 * オイラーツアー
 * T: 辺と頂点のコストの型
 */
template<typename T>
class eulerTour{
public:
    struct edge{
        T cost;
        int nextNodeId;
    };

    const T INF = numeric_limits< T >::max();
    T mod = 1e9 + 7;
    vector<int> depth;
    vector<int> nodeIn;
    vector<int> nodeOut;
    vector<int> parent;
    vector<vector<edge>> graph;


    eulerTour(int nodeNum){
        this->graph.resize(nodeNum);
        this->nodeNum = nodeNum;
        this->depth.resize(nodeNum);
        this->nodeIn.resize(nodeNum, -1);
        this->nodeOut.resize(nodeNum, -1);
        this->parent.resize(nodeNum, -1);
    }

    // Unidirection
    void makeEdge(int curnode, int nextnode, T cost){
        assert(curnode < this->nodeNum);
        assert(nextnode < this->nodeNum);
        this->graph.at(curnode).emplace_back((edge){cost, nextnode});
    }

    struct qdata{
        int id;
        int nodeDepth;
    };

    void solve(int rootNode){
        qdata curDat;
        qdata nextDat;
        qdata nextDat2;
        qdata nextDat3;
        stack<qdata> q;
        curDat.nodeDepth = 0;
        curDat.id = rootNode;
        q.push(qdata{0, 0});
        int curtime = -1;
        bool isLeaf;

        // depth は visited (さかのぼり禁止)にも使われる
        while(q.size() > 0){
            ++curtime; // timeをインクリメントして
            curDat = q.top(); q.pop(); // 次に進む
            // 訪問が行きがけ(正の値)のとき
            if(curDat.id >= 0) {
                // もし、初めての訪問なら、Intimeを打刻 基本的には１度しかないはずだが。
                if (this->nodeIn.at(curDat.id) == -1) this->nodeIn.at(curDat.id) = curtime;
                this->depth.at(curDat.id) = curDat.nodeDepth; // 深さを打刻
                isLeaf = true; // leafかの判定
                for(edge nextNode: this->graph[curDat.id]){
                    if(this->depth.at(nextNode.nextNodeId) != -1) continue; // 処理したことのないノードか？
                    isLeaf = false; // 処理した場合、葉ではない
                    // 帰りがけの情報を埋める
                    q.push(qdata{(-curDat.id - 1), curDat.nodeDepth});
                    // 次のノード情報を書く
                    q.push(qdata{nextNode, curDat.nodeDepth + 1});
                }
                // 葉の場合は自分の戻り掛けの時間だけを記録する。
                if(isLeaf){
                    nextDat3.id = (-curDat.id - 1);
                    nextDat3.nodeDepth = curDat.nodeDepth;
                    q.push(nextDat3);
                }
            // 訪問が帰りがけ(負の値)のとき
            } else {
                curDat.id  = -curDat.id - 1; // それを戻す
                // TODO: これはないはずでは？
                if(this->nodeIn.at(curDat.id) == -1) this->nodeIn.at(curDat.id) = curtime;
                // 帰りがけなので、outの時間を更新 これは複数回呼ばれても良い。最後のモノだけを取ればいいから。
                this->nodeOut.at(curDat.id) = curtime + 1;
            }
        }

    }


}

int main(int argc, char *argv[]) {
    qdata curDat;
    qdata nextDat;
    qdata nextDat2;
    qdata nextDat3;
    stack<qdata> q;
    curDat.curDepth = 0;
    curDat.curNode = rootnode;
    q.push(curDat);
    int curtime = -1;
    bool isLeaf;
    while(q.size() > 0){
        ++curtime;
        curDat = q.top();
        q.pop();
        if(curDat.curNode >= 0) {
            if (nodeIn[curDat.curNode] == -1) nodeIn[curDat.curNode] = curtime;
            depth[curDat.curNode] = curDat.curDepth;
            isLeaf = true;
            for(auto nextNode: G[curDat.curNode]){
                if(depth[nextNode] != -1) continue;
                isLeaf = false;
                nextDat.curNode = (-curDat.curNode-1);
                nextDat.curDepth = curDat.curDepth;
                q.push(nextDat);
                nextDat2.curNode = (nextNode);
                nextDat2.curDepth = curDat.curDepth + 1;
                q.push(nextDat2);
            }
            if(isLeaf == true){
                nextDat3.curNode = (-curDat.curNode-1);
                nextDat3.curDepth = curDat.curDepth;
                q.push(nextDat3);

            }
        } else {
            curDat.curNode  = -curDat.curNode - 1;
            if(nodeIn[curDat.curNode] == -1) nodeIn[curDat.curNode] = curtime;
            nodeOut[curDat.curNode] = curtime + 1;
        }
    }
    int qq;
    cin >> qq;
    vector<ll> imos(curtime + 10);
    REP(i, curtime + 10){
        imos[i] = 0;
    }
    pair<ll, ll> edat;
    ll t, e, x;
    ll ain, aout, bin, bout;
    REP(qqq, qq){
        cin >> t >> e >> x;
        edat = dat[e-1];
        if(t == 1){
            ain = nodeIn[edat.first];
            aout = nodeOut[edat.first];
            bin = nodeIn[edat.second];
            bout = nodeOut[edat.second];
        } else {
            ain = nodeIn[edat.second];
            aout = nodeOut[edat.second];
            bin = nodeIn[edat.first];
            bout = nodeOut[edat.first];
        }
        if(ain > bin) {
            imos[ain] += x;
            imos[aout + 1] += -x;
        } else {
            imos[0] += x;
            imos[bin] += -x;
            imos[bout + 1] += x;
            imos[curtime + 2] += -x;
        }

    }
    ll cur = 0;
    vector<ll> buf(curtime + 10);
    REP(i, curtime + 5){
        cur += imos[i];
        buf[i] = cur;
    }
    REP(i, n) {
        //cout << nodeIn[i] << "\n";
    }
    REP(i, n){
        cout << buf[nodeIn[i]] << "\n";
    }
    REP(i, n){
    }
}

