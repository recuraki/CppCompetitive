//
// Created by kanai on 2022/01/24.
//https://leetcode.com/problems/coin-change/


class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int INF = 1e9;
        vector<long long> dp(amount + 1, INF);
        dp.at(0) = 0;
        for(auto &coin: coins){
            if(coin >= 1e9) continue;
            for(int i = 0; i < amount; ++i){
                if( (i + coin) <= amount ) dp[i + coin] = min(dp[i + coin], dp[i] + 1);
            }
        }
        if(dp.at(amount) == INF) return -1;
        return dp.at(amount);

    }
};
