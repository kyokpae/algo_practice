#include <iostream>
#include <cstring>

using namespace std;

#define REP2(i, from, to) for (i = from; i < to; i++)
#define REP(i, to) REP2(i, 0, to)

int main(void) {
    while (true) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) {
            break;
        }

        int y[500][500];
        int b[500][500];
        int i, j;
        // read yeyenium deposits map
        REP(j, n) REP(i, m) {
            cin >> y[j][i];
        }
        // read blogium deposits map
        REP(j, n) REP (i, m) {
            cin >> b[j][i];
        }

        // solution
        int B[500];
        int rows[2][500];
        memset(rows, 0, sizeof(rows));
        memset(B, 0, sizeof(B));
        int prev = 0;
        int curr = 1;
        REP(j, n) {
            int Y = 0;
            REP(i, m) {
                Y += y[j][i];
                B[i] += b[j][i];
                int next_dp = rows[prev][i] + Y;
                next_dp = max(next_dp, rows[curr][i-1] + B[i]);
                rows[curr][i] = next_dp;
            }
            prev = curr;
            curr = (curr + 1) % 2;
        }
        cout << rows[prev][m-1] << endl;
    }
    return 0;
}
