//
// Created by kanai on 2022/02/06.
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/submissions/


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        int mi = prices[0];
        for(auto &x: prices){
            mi = min(mi, x);
            ans = max(ans, x - mi);
        }
        return ans;
    }
};
