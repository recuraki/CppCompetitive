#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;
    for(int i=0; i< 20; i++){
        cout <<setw(4)  <<  i  << "(" << setw(8) << bitset<9>(s) << "): " << int((log2(i) + 1) / 1) << "-keta\n";
    }
}