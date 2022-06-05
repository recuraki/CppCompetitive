//
// Created by kanai on 2022/02/06.
// https://leetcode.com/problems/triangle/submissions/



class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int INF = 1e9;
        int ans = INF;
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, INF));
        dp[0][0] = triangle[0][0];
        for(int h = 0; h < (n-1); ++h){
            for(int w = 0; w <= h; ++w){
                dp[h+1][w] = min(dp[h+1][w], dp[h][w] + triangle[h+1][w]);
                dp[h+1][w+1] = min(dp[h+1][w+1], dp[h][w] + triangle[h+1][w+1]);
            }
        }
        for(int w = 0; w < n; ++w) ans = min(ans, dp[n-1][w]);
        return ans;
    }
};
