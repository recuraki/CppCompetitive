#include <bits/stdc++.h>
#include <atcoder/all>
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define REP(i, n) FOR(i,0,n)
using namespace std;
using namespace atcoder;
const int numNode = 2*100000;
const int numColor = 4 * 100000;
const int numGraph = numNode + numColor + 100;
const int snode = numGraph - 3;
const int tnode = numGraph - 2;ap

int main(int argc, char *argv[]) {
    int n, a, b;
    cin >> n;
    mf_graph<int> mf(numGraph);
    REP(i, n){
        cin >> a >> b;
        a += numNode; b += numNode;
        mf.add_edge(snode, i, 1);
        mf.add_edge(i, a, 1);
        mf.add_edge(i, b, 1);
    }
    FOR(i, numNode, numNode + numColor + 2){
        mf.add_edge(i, tnode, 1);
    }
    cout << mf.flow(snode, tnode) << endl;
}