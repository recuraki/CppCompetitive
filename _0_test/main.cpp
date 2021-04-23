#include <bits/stdc++.h>
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// #include <atcoder/all>
using namespace std;
using namespace __gnu_pbds;
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <ctime>
#include <cstring>
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define rer(i,l,u) for(int (i)=(int)(l);(i)<=(int)(u);++(i))
#define reu(i,l,u) for(int (i)=(int)(l);(i)<(int)(u);++(i))
#define reps(i,n,s) for(int (i)=0;(i)<(int)(n);(i)+=(s))
#define reus(i,l,u,s) for(int (i)=(int)(l);(i)<(int)(u);(i)+=(s))
#if defined(_MSC_VER)
#define aut(r,v) auto r = (v)
#else
#define aut(r,v) typeof(v) r = (v)
#endif
#define each(it,o) for(aut(it, (o).begin()); it != (o).end(); ++ it)
#define all(o) (o).begin(), (o).end()
#define mset(m,v) memset(m,v,sizeof(m))
#define INF 0x3f3f3f3f
#define INFL 0x3f3f3f3f3f3f3f3fLL
#define EPS 1e-9
using namespace std;
typedef vector<int> vi; typedef pair<int,int> pii; typedef vector<pair<int,int> > vpii;
typedef long long ll; typedef vector<long long> vl; typedef pair<long long,long long> pll; typedef vector<pair<long long,long long> > vpll;
typedef vector<string> vs; typedef long double ld;


#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
#define SZ(x) ((int)(x).size())
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <cassert>
using namespace std;

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <cassert>
using namespace std;

typedef unsigned int u32;
inline int popcount(u32 x) {
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    return ((x + (x >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
}
//(k+1)番目の1の立っている位置(最下位から)を返す
//http://graphics.stanford.edu/~seander/bithacks.html#SelectPosFromMSBRank を参考にした
inline int select32(u32 x, int k) {
    u32 a, b, c; int t, s;
    a = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    b = (a & 0x33333333) + ((a >> 2) & 0x33333333);
    c = (b & 0x0f0f0f0f) + ((b >> 4) & 0x0f0f0f0f);
    t = (c & 0xff) + ((c >> 8) & 0xff);
    s = 0;
    s += ((t - k - 1) & 128) >> 3; k -= t & ((t - k - 1) >> 8); //if(k >= t) s += 16, k -= t;
    t = (c >> s) & 0xf;
    s += ((t - k - 1) & 128) >> 4; k -= t & ((t - k - 1) >> 8); //if(k >= t) s += 8, k -= t;
    t = (b >> s) & 0x7;
    s += ((t - k - 1) & 128) >> 5; k -= t & ((t - k - 1) >> 8); //if(k >= t) s += 4, k -= t;
    t = (a >> s) & 0x3;
    s += ((t - k - 1) & 128) >> 6; k -= t & ((t - k - 1) >> 8); //if(k >= t) s += 2, k -= t;
    t = (x >> s) & 0x1;
    s += ((t - k - 1) & 128) >> 7; //if(k >= t) s += 1;
    return s;
}
//※静的なデータ構造
//constructした後setを何回か呼び、その後buildを呼んだ後にrank,selectが行える
struct FullyIndexableDictionary {
    static const int NOTFOUND = -1;
    static const int SELECTT_INTERVAL = 32;	//SELECTT_INTERVAL >= 32
    int length, blockslength, count;
    vector<u32> blocks; vector<int> ranktable, selecttable0, selecttable1;
    FullyIndexableDictionary(int len): length(len) {
        blocks.resize((blockslength = (len + 31) / 32) + 1);
    }
    inline void set(int i) { blocks[i / 32] |= 1 << i % 32; }
    void build() {
        if(length == 0) { count = 0; return; }
        ranktable.assign(blockslength + 1, 0);
        selecttable0.clear(); selecttable1.clear();
        int prev0 = 0, prev1 = 0, count0 = 0, count1 = 0;
        for(int i = 0; i < blockslength; i ++) {
            ranktable[i] = count1;
            count1 += popcount(blocks[i]);
            count0 = 32 * (i + 1) - count1;
            if(prev1 < (count1+SELECTT_INTERVAL-1) / SELECTT_INTERVAL)
                selecttable1.push_back(i), prev1 = (count1+SELECTT_INTERVAL-1) / SELECTT_INTERVAL;
            if(prev0 < (count0+SELECTT_INTERVAL-1) / SELECTT_INTERVAL)
                selecttable0.push_back(i), prev0 = (count0+SELECTT_INTERVAL-1) / SELECTT_INTERVAL;
        }
        ranktable[blockslength] = count1;
        selecttable1.push_back(blockslength-1);
        selecttable0.push_back(blockslength-1);
        count = count1;
    }
    inline bool access(int pos) const {
        return blocks[pos / 32] >> pos % 32 & 1;
    }
    inline int rank(int pos) const {	//[0..pos)の1の個数
        int block_idx = pos / 32;
        return ranktable[block_idx] + popcount(blocks[block_idx] & (1U << pos % 32)-1);
    }
    inline int rank(bool b, int pos) const { return b ? rank(pos) : pos - rank(pos); }
    inline int rank(bool b, int left, int right) const { return rank(b, right) - rank(b, left); }
    //O(log n)は重いよねえ。expect O(1) (たぶん) ならできるけど最悪ケースがなあ
    //あるいはメモリ4*32*n bytes でO(1)でもできるけど…ハッシュテーブルでうまくやればうまくできるか？
    template<bool b>
    int select(int k) const {	//(k+1)番目のbの位置
        if((b ? count : length - count) <= k) return NOTFOUND;
        int selecttable_index = k / SELECTT_INTERVAL;
        int l = (b ? selecttable1 : selecttable0)[selecttable_index],
                u = (b ? selecttable1 : selecttable0)[selecttable_index + 1] + 1;	//ブロックを二分探索
        while(l + 1 < u) {
            int m = (l + u) / 2;
            ((b ? ranktable[m] : m * 32 - ranktable[m]) <= k ? l : u) = m;
        }
        return l * 32 + select32(b ? blocks[l] : ~blocks[l], k - (b ? ranktable[l] : 32 * l - ranktable[l]));
    }
    inline int select(bool b, int k) const { return b ? select<true>(k) : select<false>(k); }
    inline int select(bool b, int k, int left) const { return select(b, rank(b, left) + k); }
};

/*
	WaveletMatrix。たしかにこっちの方が「常に」使うべきな気がする
*/
inline unsigned int BITMASK(int i) {
    return (1 << i) - 1;
}
//※メモリ, 時間はだいたい支配的な部分のみ書く
//メモリ: (length * bitsize / 8) bytes
struct WaveletMatrix {
    typedef unsigned long long Val;
    static const int NOTFOUND = -1;
    static const Val UNDEFINED = Val(-1);
    static const int MAX_BITSIZE = 64;
    int length, bitsize; Val maxval;
    vector<FullyIndexableDictionary> dicts;
    vector<int> mids;
    //追加メモリ: (2 * length * sizeof Val) bytes
    //時間: bitsize * length * 大きめ
    void init(const vector<Val>& data) {
        length = data.size();
        maxval = *max_element(data.begin(), data.end());
        if(1ULL << (8 * sizeof(Val) - 1) <= maxval) bitsize = 8 * sizeof(Val);
        else for(bitsize = 0; Val(1) << bitsize <= maxval; bitsize ++) ;
        dicts.assign(bitsize, length);
        mids.assign(bitsize, 0);
        vector<Val> datacurrent(data), datanext(length);
        for(int bit = 0; bit < bitsize; bit ++) {
            int pos = 0;
            for(int i = 0; i < length; i ++)
                if((datacurrent[i] >> (bitsize - bit - 1) & 1) == 0)
                    datanext[pos ++] = datacurrent[i];
            mids[bit] = pos;
            for(int i = 0; i < length; i ++)
                if((datacurrent[i] >> (bitsize - bit - 1) & 1) != 0)
                    dicts[bit].set(i), datanext[pos ++] = datacurrent[i];
            dicts[bit].build();
            datacurrent.swap(datanext);
        }
    }
    Val access(int pos) const {
        Val val = 0;
        for(int bit = 0; bit < bitsize; bit ++) {
            bool dir = dicts[bit].access(pos);
            val = val << 1 | (dir ? 1 : 0);
            pos = dicts[bit].rank(dir, pos);
            if(dir) pos += mids[bit];
        }
        return val;
    }
    int rank(Val val, int left, int right) const {
        if(val > maxval) return 0;
        for(int bit = 0; bit < bitsize; bit ++) {
            bool dir = val >> (bitsize - bit - 1) & 1;
            left = dicts[bit].rank(dir, left), right = dicts[bit].rank(dir, right);
            if(dir) left += mids[bit], right += mids[bit];
        }
        return right - left;
    }
    int rank(Val val, int right) const { return rank(val, 0, right); }
    int rank_all(Val val, int left, int right, int& out_lt, int& out_gt) const {
        if(val > maxval) { out_lt = right - left; out_gt = 0; return 0; }
        out_lt = out_gt = 0;
        for(int bit = 0; bit < bitsize; bit ++) {
            bool dir = val >> (bitsize - bit - 1) & 1;
            int leftcount = dicts[bit].rank(dir, left), rightcount = dicts[bit].rank(dir, right);
            (dir ? out_lt : out_gt) += (right - left) - (rightcount - leftcount);
            left = leftcount, right = rightcount;
            if(dir) left += mids[bit], right += mids[bit];
        }
        return right - left;
    }
    inline int rank_lt(Val val, int left, int right) const {
        int tmp_lt, tmp_gt;
        rank_all(val, left, right, tmp_lt, tmp_gt);
        return tmp_lt;
    }
    inline int rangefreq(int left, int right, Val bottom, Val up) {
        return rank_lt(up, left, right) - rank_lt(bottom, left, right);
    }
    //O(bitsize log length) (FID::selectがlog nで最悪の場合)
    int select(Val val, int k) const {
        if(val > maxval) return NOTFOUND;
        static int lefts[MAX_BITSIZE], rights[MAX_BITSIZE];
        int left = 0, right = length;
        for(int bit = 0; bit < bitsize; bit ++) {
            lefts[bit] = left, rights[bit] = right;
            bool dir = val >> (bitsize - bit - 1) & 1;
            left = dicts[bit].rank(dir, left), right = dicts[bit].rank(dir, right);
            if(dir) left += mids[bit], right += mids[bit];
        }
        for(int bit = bitsize-1; bit >= 0; bit --) {
            k = dicts[bit].select(val >> (bitsize - bit - 1) & 1, k, lefts[bit]);
            if(k == FullyIndexableDictionary::NOTFOUND || k >= rights[bit])
                return NOTFOUND;
            k -= lefts[bit];
        }
        return k;
    }
    int select(Val val, int k, int left) const { return select(val, k + rank(val, left)); }
    void quantile(int left, int right, int k, Val& out_val, int& out_k) const {
        if(right - left <= k) { out_val = UNDEFINED; out_k = NOTFOUND; return; }
        Val val = 0;
        for(int bit = 0; bit < bitsize; bit ++) {
            int count = dicts[bit].rank(true, left, right);
            bool dir = k < count;
            val = val << 1 | (dir ? 1 : 0);
            if(!dir) k -= count;
            left = dicts[bit].rank(dir, left), right = dicts[bit].rank(dir, right);
            if(dir) left += mids[bit], right += mids[bit];
        }
        out_val = val; out_k = k;
    }
    struct IdxVal {
        int idx; Val val;
        IdxVal() {}
        IdxVal(int i, Val v): idx(i), val(v) {}
    };
    inline Val quantile(int left, int right, int k) const {
        Val tmp_val; int tmp_k;
        quantile(left, right, k, tmp_val, tmp_k);
        return tmp_val;
    }
    inline IdxVal quantile_idxval(int left, int right, int k) const {
        Val tmp_val; int tmp_k;
        quantile(left, right, k, tmp_val, tmp_k);
        return IdxVal(select(tmp_val, tmp_k, left), tmp_val);
    }
    inline Val maximum(int left, int right) const { return quantile(left, right, 0); }
    inline Val minimum(int left, int right) const { return quantile(left, right, right - left - 1); }
    //区間がかぶってるとkとかがintより大きくなるよね
    void quantile_ranges(const vector<int>& lefts0, const vector<int>& rights0, int k, Val& out_val, int& out_k) const {
        int n = lefts0.size();
        int width = 0;
        for(int i = 0; i < n; i ++) width += rights0[i] - lefts0[i];
        if(width <= k) { out_val = UNDEFINED; out_k = NOTFOUND; return; }
        static vector<int> lefts, rights;	//自動変数だとメモリ確保の時間…と思ったけどこれだとどうだろう？
        lefts.assign(lefts0.begin(), lefts0.end());
        rights.assign(rights0.begin(), rights0.end());
        Val val = 0;
        for(int bit = 0; bit < bitsize; bit ++) {
            int count = 0;
            for(int i = 0; i < n; i ++) {
                count += dicts[bit].rank(true, lefts[i], rights[i]);
            }
            bool dir = k < count;
            val = val << 1 | (dir ? 1 : 0);
            if(!dir) k -= count;
            for(int i = 0; i < n; i ++) {
                lefts[i] = dicts[bit].rank(dir, lefts[i]);
                rights[i] = dicts[bit].rank(dir, rights[i]);
                if(dir) lefts[i] += mids[bit], rights[i] += mids[bit];
            }
        }
        out_val = val; out_k = k;
    }
    //区間がかぶってるとバグる
    //区間がソートされていないとバグる
    inline IdxVal quantile_ranges_idxval(const vector<int>& lefts, const vector<int>& rights, int k) const {
        int n = lefts.size();
        Val tmp_val; int tmp_k;
        quantile_ranges(lefts, rights, k, tmp_val, tmp_k);
        for(int i = 0; i < n; i ++) {
            if(tmp_k < rights[i] - lefts[i]) {
                return IdxVal(select(tmp_val, tmp_k, lefts[i]), tmp_val);
            }
            tmp_k -= rights[i] - lefts[i];
        }
        return IdxVal(NOTFOUND, UNDEFINED);
    }
    struct Range {
        int left, right;
        int bit; Val val;
        Range(int l, int r, int b, Val v):
                left(l), right(r), bit(b), val(v) {}
    };
    //O(bitsize min(length, maxval) log min(length, maxval))?
    //priority_queueではやはり最悪ケースが…
    //でもランダムで適当(バラけすぎとかが無い)なデータに対しては結構速い
    template<typename F, typename FOut>
    int rectbfsk(const F& f, int left, int right, Val bottom, Val up, int k, FOut& out) const {
        int k0 = k;
        up = min(up, maxval+1);
        priority_queue<Range, vector<Range>, F> q(f);
        q.push(Range(left, right, 0, 0));
        while(k && !q.empty()) {
            Range t = q.top(); q.pop();
            if(t.bit == bitsize) {
                f.pushvalues(out, t, k);
            }else {
                int leftcount = dicts[t.bit].rank(false, t.left);
                int rightcount = dicts[t.bit].rank(false, t.right);
                if( rightcount - leftcount != 0 &&
                    bottom <= ((t.val << (bitsize - t.bit)) | BITMASK(bitsize - t.bit - 1)))
                    q.push(Range(leftcount, rightcount, t.bit + 1, t.val << 1));
                if( (t.right - t.left) - (rightcount - leftcount) != 0 &&
                    (((t.val << 1 | 1) << (bitsize - t.bit - 1))) < up) {
                    q.push(Range(
                            (t.left - leftcount) + mids[t.bit], (t.right - rightcount)  + mids[t.bit],
                            t.bit + 1, t.val << 1 | 1));
                }
            }
        }
        return k0 - k;
    }
    struct ValCount {
        Val val; int count;
        ValCount(Val v, int c): val(v), count(c) {}
        ValCount() {}
    };
    struct FreqList {
        inline bool operator()(const Range& x, const Range& y) const {
            return x.right - x.left < y.right - y.left ||
                   (x.right - x.left == y.right - y.left && x.val > y.val);
        }
        inline void pushvalues(vector<ValCount>& out, const Range& t, int& k) const {
            out.push_back(ValCount(t.val, t.right - t.left));
            k --;
        }
    };
    inline int topk(int left, int right, Val bottom, Val up, int k, vector<ValCount>& out) const {
        return rectbfsk<FreqList,vector<ValCount> >(FreqList(), left, right, bottom, up, k, out);
    }
    template<typename F, typename FOut>
    struct DfsInfo {
        const F& f;
        FOut& out;
        Val bottom, up;
        DfsInfo(const F& f_, FOut& o, Val b, Val u): f(f_), out(o), bottom(b), up(u) {}
    };
    //O(min(k bitsize, min(length, maxval)))?
    //minじゃなくてもう少しなめらかな関数で上界得られそうだけど…kつの中で幅に入らない分は共有されるイメージ
    //でもO(k bitsize)はやはり心強いな。k=1ならO(bitsize)となるわけだし
    template<typename F, typename FOut>
    void rectdfsk_dfs(const DfsInfo<F,FOut>& info, int bit, Val val, int left, int right, int& k) const {
        if(bit == bitsize) {
            info.f.pushvalues(info.out, val, right - left, k);
            return;
        }
        int leftcount = dicts[bit].rank(left);
        int rightcount = dicts[bit].rank(right);
        if(F::MAXF) {
            if(k > 0 && rightcount - leftcount != 0 &&

               (((val << 1 | 1) << (bitsize - bit - 1)) < info.up))
                rectdfsk_dfs<F,FOut>(info, bit+1, val << 1 | 1, leftcount + mids[bit], rightcount + mids[bit], k);
            if( k > 0 && (right - left) - (rightcount - leftcount) != 0 &&
                (info.bottom <= ((val << (bitsize - bit)) | BITMASK(bitsize - bit - 1))))
                rectdfsk_dfs<F,FOut>(info, bit+1, val << 1, left - leftcount, right - rightcount, k);
        }else {
            if( k > 0 && (right - left) - (rightcount - leftcount) != 0 &&
                (info.bottom <= ((val << (bitsize - bit)) | BITMASK(bitsize - bit - 1))))
                rectdfsk_dfs<F,FOut>(info, bit+1, val << 1, left - leftcount, right - rightcount, k);
            if(k > 0 && rightcount - leftcount != 0 &&
               (((val << 1 | 1) << (bitsize - bit - 1)) < info.up))
                rectdfsk_dfs<F,FOut>(info, bit+1, val << 1 | 1, leftcount + mids[bit], rightcount + mids[bit], k);
        }
    }
    template<bool maxf>
    struct MinMaxList {
        enum { MAXF = maxf };
        inline void pushvalues(vector<ValCount>& out, Val val, int count, int& k) const {
            out.push_back(ValCount(val, min(k, count)));
            k -= min(k, count);
        }
    };
    template<typename F, typename FOut>
    int rectdfsk(const F& f, int left, int right, Val bottom, Val up, int k, FOut& out) const {
        rectdfsk_dfs<F,FOut>(DfsInfo<F,FOut>(f, out, bottom, up), 0, 0, left, right, k);
        return k;
    }
    template<bool maxf>
    int rectminmaxk(int left, int right, Val bottom, Val up, int k, vector<ValCount>& out) const {
        return rectdfsk<MinMaxList<maxf>,vector<ValCount> >(MinMaxList<maxf>(), left, right, bottom, up, k, out);
    }
};
ostream& operator<<(ostream& o, const WaveletMatrix::IdxVal& idxval) {
    return o << "(" << idxval.idx << ": " << idxval.val << ")";
}

#include <cstdlib>
#include <ctime>
u32 xor128() {
    static u32 x = 123456789;
    static u32 y = 362436069;
    static u32 z = 521288629;
    static u32 w = 88675123;
    u32 t;

    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}
int main() {
    int n, q;
    int l, r;
    cin >>n >> q;
    vector<WaveletMatrix::Val> v(n);
    WaveletMatrix::Val x;
    REP(i,n){ cin >> x; v[i] = x;}
    WaveletMatrix w; w.init(v);
    vector<WaveletMatrix::ValCount> res;
    REP(qq, q) {
        cin >> l >> r;
        if (l==r){
            cout << 1 << "\n";
            continue;
        }
        w.topk(l-1, r, 1, 1000000, 1, res);
        if(res[0].count > (r-l+1)/2) {cout << 2 <<"\n";}
        else {cout << 1 <<"\n";}
    }
}

