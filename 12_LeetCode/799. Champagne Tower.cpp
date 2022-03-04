//
// Created by kanai on 2022/03/04.
//

/*

0      0
1     0 1
2    0 1 2
3   0 1 2 3
4  0 1 2 3 4
5 0 1 2 3 4 5
なので、j段目のiを見ていき、1を引いた1/2を iとi+1に流せばいい
*/
class Solution {
public:

    double champagneTower(int poured, int query_row, int query_glass) {
        long double res[100][100];
        memset(res, 0, sizeof(res));
        res[0][0] = poured;
        for(int h = 0; h < 99; ++h){
            for(int w = 0; w <= h; ++w){
                if(res[h][w] <= 1L) continue;
                res[h+1][w] += (res[h][w] - 1) / 2L;
                res[h+1][w+1] += (res[h][w] - 1) / 2L;
            }
        }
        return min(res[query_row][query_glass], (long double)1);

    }
};