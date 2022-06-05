//
// Created by kanai on 2022/01/30.
// https://leetcode.com/contest/weekly-contest-278/problems/keep-multiplying-found-values-by-two/

#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int findFinalValue(vector<int>& nums, int original) {
        unordered_set<int> st;
        for(auto &x: nums) st.insert(x);
        while(st.count(original) == 1) original *= 2;
        return original;
    }
};
