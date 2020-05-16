#include <bits/stdc++.h>
using namespace std;
using lint = long long int;
using pint = pair<int, int>;
using plint = pair<lint, lint>;
struct fast_ios { fast_ios(){ cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20); }; } fast_ios_;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

//////////////////////////////////////
#include <iostream>
using namespace std;
#define dp(arg) do { cout << #arg << ":"; dprint(arg); } while(0)

template <typename T> void dprint(T arg) { cout << arg << "\n"; }
template <typename T> void dprint(const vector<T>& arg) { for_each(begin(arg), end(arg), [](T value){ cout << value << " "; }   ); cout << "\n";  }
template <typename T> void dprint(const vector<vector<T>>& arg) { for_each(begin(arg), end(arg), [=](vector<T> arg2){ dprint(arg2); cout << "\n";} );  }

// #define dprint(arg) ;
//////////////////////////////////////

bool is_prime(long long N) {
    if (N == 1) return false;
    else if (N == 2) return true;
    else if (N % 2 == 0) return false;

    for (long long i = 3; i * i <= N; i = i + 2) {
        if (N % i == 0) return false;
    }
    return true;
}

// https://www.geeksforgeeks.org/prime-factorization-using-sieve-olog-n-multiple-queries/?ref=rp
// 生成される区間は[2, N)  PRIMEMAXは使う最大数に合わせる
// O(N)
const long long PRIMEMAXSIZE = (1000000) +1; // NOT 10^9
vector<long long >isprime(PRIMEMAXSIZE , true);
vector<long long >primes;
vector<long long >primeSPF(PRIMEMAXSIZE); // smallest prime factor
void gen_prime_sieve(int N) {
    isprime[0] = isprime[1] = false ;
    for (long long int i=2; i<N ; i++) {
        if (isprime[i]) { primes.push_back(i); primeSPF[i] = i; }
        for (long long int j=0; j < (int)primes.size() &&
             i * primes[j] < N && primes[j] <= primeSPF[i]; j++) {
            isprime[i * primes[j]]=false;
            primeSPF[i * primes[j]] = primes[j] ;
        }
    }
}
// 素因数分解 (unordered mapではない)
// 素数の場合はその数自身を返す
// https://ei1333.github.io/luzhiled/snippets/math/prime-factor.html
// <約数:lint, その約数の数:int>のmapを返す
map<lint, int> prime_factor(lint n) {
    map<lint, int> ret;
    for(lint i = 2; i * i <= n; i++) {
        while(n % i == 0) { ret[i]++; n /= i; }
    }
    if(n != 1) ret[n] = 1; // n is Prime
    return ret;
}

// 約数のリストを返す (unordered mapのprime factorではない)
// 昇順
vector<lint> divisors(lint n) {
    auto pf = prime_factor(n);
    vector<lint> res = vector<lint>({1});
    if(pf.size() == 1){ res.push_back(n); return res; }
    for(auto item: pf) { res.push_back(item.first); }
    res.push_back(n); return res;
}

/////////////////////////
void test_is_prime(long long i){
    if (is_prime(i)){
        cout << i << " is primes" << "\n";
    } else {
        cout << i << " is NOT primes" << "\n";
    }
}

void test_gen_prime_sieve(){
    gen_prime_sieve(13); // 1-12
    dprint(primes);
}

void test_prime_factor() {
    cout << "75:" << "\n";
    for(auto item: prime_factor(75)) { // 3 5 5
        while(item.second--) cout << " " << item.first;
    }
    cout << "\n";
    cout << "13:" << "\n";
    for(auto item: prime_factor(13)) { // 13
        while(item.second--) cout << " " << item.first;
    }
}

void test_divisors() {
    vector<lint> res;
    cout << "75:" << "\n";
    dp(divisors(75));
    cout << "13:" << "\n";
    dp(divisors(13));
}

int main(){
    cout << "prime" << "\n";
    test_is_prime(1);
    test_is_prime(3);
    test_is_prime(25);
    test_is_prime(13);
    test_gen_prime_sieve();
    test_prime_factor();
    cout << "divv" << "\n";
    test_divisors();
}