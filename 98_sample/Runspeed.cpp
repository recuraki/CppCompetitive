#include <bits/stdc++.h>
using namespace std;
int dat[10000][10000], dat2[10000][10000];
#define CLK std::chrono::system_clock::now()
int main(){
    int i,j;

    /* 連続アクセス1232ms */
    auto start = CLK;
    for(i = 1; i < 10000; ++i) for(j = 1; j < 10000; ++j) dat[i][j] = dat[i-1][j-1] + i+j;
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(CLK-start).count() << "ms"<< "\n";

    /* 飛んでる空間へのアクセス 2660ms*/
    start = CLK;
    for(i = 1; i < 10000; ++i) for(j = 1; j < 10000; ++j) dat2[j][i] = dat2[j-1][i-1] + i+j;
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(CLK-start).count() << "ms"<< "\n";
}