// http://www.spoj.pl/problems/LABYR1/
#include <iostream>

using namespace std;

#define REP(x, n) for (int x = 0; x < (n); x++)

char buf[1002];
bool l[1000][1000];
int w, h;
int rope;

int visit(int x, int y, int d) {
    l[y][x] = false;
    int d1 = 0;
    int d2 = 0;
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, -1, 0, 1};
    REP(i, 4) {
        int X = x + dx[i];
        int Y = y + dy[i];
        if (X >= 0 && Y >= 0 && X < w && Y < h && l[Y][X]) {
            int len = visit(X, Y, 1);
            if (len > d1) {
                d2 = d1;
                d1 = len;
            } else if (len > d2) {
                d2 = len;
            }
            if (d1 + d2 > rope) {
                rope = d1 + d2;
            }
        }
    }
    return d + d1;
}

int main(void) {
    int t;
    cin >> t;
    while (t--) {
        cin >> w >> h;
        cin.getline(buf, 1002);

        int sx = 0;
        int sy = 0;

        REP(y, h) {
            cin.getline(buf, 1002);
            REP(x, w) {
                l[y][x] = (buf[x] == '.');
                if (buf[x] == '.') {
                    l[y][x] = true;
                    sx = x;
                    sy = y;
                } else {
                    l[y][x] = false;
                }
            }
        }
        rope = 0;
        visit(sx, sy, 0);
        cout << "Maximum rope length is " << rope << "." << endl;
    }
    return 0;
}
