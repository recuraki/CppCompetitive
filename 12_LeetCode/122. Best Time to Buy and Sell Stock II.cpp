//
// Created by kanai on 2022/02/06.
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

/*
dp[i][status]
0 = dont have
1 = have
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int INF = 1 << 30;
        int n = prices.size();
        int dp[n][2];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for(int i = 1; i < n; ++i){
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
        }
        return dp[n-1][0];
    }
};
