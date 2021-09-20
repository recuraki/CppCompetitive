#include <bits/stdc++.h>
#include "unordered_map"
using namespace std;
using ll = long long int;


#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
#define SZ(x) ((int)(x).size())

#define pb push_back
#define em emplace
#define mp make_pair
#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)

// chmax/min: if update a then true
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }

template <typename T1, typename T2> pair<T1, T2> operator+(const pair<T1, T2> &l, const pair<T1, T2> &r) { return make_pair(l.first + r.first, l.second + r.second); }
template <typename T1, typename T2> pair<T1, T2> operator-(const pair<T1, T2> &l, const pair<T1, T2> &r) { return make_pair(l.first - r.first, l.second - r.second); }


#ifndef KANAILOCAL
#define KANAILOCAL 1
#endif

//////////////////////////////////////
#define dp(arg) if(KANAILOCAL) { cout << #arg << ":"; dprint(arg); }
template <typename T> void dprint(T arg) { cout << arg << "\n"; }
template <typename T> void dprint(const vector<T>& arg) { for_each(begin(arg), end(arg), [](T value){ cout << value << " "; }   ); cout << "\n";  }
template <typename T> void dprint(const vector<vector<T>>& arg) { for_each(begin(arg), end(arg), [=](vector<T> arg2){ dprint(arg2); cout << "\n";} );  }
//#define dprint(arg) ;
//////////////////////////////////////

using namespace std;

/*
 * Counter:
 * counter<int>.load(vector<int>)
 * counter<string>.load(vector<string>)
 * !!! Special Usage !!! counter<char>.load(string)
 */
template <class T>
struct Counter{
public:
    unordered_map <T, int> counter;
    vector<pair<T, int>> mostCounter;

    constexpr bool isExist(T x){
        if(counter.find(x) == counter.end()){
            return  false;
        }
        return  true;
    }


    void load (vector<T> invec){
        for (auto &x: invec){
            if(counter.find(x) == counter.end()){
                counter[x] = 1;
            } else {
                ++counter[x];
            }
        }
    }

    void load (string instr){
        for (int i = 0; i < (int)instr.length(); ++i){
            if(counter.find(instr[i]) == counter.end()){
                counter[instr[i]] = 1;
            } else {
                ++counter[instr[i]];
            }
        }
    }
    vector<T> keys(){
        vector<T> res;
        for(auto x = counter.begin(); x != counter.end(); ++x){
            res.push_back(x->first);
        }
        return res;
    };
    void mostcommon(){
        for(auto x = counter.begin(); x != counter.end(); ++x){
            mostCounter.push_back(make_pair(x->first, x->second));
        }
        sort(mostCounter.begin(), mostCounter.end(), [](auto const& l, auto const &r){
            if(l.second > r.second) { return true; }
            return false;
        });
    }
    void addOther(Counter arg){
        for(auto x = counter.begin(); x != counter.end(); ++x){
            if(arg.isExist(x)){
                counter[x] += arg.counter[x];
            }
        }
        for(auto x = arg.counter.begin(); x != arg.counter.end(); ++x){
            if(this->isExist(x)){
                counter[x] = arg.counter[x];
            } else {
                counter[x] += arg.counter[x];
            }
        }
    }

    constexpr int operator[](T x) { return counter[x]; }

};


int main() {
    unordered_map <string,int> counter;
    vector<string> stringVector {"Cat","Cat","Cat","Dog","Dog","Lizard"};
    Counter<string> c;
    c.load(stringVector);
    dp(c.keys()); // c.keys():Lizard Cat Dog
    c.mostcommon();
    /*
     * Cat:3, Dog:2, Lizard:1
     */
    for(auto x: c.mostCounter){
        cout << x.first << ":" << x.second << endl;
    }

    Counter<char> cc, cc2, cc3;
    string str1 = "recuraki";
    cc.load(str1);
    cc2.load(str1);
    cc.mostcommon();
    for(auto x: cc.mostCounter){
        cout << x.first << ":" << x.second << endl;
    }
    dp("+ operator")
    cc3 = cc + cc2;
    for(auto x: cc3.mostCounter){
        cout << x.first << ":" << x.second << endl;
    }



}
