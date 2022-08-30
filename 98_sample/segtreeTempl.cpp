#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long int;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)


using ll = long long;

// 乗せる型と、opと、単位元e。
// eはlambdaで書くことに注意
struct typetako{ long double a,b; };
auto optako = [](typetako x, typetako y){ return typetako{x.a * y.a, x.b * y.a + y.b }; };
auto etako = []{ return typetako{1, 0}; };

long long opgcd(long long a, long long b) { return gcd(a, b); }
long long egcd() { return 0; }

long long opadd(long long a, long long b) { return a + b; }
long long eadd() { return (long long)0; }

/*
 * https://betrue12.hateblo.jp/entry/2020/09/22/194541 をみる。
 * segtree lazyについて
 * lazy_segtree<S, op, e, F, mapping, composition, id>について、
 *  S: valの形:
 *  F: LAZYの型:
 *  S op(S a, S b): aとbに対する演算。は子ノードa,bを足すときの処理としていい
 *    単なるaddのa, bならa + bでいいが、区間和などを持たせたい場合は、
 *    {a, cnta} + {b, cntb}としていい
 *  S e: 単位元 単純に初期値(単位元)と考えていい。0, 1, INF, -INF
 *  S mapping(F f, S x):上位のlazyを1つ子のvalに伝搬させる演算
 *   ここでの
 *  F composition(F f, F g) 上位のlazyを1つ子のlazyに伝える。
 *   これは、既にある子のgにfを演算するのがポイント。
 *   例えば、区間setの場合は、return f(既にgが合ってもfで上書きしていいから)
 *  F id():
 *   lazyの初期値。として捉えてよい。つまり、「存在しない数」。
 *   lazyを下にmappingで伝搬させても、「valを変更しないよう」なF。言わば、零元。
 *   ここは定義によって変わり、難しい。
 *    区間maxなどの場合、-INFを淹れておけばいい。これは取られない値であり、零元である。
 *    区間加算の場合箱となる。まず"0"という加算の零元は値として入りうるので、ID=0にはできない。
 *      mappingは下の値を更新するので初期値は0にしたいものの、「取られない値」の条件を満たさない。
 *      そこで、(競プロの範囲では) a_iとして取られない適当な数(INFでも-INFでもいい)を選ぶ。
 *      そして、mapping/compositionの際にはその値かどうかで処理を分ける。
 *
 *
 *
 * set(ind, x): [ind]にxを淹れる
 * get(ind, x): [ind]の値を得る
 * prod(l, r): [l, r) の区間のopを得る
 * all_prod(): prod(0, n)と同じ
 *
 * apply(): 区間に演算を反映する
 *  1: apply(ind, func): indの値を func(a[ind])する。
 *  2: apply(l, r func): [l, r)の区間のindをfunc(a[ind])する
 *
 *  max_right:
 *  int min_left<G>():
 *
 *  例: https://qiita.com/recuraki/items/57b9f539511ef0876a5f#%E8%A7%A3%E6%B3%952-%E3%82%BB%E3%82%B0%E3%83%A1%E3%83%B3%E3%83%88%E3%83%84%E3%83%AA%E3%83%BC%E3%82%84bit%E4%B8%8A%E3%81%A7%E3%81%AE%EF%BC%92%E5%88%86%E6%8E%A2%E7%B4%A2acl%E3%81%AE%E7%B7%B4%E7%BF%92
 *      atcoder::segtree::max_right<f>(l)を使います。ドキュメントの通り、fを満たす最大のindexの+1を返します。
 *
 */
long long opaddlazy(long long a, long long b) {return a+b;}


int main(){
    segtree<typetako, optako, etako> sttako(100);
    segtree<long long, opgcd, egcd> stgcd(100);
    segtree<long long, opadd, eadd> stadd(100);


}