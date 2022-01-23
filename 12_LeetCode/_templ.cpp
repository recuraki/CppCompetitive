//
// Created by kanai on 2022/01/24.
//https://leetcode.com/problems/palindrome-number/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(long long x) {
        long long ox = x;
        long long y = 0;
        while(x > 0){
            y *= 10;
            y += x % 10;
            x /= 10;
        }
        if(ox == y) return true;
        return false;
    }
};

int main() {
    Solution st;
    cout << st.isPalindrome(-121) << "\n";
    cout << st.isPalindrome(121) << "\n";
}