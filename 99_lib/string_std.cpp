#include <bits/stdc++.h>
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

string str1(const string& a, const string& b){ return a + ":" + b;}

int main() {
    // Space?
    cout << isspace(' ') << ":" << isspace('a') << endl;
    // isspace " " or "tab" or \n or \r or \f or \r
    // isalpha a-z A-Z?
    // isdigit 0-9
    // isxdigit 0-9 A-F a-f
    // isupper A-Z
    // islower a-z
    // isalnum a-z A-Z 0-9
    // isprint 出力可能？

    cout << str1("abc", "def") << endl;
    string str2;
    str2 = str1("abc", "def");
    cout << str2 << endl;

    vector<string> v1 {"b1", "c1", "a1"};
    dp(v1);
    sort(ALL(v1));
    dp(v1);
    sort(ALL(v1), greater<string>());
    dp(v1);

    string s5 = {7, 'a'};
    cout << s5 << endl;

    // 比較演算子: ==, < > <= =>

    string str6 = "recuraki";
    cout << str6.size() << endl;
    str6.resize(10);
    cout << str6.size() << str6 << ":" << endl;

    dp(str6.at(2));
    str6.push_back('a');
    dp(str6);

    string strd = "0123456789";
    ll ll1 = stoll(strd);
    cout << ll1 << endl;

    dp(strd.assign(3,2));

    auto str7 = "recuraki"s;
    for(auto i = str7.begin(); i != str7.end(); i++){
        cout << " " << *i;
    }
    cout << endl;

    auto text = "quick brown fox jumps over the lazy dog."s ;
    // 12
    auto fox = text.find("fox"sv) ;
    // 32
    auto dog = text.find("dog"sv) ;
    auto fax = text.find("fax"sv) ;
    dp(fox);
    dp(dog);
    dp(fax == string::npos);

    text = "cat and cat and hoge and cat"s;
    dp(text + ": find cat")
    auto targetstr = "cat"s;
    auto pos = - targetstr.length();
    while(1){
        pos = text.find(targetstr, pos + targetstr.length());
        if(pos == string::npos) break;
        cout << pos << " ";

    }
    cout << endl;

    // replace str s/cat/batbatbat/g
    auto afterstr="batbatbat"s;
    pos = - afterstr.length();
    while(1){
        pos = text.find(targetstr, pos + afterstr.length());
        if(pos == string::npos) break;
        text.replace(pos, targetstr.length(), "batbatbat");
    }
    dp(text);



}
