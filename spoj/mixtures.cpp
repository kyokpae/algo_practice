// http://www.spoj.pl/problems/MIXTURES/
#include <iostream>
#include <climits>

using namespace std;

int main(void) {
    while (cin.good()) {
        int n;
        cin >> n;
        if (!cin.good()) {
            return 0;
        }
        int c[100];
        int C[100][100];
        int S[100][100];
        // read input
        for (int i = 0; i < n; ++i) {
            cin >> c[i];
            C[i][i] = c[i];
            S[i][i] = 0;
        }
        // dp solution
        for (int j = n-2; j >= 0; --j) {
            for (int i = j+1; i < n ; ++i) {
                int best = INT_MAX;                
                for (int k = j; k < i; ++k) {
                    int smoke = C[j][k] * C[k+1][i] +S[j][k] + S[k+1][i];
                    if (smoke < best) {
                        C[j][i] = (C[j][k] + C[k+1][i]) % 100;
                        S[j][i] = smoke;
                        best = smoke;
                    }
                }
            }
        }
        cout << S[0][n-1] << endl;
    }
    return 0;
}
