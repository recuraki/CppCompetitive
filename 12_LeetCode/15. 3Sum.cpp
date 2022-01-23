//
// Created by kanai on 2022/01/23.
//https://leetcode.com/problems/3sum/


class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        unordered_map<int, vector<int>> mp;
        for(int i = 0; i < nums.size(); ++i) mp[nums[i]].emplace_back(i);

        for(int i = 0; i < nums.size(); ++i){
            for(int j = i + 1; j < nums.size(); ++j){
                auto need = - (nums[i] + nums[j]);
                if(mp.count(need) == 0) continue;
                for(auto &k: mp[need]){
                    if(k < i) ans.emplace_back({nums[k], nums[i], nums[j]})
                    else if(k < i && k < j) ans.emplace_back({nums[i],nums[k], nums[j]})
                    else if(k < i && j < k) ans.emplace_back({nums[i],nums[j], nums[k]})
                }
            }
        }
        return ans;




    }
};