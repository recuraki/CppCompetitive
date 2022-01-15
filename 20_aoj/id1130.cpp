#include <bits/stdc++.h>

using namespace std;
using namespace atcoder;
#define ll long long
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

void solve(){
    int h, w;
    vector<vector<char>> maze;
    vector<int> dh = {-1, 0, 0, 1};
    vector<int> dw = {0, -1, 1, 0};
    int curh, curw;
    char c;
    while(true){
        cin >> w >> h;
        if(h==0 && w==0) break;
        maze = vector<vector<char>>(h + 2, vector<char>(w + 2, '#'));
        REP(i, w) maze[0][i] = '#';
        FOR(hh, 1, h + 1){
            FOR(ww, 1, w + 1){
                cin >> c;
                if(c == '@'){
                    curh = hh;
                    curw = ww;
                    c = '.';
                }
                maze[hh][ww] = c;
            }
        }
        REP(i, w) maze[h+1][i] = '#';
        int nodenum = (w+2) * (h+2) + 2;
        int nodes = nodenum - 2;
        int nodet = nodenum - 1;
        auto hw2num = [&](int hh, int ww){ return hh * (w+2) + ww; };
        mf_graph<int> mf(nodenum);
        REP(hh, h+2){
            REP(ww, w+2){
                if(maze[hh][ww] == '#') continue;
                mf.add_edge(hw2num(hh, ww), nodet, 1);
                REP(di, dh.size()){
                    mf.add_edge(hw2num(hh, ww), hw2num(hh+dh[di], ww+dw[di]), h*w);
                }
            }
            mf.add_edge(nodes, hw2num(curh, curw), h*w);
        }
        cout << mf.flow(nodes, nodet) << "\n";
    }

}

int main(int argc, char *argv[]) {
    solve();
    return 0;
}