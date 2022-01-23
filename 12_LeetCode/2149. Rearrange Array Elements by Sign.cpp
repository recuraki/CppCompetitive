//
// Created by kanai on 2022/01/24.
//https://leetcode.com/contest/weekly-contest-277/problems/rearrange-array-elements-by-sign/
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> p;
        vector<int> n;
        for(auto &x: nums){
            if(x<0){n.emplace_back(x);}
            else{p.emplace_back(x);}
        }
        vector<int> ans;
        for(int i=0; i < nums.size(); ++i){
            if(i%2 == 0) ans.emplace_back(p[i/2]);
            else ans.emplace_back(n[i/2]);
        }
        return ans;

    }
};
