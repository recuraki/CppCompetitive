#include <bits/stdc++.h>
using namespace std;

// 基本的な累積和
template <class T> struct cumSum1D{
public:
    vector<T> sdat;
    void load(const vector<T> &dat){
        this->sdat.resize(dat.size() + 1);
        this->sdat.at(0) = 0;
        for(int i = 0; i < dat.size(); i++){
            this->sdat.at(i + 1) = this->sdat.at(i) + dat.at(i);
        }
    };
    T query(const int l, const int r){
        /* Query [l, r)  //Close, Open */
        assert(l <= r);
        return(this->sdat.at(r) - this->sdat.at(l));
    };
};


void cumSum1D_sample1(){
    vector<int> a = {1,2,3,4,5};
    cumSum1D<int> sum1D;
    sum1D.load(a);
    cout << sum1D.query(0,5) << endl;
    cout << sum1D.query(1,5) << endl;
    cout << sum1D.query(2,2) << endl;
    cout << sum1D.query(2,3) << endl;
    cout << sum1D.query(3,2) << endl;
}

// https://judge.yosupo.jp/problem/static_range_sum
void static_range_sum(){
    cin.tie(0); ios::sync_with_stdio(false);
    int n, q; cin >> n >> q;
    vector<long long> dat(n);
    for(int i = 0; i < n; ++i) cin >> dat.at(i);
    cumSum1D<long long> cum;
    cum.load(dat);
    while(q--){
        int a, b;
        cin >> a >> b;
        cout << cum.query(a, b) << "\n";
    }
}

int main(){
    //cumSum1D_sample1();
    static_range_sum();
}