/*
 * ジグザグ マトリックス
 * 1 2 3
 * 4 5 6
 * 7 8 9
 * という配列があり、要素を持ちながら、2x2で全探索をしたいとする。この時、
 * in = [1,2,4,5] out=[]
 * in = [3,6] , out[1,4]
 * in = [8,9] , out[2,3]
 * in = [4,7] , out[6,9]
 * in = [], out = [4,5,7,8]
 * というように、in, outが最小になるように遷移するような動きをしてあげたい。
 */
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
using ll = long long;

template <class T> struct zigzagMatrix{
public:
    vector<vector<T>>* maze;
    int mazeh, mazew;
    int windoww, windowh;
    int movew, moveh, maxturn; // ウィンドウが動けるサイズ
    void load(vector<vector<T>> &maze, int windowh, int windoww){
        this->maze = &maze;
        this->mazeh = maze.size();
        this->mazew = maze.at(0).size();
        this->windowh = windowh;
        this->windoww = windoww;
        this->movew = this->mazew - this->windoww + 1;
        this->moveh = this->mazeh - this->windowh + 1;
        this->maxturn = this->moveh * this->movew;
        // 全ての幅が等しいかを判定
        REP(i, maze.size()) assert(this->mazew == maze.at(i).size());
    }

    void move(int turn, vector<T> &in, vector<T> &out){
        in.clear(); out.clear();
        int h, w;
        // 定義されないターンなら飛ばす
        if(turn >= this->maxturn){ return; }
        // スタートの処理
        if(turn == 0) {
            REP(i, this->windowh){
                REP(j, this->windoww){
                    in.template emplace_back(this->maze->at(i).at(j));
                }
            }
            return;
        }
        // ウィンドウの(h, w)の計算
        h = turn / this->movew;
        if(h%2 == 0)  w = turn % this->movew;
        else w = this->movew - 1 - (turn % this->movew);
        // cout << "turn: "<< turn << "=" << h << "," << w << "\n";


        if(h % 2 == 0){ // 順方向の処理
            if(w == 0){ // 縦移動
                REP(i, windoww){
                    in.emplace_back(this->maze->at(h + this->windowh - 1).at(w + i));
                    out.emplace_back(this->maze->at(h-1).at(w+i));
                }
            } else { // 横移動
                REP(i, windowh){
                    out.emplace_back(this->maze->at(h + i).at(w - 1));
                    in.emplace_back(this->maze->at(h + i).at(w + this->windoww - 1));
                }
            }
        } else { // 逆方向の処理
            if(w == (this->movew - 1)){ // 縦移動
                REP(i, windoww){
                    in.emplace_back(this->maze->at(h + this->windowh - 1).at(w + i));
                    out.emplace_back(this->maze->at(h-1).at(w+i));
                }
            } else {  // 横移動
                REP(i, windowh){
                    in.emplace_back(this->maze->at(h + i).at(w));
                    out.emplace_back(this->maze->at(h + i).at(w + this->windoww));
                }
            }
        }
    }


    void dumpmaze(){
        REP(i, this->mazeh){
            REP(j, this->mazew){
                cout << this->maze->at(i).at(j) << " ";
            }
            cout << "\n";
        }
    }
};

int main(){
    vector<vector<int>> maze = {
            {1,2,3, 4},
            {5,6,7, 8},
            {9,10,11,12},
            {13,14,15,16}
    };
    vector<int> in, out;
    zigzagMatrix<int> zz;
    zz.load(maze, 2, 2);
    zz.dumpmaze();
    REP(i, 10){
        cout << "\n";
        zz.move(i, in, out);
        cout << ">in: ";
        for(auto x: in) cout << x << " ";
        cout << "\n";
        cout << " > out: ";
        for(auto x: out) cout << x << " ";
        cout << "\n";
    }

}