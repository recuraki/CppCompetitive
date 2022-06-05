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
 *   lazyの初期値。として捉えてよい。
 *   lazyを下にmappingで伝搬させても、valを変更しないようなF。
 *   ここは定義によって変わる。
 *    区間加算の場合、mappingは下野の値を更新するので
 *
 *
 *
 * set(ind, x): [ind]にxを淹れる
 * get(ind, x): [ind]の値を得る
 * prod(l, r): [l, r) の区間のopを得る
 * all_prod(): prod(0, n)と同じ
 * apply(): 区間に演算を反映する
 *  1: apply(ind, func): indの値を func(a[ind])する。
 *  2: apply(l, r func): [l, r)の区間のindをfunc(a[ind])する
 *
 *  max_right:
 *  int min_left<G>():
 */
long long opaddlazy(long long a, long long b) {return a+b;}


int main(){
    segtree<typetako, optako, etako> sttako(100);
    segtree<long long, opgcd, egcd> stgcd(100);
    segtree<long long, opadd, eadd> stadd(100);


}