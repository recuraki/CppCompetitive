//
// Created by kanai on 2022/01/30.
// https://leetcode.com/contest/weekly-contest-278/problems/all-divisions-with-the-highest-score-of-a-binary-array/


class Solution {
public:
    vector<int> maxScoreIndices(vector<int>& nums) {
        vector<int> ans;
        int ansval;
        int sl = 0;
        int sr = 0;
        for(auto &val: nums){
            if(val == 1) ++sr;
        }
        ansval = sr;
        ans = {0};
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] == 0){
                ++sl;
            } else {
                --sr;
            }
            auto score = sl + sr;
            if(score > ansval){
                ansval = score;
                ans = {i+1};
            } else if (score == ansval) {
                ans.emplace_back(i+1);
            }
        }
        return ans;
    }
};
