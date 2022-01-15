//
// Created by kanai on 2022/01/16.
//

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans;
        for(int i = 0; i < nums.size(); ++i){
            for(int j = i + 1; j < nums.size(); ++j){
                if(nums.at(i) + nums.at(j) == target){
                    ans.emplace_back(i);
                    ans.emplace_back(j);
                    return ans;
                }
            }

        }
        assert(false);
    }
};