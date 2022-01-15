#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
#define FASTIOpre() cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);


/*
* この実装は抽象化しているように見せかけて抽象化しきれていない
* この実装はノードの数やノード自身のコストを数えるのには使えるが、
* 辺がコストを持つ場合はうまくいかない。(辺にcostを持たせているに使っていない)
*/
template <class S, S (*op)(S, S, ll), S (*e)(), S (*initNodeValue)()> struct rerooting{
public:

    // 辺の持つ情報(make_edgeで辺が持つ情報)
typedef long long EDGECOSTTYPE;
struct edge{
    int nextnode;
EDGECOSTTYPE cost;
};

vector<S> dat;
vector<vector<edge>> G;
vector<int> parent;
bool isDFS;
int n;

// コンストラクタは頂点の数だけ与える
rerooting(const int n){
                      // 全頂点を初期値に設定
dat = vector<S>(n, initNodeValue());
G = vector<vector<edge>>(n, vector<edge>());
this->n = n;
// -2をUNUSEということにする
parent = vector<int>(n, -2);
isDFS = false;
}

// 無向辺を張る
void make_edge(const int s, const int t, const ll w){
    G.at(s).emplace_back(edge{t, w});
G.at(t).emplace_back(edge{s, w});
}

// dfsのヘルパー(rootノードの)
void dfs(const int rootnode) {
assert(!isDFS); // 2度 DFS NG
dfsCoroutine(rootnode, -1);
isDFS = true;
}
// DPを行い、葉のノードから親のノードにop()する
void dfsCoroutine(const int curnode, const int rootnode){
    parent.at(curnode) = rootnode;
for(auto x: G.at(curnode)) {
if (parent.at(x.nextnode) != -2) continue;
dfsCoroutine(x.nextnode, curnode);
dat.at(curnode) = op(dat.at(curnode), dat.at(x.nextnode), x.cost);
}
}

// rerootするためのヘルパー
void reroot(int rootnode){
assert(isDFS); // DFSされていないなら実行してはダメ
                  // rootnodeからDSFする。この際、rootには零元が送られてきたとみなす。
// = rootの子(2段目)には、rootの親からの情報などなかったことにする
rerootCoroutine(rootnode, e());
}

// rerooting本体
void rerootCoroutine(const int curnode, const S &costFromParent){
                                                                // 自分の親を知る
auto parentNode = parent.at(curnode);

// まず、ここで自分の子供のコストを保存しておく(参照ではなく値渡し)
      // 値渡ししておかないと、子を更新した後、他の子を更新する際、予期せぬ値になる。
// datとresをわければ、値渡しは不要になる
vector<pair<int, S>> childList; // childListはpair で first, second = nextnode, 親からのコスト<S>
for(auto x: G.at(curnode)) {
// 親は拾わない。このルーチンの前に伝搬されているから
if(x.nextnode == parentNode) continue;
pair<S, ll> tmp;
tmp.first = dat.at(x.nextnode);
tmp.second = x.cost;
tmp.first.cost += x.cost;
childList.template emplace_back(x.nextnode, tmp);
}

// rerootingのための累積和的な処理用
   // Nノードの子がいたとして、各ノードにN-1ノード分の情報を伝えようとすると、O(N^2)になる
                                                  // このため、累積和的な考え方をO(N)で事前計算しておき、O(N)で伝搬することでO(N)で伝搬できる。
// 持たせ方は次の通り
   //    0    1   2   3   4   5
                              // L: e   0-0 0-1 0-2 0-3 0-4
                                                        // R:1-5  2-5 3-5 4-5 5-5  e
                                                                                   // e: 零元(opしても値が変わらない)
                                                                                         // a-bはaからbのnodeを"+"したもの(opではない)
int childNum = childList.size();
//cout << "childnum:" << childNum << "\n";
vector<S> cumListFromL = vector<S>(childNum, e());
vector<S> cumListFromR = vector<S>(childNum, e());
REP(i, childNum - 1){ // childNumまで回す。これが、Nまでじゃないのは、上記のように"x"の場所があるから
//cout << " rerootCoroutine: cumcalc" << childList[i].first << "\n";
cumListFromL[i+1]            = op(cumListFromL[i+1], childList[i].second.first, 0);
cumListFromR[childNum-1-i-1] = op(cumListFromR[childNum-1-i-1], childList[i].second.first, 0);
}

// 各子のRerootを行う
REP(i, childNum){ // i番目の子ノードを処理する
auto childNode = childList[i].first;
//cout << "curnode:" << curnode << " update childNum: " << childNode << "\n";
//cout << "L" << cumListFromL[i].cost << "," << cumListFromL[i].nodenum << "\n";
//cout << "R" << cumListFromR[i].cost << "," << cumListFromR[i].nodenum << "\n";
// 子に伝搬する情報を作る。まず、渡す情報は、このノードの初期値だとする
S costToChild = initNodeValue();
// 子に渡す情報に、親からの情報をopで足す (=親から今のノードにたどり着いた)
costToChild = op(costToChild, costFromParent, 0);
// 子に渡す情報に、左側からの情報をopで足す (=左からノードにたどり着いた)
costToChild = op(costToChild, cumListFromL[i], 0);
// 子に渡す情報に、右側からの情報をopで足す (=右からノードにたどり着いた)
costToChild = op(costToChild, cumListFromR[i], 0);
// 子に情報を伝搬する with road cost

costToChild.cost += childList[i].second.second;

dat.at(childNode) = op(dat.at(childNode), costToChild, 0);
// さらにその子の下を掘る。この際に、このノードに伝えた情報を渡す
rerootCoroutine(childNode, costToChild);
}
}
};


// ノードが持つ情報
struct node{
    ll cost;
ll kankoCost;
// + operatorは必要で、これはrerootの時の累積和に必要
                  // opはnodenumを足すが、これは足さない
node operator+(const node &r){
return node{cost + r.cost, kankoCost};
}
};

// ノードの零元。これがないと、rerootの時の累積和ができない
auto e = []{ return node{0,  0}; };

// ノードの初期値。
auto initVal = []{ return node{0,  0}; };

// ノードのマージ
auto op = [](const node x, const node y, const ll roadCost){
return node{max(x.cost, y.cost + roadCost) , // cost
x.kankoCost}; // nodenum
};

void abc220_f(void){
int n; cin >> n;
rerooting<node, op, e, initVal> rr(n);
int s, t, w;
REP(i, n-1){
    cin >> s >> t >> w;
s--; t--;
rr.make_edge(s, t, w);
}
ll kankocost;
REP(i, n){
    cin >> kankocost;
rr.dat.at(i).kankoCost = kankocost;
rr.dat.at(i).cost = kankocost;
}
rr.dfs(0);
rr.reroot(0);
REP(i, rr.n){
    cout << rr.dat.at(i).cost << "\n";
}
}


using namespace std;
int main() {
FASTIOpre();
abc220_f();
}