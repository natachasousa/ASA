/*
 * Program that computes the maximum value obtainable from a slab of marble by
 * cutting it into pieces with specified dimensions and associated prices.
 *
 * Alunas: Beatiz Martinho (106835), Natacha Sousa (107413)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maximizeValue(int X, int Y, vector<vector<int> > &dp) {

    // test each possible cut (horizontally and vertically)
    for (int x = 0; x < (X+1) ; x++){
        for (int y = 0; y < Y+1; y++){
            if(x == 0 || y == 0){
                dp[x][y] = 0;
            } else {
                for (int a = 0; a <= x; a++){ // get the max value for the current horizontal cut
                    dp[x][y] = max(dp[x][y], dp[a][y] + dp[x - a][y]);
                }
                for (int b = 0; b <= y; b++){ // get the max value for the current vertical cut
                    dp[x][y] = max(dp[x][y], dp[x][b] + dp[x][y - b]);
                }
                // also check if not doing a cut is more favorable
                dp[x][y] = max(dp[x][y], dp[x - 1][y]); 
                dp[x][y] = max(dp[x][y], dp[x][y - 1]);
            }
        }
    }
    return dp[X][Y];
}

int main() {

    int X, Y, n, pieceX, pieceY, value;
    scanf("%d %d", &X, &Y);
    scanf("%d", &n);

    // Memory structure (cells inicialized at -1)
    vector<vector<int> > dp(X + 1, vector<int>(Y + 1, -1));

    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &pieceX, &pieceY, &value);
        // put the input pieces values in the cells correspondent to their size (in both directions)
        if (pieceX < X+1 && pieceY < Y+1){
            // also check if the correspondent cell alredy has a bigger value
            dp[pieceX][pieceY] = max(dp[pieceX][pieceY], value);
        }
        if (pieceX < Y+1 && pieceY < X+1){
            // also check if the correspondent cell alredy has a bigger value
            dp[pieceY][pieceX] = max(dp[pieceY][pieceX], value);
        }
    }

    printf("%d\n", maximizeValue(X, Y, dp));

    return 0;
}
