#include <bits/stdc++.h>
using namespace std;

int main(){
    // nullptr
    // PQは大きい順
    priority_queue<int, vector<int>, less<int>> pq;// と定義されている。これは大きい分に取り出す。
    pq.emplace(1);
    pq.emplace(-1);
    cout << pq.top() << "\n"; pq.pop();
    cout << pq.top() << "\n"; pq.pop();

    priority_queue<int, vector<int>, greater<int>> pq2; // とすると小さい順
    pq2.emplace(1);
    pq2.emplace(-1);
    cout << pq2.top() << "\n"; pq2.pop();
    cout << pq2.top() << "\n"; pq2.pop();

    vector<int> v = {2,1,3};
    sort(v.begin(), v.end());
    for(auto &vx: v) cout << vx << " ";
    sort(v.begin(), v.end(), less<int>()); // と定義されている
    for(auto &vx: v) cout << vx << " ";
    sort(v.begin(), v.end(), greater<int>()); // これで大きい順
    for(auto &vx: v) cout << vx << " ";

    vector<int> nums={1,2,3};
    int maxval = *max_element(nums.begin(), nums.end());

    deque<char> v2;
    v2.push_back('a');
    v2.push_back('1');
    v2.push_back('2');
    v2.push_front('z');
    string s2(v2.begin(), v2.end());
    cout << s2 << "\n";


    // IF false = 0 => while(1)だからねー

#define ceil(a,b) (((a) + ((b) - 1)) / (b))
    // string[index] はchar

}