#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <cassert>
#include <random>
#include <sstream>
#include <stack>
#include <queue>
#include <string.h>
using namespace std;
using ll = long long int;

constexpr const double timelimit = 1.98 * 1000 * 1000;

constexpr const int dh[4] = {-1, 0, 0,1};
constexpr const int dw[4] = {0, -1, 1, 0};
constexpr const int dlen = 4;
constexpr const int MAXN = 30;

std::mt19937 mt_for_action(0);

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)


template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }

clock_t startclk;

struct score_result{
    ll realscore;
    ll evalscore;
};



struct actionpoint{
    int h1, w1, h2, w2;
public:
    std::string toString() const {
        std::stringstream ss;
        ss << h1 << " " << w1 << " " << h2 << " " << w2;
        return ss.str();
    }
};


class MazeState {
private:
    int N, K, P;


public:
    int turn_ = 0;
    int turnlimit_ = -1;
    score_result curScore = {0, 0};
    actionpoint causeAction = actionpoint{-1, -1, -1, -1};
    MazeState *causeMaseState = 0;
    vector<actionpoint> history_;
    int maze_[MAXN*MAXN];

    MazeState() {
        cerr << "new constractor" << endl;
    };

    MazeState(int *maze, int Narg, int Karg, int Parg) {
        N = Narg;
        K = Karg;
        P = Parg;
        //maze_ = (int*)malloc(sizeof(int) * N * N);
        turnlimit_ = 2*N*N*N;
        turn_ = 0;
        REP(h, N) {
            REP(w, N) {
                maze_[h * N + w] = maze[h * N + w];
            }
        }
    }

    void evaluateScore() { /* スコアを計算する */
        int visited_[N*N];

        unordered_map<int, int> cnt;
        cnt.clear();
        REP(i, N) REP(j,N) visited_[i*N+j] = 0;
        REP(h, N) {
            REP(w, N) {
                // nativeなスコア計算 O(N^2)
                int curcolor = maze_[h*N+w]; // wall deny
                //cerr << "NEW " << h << " " << w << "col=" << curcolor << endl;
                if(maze_[h*N+w] == 0) continue;
                if(visited_[h*N+w] == 1) continue;
                visited_[h*N+w] = 1;
                int cursize = 1; // this graph size
                stack<pair<int, int>> q;
                q.push({h, w});
                while (q.size() > 0) {
                    auto [curh, curw] = q.top();
                    //cerr << " step " << curh << " " << curw << endl;
                    q.pop();
                    REP(di, dlen) {
                        int nxth = curh + dh[di];
                        int nxtw = curw + dw[di];
                        if (!(0 <= nxth && nxth < N)) continue; // wall
                        if (!(0 <= nxtw && nxtw < N)) continue; // wall
                        if (visited_[nxth*N+nxtw] == 1) continue; // alredry ?
                        if (maze_[nxth*N+nxtw] == 0) continue; // color ?
                        if (maze_[nxth*N+nxtw] != curcolor) continue; // color ?
                        visited_[nxth*N+nxtw] = 1; // mark visit
                        q.push({nxth, nxtw});
                        ++cursize;
                    }
                }
                ++cnt[cursize];
                //if(cursize == K) cerr << "!" << h <<"," << w << endl;
            }
        }

        curScore.realscore = (cnt[K] * P) - turn_;
        //cerr << "comp" << cnt[K] << endl;
        curScore.evalscore = 0;
        curScore.evalscore = (cnt[K] * P) - turn_;
        for(auto k: cnt){
            curScore.evalscore -= - (double) k.second * abs(K-k.first); // /P ;
        }
        //curScore.evalscore -= turn_;
        //curScore.evalscore = curScore.realscore;
        //cerr << "kcnt=" << cnt[K] << endl;
        //cerr << "Turn:" << turn_ << " Score:" << curScore.realscore << "evalScore" << curScore.evalscore << endl;
    }


    bool isDone() { // 規定ターンと同様になってしまったならDone
        return turnlimit_ <= turn_;
    }


    bool isValiadAction(actionpoint ap) const {
        //if( (ap.h1 != ap.h2) || (ap.w1 != ap.w2) ) return false;
        if(!(0 <= ap.h1 && ap.h1 < N && 0 <= ap.w1 && ap.w1 < N)) return false; // valid
        if(!(0 <= ap.h2 && ap.h2 < N && 0 <= ap.w2 && ap.w2 < N)) return false; // valid
        if(maze_[ap.h1*N+ap.w1] == maze_[ap.h2*N+ap.w2]) return false; // same color?
        if(maze_[ap.h1*N+ap.w1] == 0) return false; // is wall?
        if(maze_[ap.h2*N+ap.w2] == 0) return false; // is wall?
        //cerr << "permit: " << ap.toString() << endl;
        return true;
    }

    vector<actionpoint> validActions() const{
        int trycount = 100;
        int maxcandidate = 8;
        int findcandidate = 0;
        vector<actionpoint> candidate = {};
        while(trycount--){
            if(maxcandidate <= findcandidate) break;
            int h1 = (int)mt_for_action() % N;
            int w1 = (int)mt_for_action() % N;
            int h2 = h1;
            int w2 = w1;
            if((int)mt_for_action() % 2 == 0) ++w2;
            else ++h2;
            actionpoint ap = {h1, w1, h2, w2};
            if(isValiadAction(ap)) {
                ++findcandidate;
                candidate.emplace_back(ap);
            }
        }
        return candidate;
    }

    void advance(const actionpoint ap){ // ターンを進める
        ++turn_;
        //assert(isValiadAction(ap));
        //cerr << "Action Turn:" << turn_ << " (" << ap.h1 << "," << ap.w1 << ") <-> (" << ap.h2 << "," << ap.w2 << ")" << endl;
        swap(maze_[ap.h1 * N + ap.w1], maze_[ap.h2*N+ap.w2]);
    }
    void advance2(const actionpoint ap){ // ターンを進める
        //assert(isValiadAction(ap));
        swap(maze_[ap.h2 * N + ap.w2], maze_[ap.h1 * N + ap.w1]);
    }


    std::string toString() const {
        std::stringstream ss;
        ss << "Map:" << endl;
        REP(h, N){
            REP(w, N){
                ss << maze_[h*N+w];
            }
            ss << endl;
        }
        return ss.str();
    }
};

bool operator<(const score_result &score_1, const score_result &score_2)
{
    return score_1.evalscore < score_2.evalscore;
}

bool operator<(const MazeState &maze1, const MazeState &maze2){
    return maze1.curScore < maze2.curScore;
}


vector<actionpoint> beamSearchAction(const MazeState &state, const int beamWidth, const int beamDepth){
    vector<priority_queue<MazeState>> beamHistory(beamDepth + 1);
    REP(t, beamDepth + 2) beamHistory.at(t) = priority_queue<MazeState>();
    queue<actionpoint> ans;
    vector<actionpoint> finalans;
    int scoremaxind = -1; // not index. count.
    beamHistory.at(0).push(state);

    for(int t = 0; t < beamDepth; ++t){
        if((double)(::clock() - startclk) > timelimit ) break;
        for(int i = 0; i < beamWidth; ++i){
            if((double)(::clock() - startclk) > timelimit ) break;
            if(beamHistory.at(t).empty()) break;
            const auto &now_state = beamHistory.at(t).top();
            beamHistory.at(t).pop();
            auto legalActions = now_state.validActions();
            for(const auto action: legalActions){
                MazeState next_state = now_state;
                next_state.advance(action);
                next_state.evaluateScore();
                next_state.causeAction = action;
                next_state.causeMaseState = now_state;
                beamHistory.at(t + 1).push(next_state);
                scoremaxind = t+1;
            }
        }
    }
    cerr << "!2" << endl;

    /* 復元 */
    assert(beamHistory.at(scoremaxind).size() > 0);
    auto lastState = beamHistory.at(scoremaxind).top();
    MazeState *cur;
    cur = lastState.causeMaseState;
    while(cur != 0){
        cerr << "Turn: " << cur->turn_ << " Score:" << cur->curScore.realscore << endl;
        ans.push(cur->causeAction);
        cur = cur->causeMaseState;
    }
    while(ans.size() > 0){
        finalans.push_back(ans.back());
        finalans.pop_back();
    }
    return finalans;

}

void solve(){
    int N, C, K, P;
    cin >> N >> C >> K >> P;
    int initmaze[N*N];
    //memset(initmaze, 0, sizeof(int)*N*N);
    REP(h, N){
        REP(w, N){
            cin >> initmaze[h*N+w];
        }
        cerr<< endl;
    }

    auto curmap = MazeState(initmaze, N, K, P);
    curmap.evaluateScore();

    vector<int> ansscore;
    auto ans = beamSearchAction(curmap, 1, 20);
    cerr << "proced" << endl;
    cerr << ans.size() << endl;
    cout << ans.size() << endl;
    for(auto e: ans){
        cerr << e.toString() << endl;
        cout << e.toString() << endl;
    }
}

int main() {
    startclk = clock();
    solve();
}
