#include <bits/stdc++.h>
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

template<typename T>
class nodeCount{
public:
    struct edge{int id; T cost;};
    vector<bool> visited;
    vector<vector<edge>> graph;
    int nodeNum;
    vector<int> Count;
    vector<T> VCost;

    void addEdge(int a, int b, T cost){
        this->graph.at(a).emplace_back(edge{b, cost});
        this->graph.at(b).emplace_back(edge{a, cost});
    };

    nodeCount(int node){
        this->graph = vector<vector<edge>>(node);
        this->visited = vector<bool>(node, false);
        this->Count = vector<int>(node, 0);
        this->VCost = vector<T>(node, 0);
        this->nodeNum = node;
    }

    int dsf(int node, T cost) noexcept{
        int cnt = 1;
        this->visited.at(node) = true;
        this->VCost.at(node) = cost;
        for(edge nextNode: this->graph.at(node)){
            if(this->visited.at(nextNode.id)) continue;
            cnt += this->dsf(nextNode.id, cost + nextNode.cost);
        }
        this->Count.at(node) = cnt;
        return cnt;
    }

    void solve(int nodeS){
        this->dsf(nodeS, (T)0);
    }

    void dump(){
        cout << "Dump: (count)" << "\n";
        REP(i, this->nodeNum) cout << " " << this->Count.at(i);
        cout << "\n";
        cout << "Dump: (VCost)" << "\n";
        REP(i, this->nodeNum) cout << " " << this->VCost.at(i);
        cout << "\n";
    }

};

int main(){
    nodeCount<int> st(7);
    st.addEdge(0,1, 1);
    st.addEdge(0,4, 2);
    st.addEdge(1,2, 4);
    st.addEdge(1,3, 8);
    st.addEdge(4,5, 16);
    st.addEdge(5,6, 32);
    st.solve(0);
    // 7 3 1 1 3 2 1
    st.dump();

}

