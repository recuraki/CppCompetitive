#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <stack>
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

template<typename T>
class diameter {
public:
    struct edge{
        T cost;
        int nextnode;
    };
    vector<vector<edge>> graph;
    int diameterSize;
    int centerNum;
    vector<int> centerNode;

    int n; /* Node Num */
    diameter(int n){
        this->n = n;
        this->graph.resize(n);
        this->diameterSize = -1;
        this->centerNum = -1;
        this->centerNode.clear();
    }

    void makeEdge2way(int curnode, int nextnode, T cost){
        this->graph.at(curnode).emplace_back((edge){1, nextnode});
        this->graph.at(nextnode).emplace_back((edge){1, curnode});
    }

    void solve(){
        int s = 0; /* 直径探索の開始ノード */
        int farestNode = 0;
        T farestCost = (T)0;
        vector<bool> visited;
        vector<T> costfroms;

        auto dfs = [&](auto && self, auto && th, int node, T cost) -> void{
            visited.at(node) = true;
            costfroms.at(node) = cost;
            if(cost > farestCost) {
                farestNode = node;
                farestCost = cost;
            }
            for(auto &nn: th->graph.at(node)){
                if(!visited[nn.nextnode]) self(self, th, nn.nextnode, cost + nn.cost);
            }
        };

        visited.clear();
        visited.resize(this->n, false);
        costfroms.clear();
        costfroms.resize(this->n);
        farestCost = -1;
        dfs(dfs, this, s, 0);

        auto step1node = farestNode; /* ノードsから一番遠いノード */
        auto step1cost = farestCost;
        cout << "farestnode from " << s << " is node " << step1node << "(cost" << step1cost << ")" << "\n";

        visited.clear();
        visited.resize(this->n, false);
        costfroms.clear();
        costfroms.resize(this->n);
        farestCost = -1;
        dfs(dfs, this, step1node, 0);
        vector<T> costfromstep1;
        copy(costfroms.begin(), costfroms.end(), back_inserter(costfromstep1));
        auto step2node = farestNode; /* ノード1から一番遠いノード */
        auto step2cost = farestCost;
        cout << "farestnode from " << step1node << " is node " << step2node << "(cost" << step2cost << ")" << "\n";


        visited.clear();
        visited.resize(this->n, false);
        costfroms.clear();
        costfroms.resize(this->n);
        farestCost = -1;
        dfs(dfs, this, step2node, 0);
        vector<T> costfromstep2;
        copy(costfroms.begin(), costfroms.end(), back_inserter(costfromstep2));



        this->diameterSize = step2cost;
        if(this->diameterSize % 2 == 0){ /* 中心は1つ */
            this->centerNum = 1;
            for(int i = 0; i < this->n; ++i){
                if(costfromstep1.at(i) == costfromstep2.at(i)) {
                    this->centerNode.push_back(i);
                    cout << "candidate" << i << "dist" << costfromstep1.at(i) << "\n";
                }
            }
            cout << "have one center " << centerNode.at(0) << "dist" << costfromstep1[centerNode.at(0)] << "\n";
            return;
        }
        /* 中心が2つ */
        this->centerNum = 2;
        for(int i = 0; i < this->n; ++i){
            if( (costfromstep1.at(i) == step2cost / 2) && (costfromstep2.at(i) == (step2cost / 2 + 1) )) {
                this->centerNode.push_back(i);
            }
            if( (costfromstep1.at(i) == (step2cost / 2 + 1)) && (costfromstep2.at(i) == (step2cost / 2) )) {
                this->centerNode.push_back(i);
            }
        }
        cout << "have 2 centers " << centerNode.at(0) << "," << centerNode.at(1) << "\n";
    }
};


int main(){
    int n, k; cin >> n >> k;
    int u, v;
    diameter<int> g(n);
    REP(i, n - 1){
        cin >> u >> v;
        u--; v--;
        g.makeEdge2way(u, v, 1);
    }
    g.solve();

    vector<bool> visited(n);
    vector<long long> costfroms(n);
    auto dfs = [&](auto&&self, int node, long long cost) -> void{
        visited.at(node) = true;
        costfroms.at(node) = cost;
        for(auto &nn: g.graph.at(node)){
            if(!visited[nn.nextnode]) self(self, nn.nextnode, cost + nn.cost);
        }
    };
    int ans = 0;
    if(g.centerNum == 1){
        dfs(dfs, g.centerNode[0], 0);
        REP(i, n){
            if(costfroms.at(i) >= k / 2) ++ans;
        }
    }
    cout << ans << "\n";

}
