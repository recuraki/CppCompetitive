#include <bits/stdc++.h>
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define REP(i, n) FOR(i,0,n)
using namespace std;
int main(){
    struct st{ int a, b, c; };
    vector<st> dat;
    vector<int> inputa = {1, 3, 5, 5, 5, 5, 9};
    vector<int> inputb = {1, 3, 6, 5, 5, 4, 9};
    vector<int> inputc = {1, 3, 9, 5, 10, 10, 9};
    st x;
    REP(i, inputa.size()){
        x.a = inputa[i];
        x.b = inputb[i];
        x.c = inputc[i];
        dat.emplace_back(x);
    }
    sort(dat.begin(), dat.end(),
         [](st const &l, st const &r){
             if(l.a != r.a) return l.a > r.a; // DESC Greater
             if(l.b != r.b) return l.b < r.b; // ASC less
                            return l.c > r.c; // DESC
            });

    for(auto x: dat){
        cout <<" >" << ":" << x.a << "," << x.b << "," << x.c << "\n";
    }
    /*
         >:9,9,9
         >:5,4,10
         >:5,5,10
         >:5,5,5
         >:5,6,9
         >:3,3,3
         >:1,1,1
     */
}