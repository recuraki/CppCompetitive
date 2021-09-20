#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using pint = pair<int, int>;
using plint = pair<ll, ll>;
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
// 素数判定 試し割り
std::random_device rnd;
// https://tacos.hatenadiary.jp/entry/2020/06/04/001512
long long modpow(long long a, long long n, long long mod) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}
// ミラーラビン
bool is_prime(ll n){
    int k = 50;
    n = abs(n);
    if(n==2) return true;

    if(n==0) return false;
    if(n==1) return false;
    if(n%2==0) return false;

    ll d = (n - 1) >> 1;
    while( (d&1) == 0) d>>= 1;

    for(int i=0; i < k; ++i){
        ll a = (rnd() % (n-1) )+ 1;
        ll t = d;
        ll y = modpow(a, t, n);

        while(t!=(n-1) && y!=1LL && y!=(n-1) ){
            y = modpow(y, 2LL, n);
            t <<= 1;
        }
        if (y!=(n-1) && ( (t&1) ==0)){
            return false;
        }
    }
    return true;
}




bool is_prime_damedame(long long N) {
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
// SPF: ある値を割り切れる最小の数。12なら2, 素数ならその数自身
// PrimeList[x]: xが素数なら1
// primes 素数のリスト
// O(logN)
const long long PRIMEMAXSIZE = (100000) +1; // 10^6 開区間なのでこの場合は10^6も検査対象に入る
vector<long long >primeList(PRIMEMAXSIZE , true);
vector<long long >primes;
vector<long long >primeSPF(PRIMEMAXSIZE); // smallest prime factor
void gen_prime_sieve(int N) {
    primeList[0] = primeList[1] = false ;
    for (long long int i=2; i<N ; i++) {
        if (primeList[i]) { primes.push_back(i); primeSPF[i] = i; }
        for (long long int j=0; j < (int)primes.size() &&
             i * primes[j] < N && primes[j] <= primeSPF[i]; j++) {
            primeList[i * primes[j]]=false;
            primeSPF[i * primes[j]] = primes[j] ;
        }
    }
}

// 素因数分解 (unordered mapではなく、ordered)
// 素数の場合はその数自身を返す
// https://ei1333.github.io/luzhiled/snippets/math/prime-factor.html
// <約数:ll, その約数の数:int>のmapを返す
// つまり、3 5 5と出る場合なら、{3,1} と {5,2}を返す
map<ll, int> prime_factor(ll n) {
    map<ll, int> ret;
    for(ll i = 2; i * i <= n; i++) {
        while(n % i == 0) { ret[i]++; n /= i; }
    }
    if(n != 1) ret[n] = 1; // n is Prime
    return ret;
}
// expandしたもの。つまり、[3 5 5]などを返す
// prime_factor_expand(75):3 5 5
vector<ll> prime_factor_expand(ll n){
    map<ll, int> facts;
    vector<ll> res;
    for(auto item: prime_factor(n)) { // 3 5 5
        while(item.second--) res.emplace_back(item.first);
    }
    return res;
}

// 約数のリストを返す (unordered mapのprime factorではない)
// 昇順
// divisors(75):1 3 5 75
// divisors(13):1 13
vector<ll> divisors(ll n) {
    auto pf = prime_factor(n);
    vector<ll> res = vector<ll>({1});
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
    cout << "prime 1-12" << "\n";
    gen_prime_sieve(13); // 1-12
    dp(primes); // primes:2 3 5 7 11
    //dp(primeList); // 0 0 1 1 0 1 0 1 0 0 0 1  0 1 1 1 1 1 1 1 1
    //dp(primeSPF);  // 0 0 2 3 2 5 2 7 2 3 2 11 2 0 0 0 0 0 0 0 0
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
    cout << "\n";
    dp(prime_factor_expand(75));
}

void test_divisors() {
    vector<ll> res;
    cout << "75:" << "\n";
    dp(divisors(75));
    cout << "13:" << "\n";
    dp(divisors(13));
}

int main(){
    cout << "prime" << "\n";
    test_is_prime(1);
    test_is_prime(3);
    test_is_prime(13);
    test_is_prime(25);
    test_is_prime(69);
    test_is_prime(10007);
    test_gen_prime_sieve();
    test_prime_factor();
    cout << "divv" << "\n";
    test_divisors();
}