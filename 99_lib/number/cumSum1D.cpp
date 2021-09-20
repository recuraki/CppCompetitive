#include <bits/stdc++.h>
using namespace std;

// cumulative sum 1D

template <class T> struct cumSum1D{
public:
    vector<T> sdat;
    void load(vector<T> dat){
        this->sdat.resize(dat.size() + 1);
        this->sdat.at(0) = 0;
        for(int i = 0; i < dat.size(); i++){
            this->sdat.at(i + 1) = this->sdat.at(i) + dat.at(i);
        }
    };
    T query(int l, int r){
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

main(){
    cumSum1D_sample1();
}