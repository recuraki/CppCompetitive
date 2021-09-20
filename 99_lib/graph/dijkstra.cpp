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

#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)
#define FASTIOpre() cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);

// chmax/min: if update a then true
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define ceil(a,b) (((a) + ((b) - 1)) / (b))



/*
 * ダイクストラでコストを求める。
 * 未到達はINF
 * parentは s および 未到達が -1
 * findRouteはその前に実行したsolveの結果をもとに経路を返す
 * TODO: 現状、vectorにしているが、これはlistで返した方が早い(reverse分)
 */
template<typename T>
class dijkstra{
public:
    struct edge{
        T cost;
        int nextnode;
    };

    const T INF = numeric_limits< T >::max();
    T mod = 1e9 + 7;

    vector<T> cost;
    using weight = pair<T, int>; // cost, nextNode = use edge and pq
    vector<vector<edge>> graph;
    vector<int> parent;
    vector<int> pathnum;
    int nodeNum;
    int lastSource;

    dijkstra(int nodeNum){
        this->graph.resize(nodeNum);
        this->nodeNum = nodeNum;
        this->lastSource = -1;
    }
    void makeEdge(int curnode, int nextnode, T cost){
        assert(curnode < this->nodeNum);
        assert(nextnode < this->nodeNum);
        this->graph.at(curnode).emplace_back((edge){cost, nextnode});
    }
    void solve(int nodeS, int nodeT){
        priority_queue<weight , vector<weight>, greater<weight>> q;
        T curCost, nextCost;
        int curNode;
        this->cost = vector<T>(nodeNum, INF);
        this->parent = vector<int>(nodeNum, -1);
        this->pathnum = vector<int>(nodeNum, 0);
        this->pathnum.at(nodeS) = 1;
        this->cost.at(nodeS) = 0;
        q.emplace(0, nodeS);
        // q = {cost, nextnode}
        this->lastSource = nodeS;
        while(q.size() > 0){
            tie(curCost, curNode) = q.top(); q.pop();
            // more fast, if you need ONLY cost of nodeT
            // if(curNode == nodeT) return;
            if(curCost > cost[curNode]) continue;
            for( edge &e: graph.at(curNode) ){
                nextCost = curCost + e.cost;
                if(cost.at(e.nextnode) == nextCost) {
                    this->pathnum[e.nextnode] += this->pathnum[curNode];
                    this->pathnum[e.nextnode] %= this->mod;
                };
                if(cost.at(e.nextnode) <= nextCost) continue;
                cost.at(e.nextnode) = nextCost;
                parent.at(e.nextnode) = curNode;
                this->pathnum[e.nextnode] = this->pathnum[curNode];
                q.emplace( nextCost, e.nextnode );
            }
        }
    }

    vector<int> findRoute(int NodeS, int NodeT){
        // todo: reverse is loose. it should be use list or deque
        assert(lastSource == NodeS);
        vector<int> res;
        auto nextnode = NodeT;
        while(nextnode != -1){
            res.emplace_back(nextnode);
            nextnode = parent.at(nextnode);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

void test(){
    dijkstra<int> dj(4);
    dj.makeEdge(0,1,10);
    dj.makeEdge(0,2,4);
    dj.makeEdge(1,2,2);
    dj.makeEdge(2,3,1);
    dj.makeEdge(1,3,5);
    dj.solve(0, 0);
    cout << "costs: ";
    REP(i, 4) cout << dj.cost.at(i) << " ";
    cout << "\n";
    cout << "parent: ";
    REP(i, 4) cout << dj.parent.at(i) << " ";
    cout << "\n";
    auto route = dj.findRoute(0, 3);
    cout << "route: ";
    for(auto &x: route) cout << x << " ";
    cout << "\n";
}

// 標準
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=jp
void GRL_1_A(){
    int v, e, r; cin>>v>>e>>r;
    int s, t, d;
    dijkstra<int> dj(v);
    REP(i, e){
        cin >>s>>t>>d;
        dj.makeEdge(s, t, d);
    }
    dj.solve(r, r);
    REP(i, v){
        if(dj.cost.at(i) == dj.INF) cout << "INF" << "\n";
        else cout << dj.cost.at(i) << "\n";
    }
}

// pathnum用
// https://atcoder.jp/contests/abc211/tasks/abc211_d
void abc211_d(){
    int n, m; cin >>n>>m;
    ll a,b;
    dijkstra<ll> dj(n);
    REP(i, m){
        cin >> a>>b; --a; --b;
        dj.makeEdge(a, b ,1);
        dj.makeEdge(b, a ,1);
    }
    dj.solve(0, 0);
    cout << dj.pathnum.at(n-1) << "\n";
}

// https://atcoder.jp/contests/abc214/tasks/abc214_c
// 214_c: ダイクストラ解法
void abc214_c(){
    int n; cin >> n;
    dijkstra<ll> dj(n+1);
    vector<ll> dats(n), datt(n);
    REP(i, n) cin >> dats.at(i);
    REP(i, n) cin >> datt.at(i);
    REP(i, n) dj.makeEdge(i%n, (i+1)%n, dats.at(i));
    REP(i, n) dj.makeEdge(n, i, datt.at(i));
    dj.solve(n,n);
    REP(i, n) cout << dj.cost.at(i) << "\n";
}


using namespace std;
int main() {
    FASTIOpre();
    //test();
    //GRL_1_A();
    //abc211_d();
    abc214_c();
}
