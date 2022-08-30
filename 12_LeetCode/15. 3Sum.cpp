//
// Created by kanai on 2022/01/23.
//https://leetcode.com/problems/3sum/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        unordered_map<int, set<int>> cache;
        vector<vector<int>> ans;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for(int l = 0; l < n-1; ++l){
            int c = l + 1;
            int r = n - 1;
            while(c < r){
                auto t = nums[l] + nums[c] + nums[r];
                if(t < 0){
                    ++c;
                    continue;
                }
                if(t > 0){
                    --r;
                    continue;
                }
                /* ok! regist */
                /* check only c and l val */
                if(cache.count(nums[c]) == 1 && cache[nums[c]].count(nums[r]) == 1){
                    //
                } else {
                    cache[nums[c]].insert(nums[r]);
                    ans.push_back({nums[l], nums[c], nums[r]});
                }
                ++c; --r;
            }
        }
        return ans;

    }
};
