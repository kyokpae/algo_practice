#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

const long long prime = 1000000007;

#define REPi(from, to) for (int i=from; i<to; i++)
#define REPj(from, to) for (int j=from; j<to; j++)

class SmallBricks31 {
public:
    int graph[1111][1111];
    long long dp[2][1111];

    int countWays(int w, int h) {
        REPi(0, 1<<w) REPj(0, 1<<w) graph[i][j] = 0;
        REPi(0, 1<<w) generateEdge(0, 0, i);

        REPi(0, 1<<w) dp[0][i] = 0;
        dp[0][(1<<w) - 1] = 1;
        int k = 0, l = 1;

        while (h--) {
            REPi(0, 1<<w) dp[l][i] = 0;
            REPi(0, 1<<w) REPj(0, 1<<w) dp[l][j] = (dp[l][j] + dp[k][i] * graph[i][j]) % prime;
            k = l;
            l = ~l & 1;
        }
        int res = 0;
        REPi(0, 1<<w) res = (res + dp[k][i]) % prime;
        return res;
    }

    // rekurencyjnie wygeneruj możliwe struktury
    void generateEdge(int w, int top, int bottom) {
        if (w == 10) {
            graph[bottom][top]++;
            return;
        }
        // pusta przestrzen
        generateEdge(w+1, top, bottom);
        // klocek 1
        if (bottom & (1<<w)) {
            generateEdge(w+1, top | (1<<w), bottom);
        }
        // klocek 2
        if ((bottom & (1<<w)) && (bottom & (1<<(w+1)))) {
            generateEdge(w+2, top | (1<<w) | (1<<(w+1)), bottom);
        }
        // klocek 3
        if ((bottom & (1<<w)) && (bottom & (1<<(w+2)))) {
            generateEdge(w+3, top | (1<<w) | (1<<(w+1)) | (1<<(w+2)), bottom);
        }
    }
};

int brick(int w, int h) {
    SmallBricks31 b;
    return b.countWays(w, h);
}

int main(void) {
    assert(4 == brick(1, 3));
    assert(13 == brick(3, 1));
    assert(84 == brick(3, 2));
    assert(587048789 == brick(6, 9));
    assert(170708663 == brick(6, 8));
    assert(237973525 == brick(5, 8));
    assert(24861902 == brick(6, 7));
    assert(81051310 == brick(6, 10));
    assert(21034400 == brick(5, 9));
    assert(82403180 == brick(5, 10));
    assert(9403676 == brick(10, 2));
    assert(301887 == brick(4, 5));
    assert(132976888 == brick(4, 9));
    assert(11676046 == brick(5, 5));
    assert(536794181 == brick(8, 9));
    return 0;
}
