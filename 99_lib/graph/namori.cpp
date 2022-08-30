//
// Created by kanai on 2022/08/30.
//
#include <bits/stdc++.h>
//#include <chrono>
#include <atcoder/all>
using namespace std;
using ll = long long int;
#define FASTIOpre() cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

// https://ei1333.github.io/algorithm/namori.html
/*
 * なもりグラフ
 * N頂点 N辺の無向グラフは１つの閉路を含むグラフである。
 * これを閉路とそれ以外に分解する
 *
 */
struct Namori{
    int n;
    int alledgenum;
    bool solved;
    vector<vector<int>> g;
    vector<int> edgecnt;
    vector<bool> isLoop;

    Namori(int n) : n(n) {
        g = vector<vector<int>>(n, vector<int>());
        edgecnt = vector<int>(n);
        isLoop(n, true);
        alledgenum = 0;
        solved = false;
    }

    void makeEdge2Way(const int &u, const int &v){
        // u <-> v でedgeを張る
        assert(u != v);
        g.at(u).push_back(v);
        g.at(v).push_back(u);
        ++alledgenum;
        ++edgecnt.at(u); ++edgecnt.at(v);
    }

    void solve(){
        assert(solved == false); // 多重solve防止
        solved = true;
        vector<int> q;
        vector<bool> visited(n);
        REP(cur, n){ // 木の始めだけひっかける
            if(edgecnt.at(cur) != 1) continue;
            q.push_back(cur);
        }


    }


};

