#include <bits/stdc++.h>
using namespace std;

/*
 * 特定の点 あるいは 特定の区間 を除いた区間の累積opを求める演算
 * 条件: 可換、単位元が存在
 * op 演算: +, *, lcm, gcd, max, minなど
 * ie 単位元
 * maxなら-INF, minならINF, +なら0, *なら1, gcdなら1, lcmなら1
 * load: 読み込みます。O(N)
 * cumFromLTo(i): 左端からiの１つ手前までにopをします。 O(1)
 * cumFromRTo(i): 右端からiの１つ手前までにopをします。 O(1)
 * cumExcludePoint(i): i以外の点をopします。 O(1)
 * cumExcludeRange(l, r): [l,r) Close,Open を除いたすべてをopします。
 *  すなわちcumListFromL[l], cumListFromR[r - 1]です
 */
// こんな感じのテーブルを持つ
//    0   1   2   3   4   5
// L: e  0-0 0-1 0-2 0-3 0-4
// R:1-5 2-5 3-5 4-5 5-5  e
template <class T, T (*op)(T, T), T (*ie)()> struct cumOp1DExcludeRange {
public:
    vector<T> cumListFromL;
    vector<T> cumListFromR;
    int nodenum;

    void load(const vector<T> &dat) {
        nodenum = (int)dat.size();
        cumListFromL = vector<T>(nodenum, ie());
        cumListFromR = vector<T>(nodenum, ie());
        for(int i = 0; i < (nodenum - 1); ++i){
            cumListFromL[i+1]            = op(cumListFromL[i], dat[i]);
            cumListFromR[nodenum-1-i-1]  = op(cumListFromR[nodenum-1-i], dat[nodenum-1-i]);
        }
    }

    /* calc [0, index)  Close, Open*/
    T cumFromLTo(int index){ return cumListFromL[index]; }
    /* calc (index, n-1] Open, Close*/
    T cumFromRTo(int index){ return cumListFromR[index]; }
    T cumExcludePoint(int index){ return op(cumListFromL[index], cumListFromR[index]); }
    T cumExcludeRange(int l, int r){ /* [l,r) Close,Open */
        assert(l < r);
        return op(cumListFromL[l], cumListFromR[r - 1]);
    }


    void cumDump(){ /* dump cumlist*/
        cout << "cumListL" << "\n";
        for(int i = 0; i < nodenum; ++i) cout << " " << i << ":" << cumListFromL[i] << "\n";
        cout << "\n";
        cout << "cumListR" << "\n";
        for(int i = 0; i < nodenum; ++i) cout << " " << i << ":" << cumListFromR[i] << "\n";
        cout << "\n";
    }
};

auto ieSum = []()  { return 0LL; };
auto opSum = [](long long x, long long y) {return (long long)x+y;};
auto ieGcd = []()  { return 0LL; };
auto opGcd = [](long long x, long long y) {return __gcd(x,y);};


int main(){
    vector<long long> dat = {6,2,4,8,1,7,11,3,9,6};
    //vector<long long> dat = {1,1,100,1,1};
    cumOp1DExcludeRange<long long, opSum, ieSum> cumsum;
    cumsum.load(dat);
    cumsum.cumDump();
    cumOp1DExcludeRange<long long, opGcd, ieGcd> cumgcd;
    cumgcd.load(dat);
    cumgcd.cumDump();

    vector<long long> dat2 = {24,6,9,7,12,12,48};
    cumOp1DExcludeRange<long long, opGcd, ieGcd> cumgcd2;
    cumgcd2.load(dat2);
    cout << cumgcd2.cumFromLTo(1) << "\n"; /* 24 */
    cout << cumgcd2.cumFromRTo(5) << "\n"; /* 48 */
    cout << cumgcd2.cumExcludePoint(3) << "\n"; /* 3 */
    cout << cumgcd2.cumExcludeRange(1, 5+1) << "\n"; /* 24 */
    cout << cumgcd2.cumExcludeRange(1, 3+1) << "\n"; /* 12 */
    return 0;
}
