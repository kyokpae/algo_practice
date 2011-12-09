// http://www.spoj.pl/problems/MAWORK/
#include <iostream>
#include <cstring>
#include <queue>
#include <bitset>

using namespace std;

struct vertex {
    vertex(char x, char y, int d) : x(x), y(y), d(d) {}
    int x;
    int y;
    int d;
};

int main(void) {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        
        queue<vertex> q;
        unsigned char R[27][27];
        unsigned char B[27][27];
        bitset<27*27> D[3000];
        D[5999].flip();
        
        char buf[200];
        cin.getline(buf, 200);
        for (int i = 0; i < n; i++) {
            cin.getline(buf, 200);
            for (int j = 0; j < n; j++) {
                R[i][j] = (buf[j] == '.') ? 0 : 1;                
            }
        }
        for (int i = 0; i < n; i++) {
            cin.getline(buf, 200);
            for (int j = 0; j < n; j++) {
                B[i][j] = buf[j] - '0';                
            }
        }
        q.push(vertex(0, 0, 0));
        while (!q.empty()) {
            vertex s = q.front();            
            //cout << s.x << " " << s.y << " " << s.d << endl;
            if (s.x == n - 1 && s.y == n - 1) {
                cout << s.d << endl;
                break;
            }            
            q.pop();
            int t = s.d + 1;            
            int dx[] = {1, 0, -1, 0, 0};
            int dy[] = {0, -1, 0, 1, 0};
            for (int i = 0; i < 5; i++) {
                int x = s.x + dx[i];
                int y = s.y + dy[i];
                int off = y * 27 + x;
                if (x >= 0 && y >= 0 && x < n && y < n && !D[t][off]) {
                    if (!(R[y][x] == 1 && B[y][x] == 0) && ((R[y][x] == 0 && B[y][x] == 0) || ((t / B[y][x]) % 2 == R[y][x]))) {
                        D[t][off] = 1;
                        q.push(vertex(x, y, t));
                    }
                }
            }
        }
        if (q.empty()) {
            cout << "NO" << endl;
        }
    }
    return 0;
}
