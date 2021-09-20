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

    int s, t;
    cin >> s>> t;
    int res = 0;
    REP(a, 101){
        REP(b, 101){
            REP(c, 101){
                if(a+b+c > s) continue;
                if(a*b*c > t) continue;
                ++res;

            }
        }
    }
    cout << res << "\n";
    return 0;
}