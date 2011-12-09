// http://www.spoj.pl/problems/BITMAP/
#include <iostream>
#include <cstring>

using namespace std;

typedef pair<unsigned char, unsigned char> vertex;

int main(void) {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        
        vertex queue[182 * 182];
        unsigned char B[182][182];
        short D[182][182];
        int b = 0;
        int e = -1;
        char buf[200];        
        cin.getline(buf, 200);
        for (int i = 0; i < n; i++) {
            cin.getline(buf, 200);
            for (int j = 0; j < m; j++) {
                if (buf[j] == '1') {
                    queue[++e] = vertex(i, j);
                    B[i][j] = 1;
                    D[i][j] = 0;
                } else {
                    B[i][j] = 0;
                    D[i][j] = -1;                    
                }
            }
        }
        while (b <= e) {
            vertex s = queue[b++];
            int dist = D[s.first][s.second] + 1;
            int dx[] = {1, 0, -1, 0};
            int dy[] = {0, -1, 0, 1};
            for (int i = 0; i < 4; i++) {
                int x = s.second + dx[i];
                int y = s.first + dy[i];
                if (x >= 0 && y >= 0 && x < m && y < n) {
                    if (D[y][x] == -1) {
                        D[y][x] = dist;
                        queue[++e] = vertex(y, x);
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << D[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
