#include <bits/stdc++.h>
using namespace std;

int main(){
    // f1は intを返し、intを取る関数、のポインタ
    int (*f1)(int);
    // f1の型を宣言しているので、f2で先行して呼べる
    auto f2 = [&](int x) { return f1(x); };
    // ここでf2を宣言する。
    f1 = [](int x) { return x + 100; };
    cout << f2(1) << "\n"; // 101

    // 関数ポインタ的な扱いをするときはキャプチャできないので、以下はコンパイルエラーになる
    // もし、f3 = [&](int x){..}ができれば通るが、この使い方は一切キャプチャができない
    /*
    int (*f3)(int);
    int (*f4)(int);
    f3 = [](int x) { if(x==0) return 0; cout<<"f3:"<<x<<"\n"; f4(x-1); };
    f4 = [](int x) { if(x==0) return 0; cout<<"f4:"<<x<<"\n"; f3(x-1); };
    f3(3);
    */
}