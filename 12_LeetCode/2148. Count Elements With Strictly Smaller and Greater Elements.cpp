//
// Created by kanai on 2022/01/24.
//https://leetcode.com/contest/weekly-contest-277/problems/count-elements-with-strictly-smaller-and-greater-elements/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countElements(vector<int>& nums) {
        int maxval = *max_element(nums.begin(), nums.end());
        int minval = *min_element(nums.begin(), nums.end());
        int ans = 0;
        for(auto &x: nums){
            if(x != maxval && x != minval ) ++ ans;
        }
        return ans;

    }
};
