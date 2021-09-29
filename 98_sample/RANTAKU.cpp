#include <bits/stdc++.h>
using namespace std;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

inline int qwq(int mod)
{
    long long x=rand(),y=rand();
    return ((x<<13)^y)%mod;
}

struct point{int x, y;};
inline int f(point &xx, point &yy){
    return  min( abs(xx.x - yy.x) , abs(xx.y - yy.y) );
}

int main(){
    int n; cin >> n;
    vector<point> dat;
    int a, b;
    REP(i, n) {
        cin >> a>>b;
        //cout << i << ":" << a << "," << b << "\n";
        dat.emplace_back(point{a, b});
    }
    REP(i, n){
        //cout << i << ":" << dat[i].x << "," << dat[i].y << "\n";
    }

    double st=clock();
    int p1, p2, p3, p4;
    //cout << qwq(n) << qwq(n) << "\n";
    p1 = (qwq(n));
    p2 = (qwq(n));
    auto base = f(dat[p1], dat[p2]);
    int c = -1;
    while((clock()-st)/CLOCKS_PER_SEC<=1.8) {
        p3 = (qwq(n));
        p4 = (qwq(n));

    }

    cout << base << "\n";


    return 0;
}