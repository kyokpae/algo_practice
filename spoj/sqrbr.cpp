// http://www.spoj.pl/problems/SQRBR/
#include <iostream>
#include <cstring>

using namespace std;

int main(void) {
    int t;
    cin >> t;
    int dp[22][22];
    
    // zero dp
    for (int i = 0; i < 22; i++) {
        dp[0][i] = 0;
        if (i < 21) {
            dp[i+1][i] = 0;
        }
    }
    dp[1][1] = 1;
    
    char B[22][22];
    while (t--) {
        memset(B, 0, sizeof(B));
        // read input
        int n, k;
        cin >> n >> k;        
        // init mask
        for (int i = 0; i < k; i++) {
            int y = 1;
            int x;
            // read bracket position
            cin >> x;
            while (x > y) {
                B[y++][x--] = 1;
            }
        }
        // dp
        for (int i = 1; i <= n + 1; i++) {
            for (int j = i; j <= n + 1; j++) {
                if (i == 1 && j == 1) {
                    dp[i][j] = 1;
                    continue;
                }
                int sum = dp[i][j-1];
                if (!B[i-1][j]) {
                    sum += dp[i-1][j];
                }
                dp[i][j] = sum;
            }
        }        
        cout << dp[n+1][n+1] << endl;
    }
    return 0;
}
