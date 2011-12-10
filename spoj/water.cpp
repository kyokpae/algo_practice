// http://www.spoj.pl/problems/WATER/
// Used BFS to spill water puddles and disjoint sets forest to merge them
#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1000000001

using namespace std;
bool cmp(void * c1, void * c2);
struct mesh {

    // disjoint set implementation with subtree merge by rank heuristic and path compression
    struct cuboid {
        cuboid() : x(0), y(0), p(NULL), h(0), orig_h(0), t(0) {}
        cuboid(int y, int x) : x(x), y(y), h(0), orig_h(0), p(NULL), t(0) {}
        void reset() {
            if (p) {
                p = this;
            }
        }

        friend ostream& operator<<(ostream& os, cuboid& c) {
            return os << c.p->h;
        }

        int x, y, orig_h, h, t;
        cuboid * p;
    };

    void init(int n, int m) {
        N = n;
        M = m;
        // init heap
        static vector<cuboid*> q(10000);
        q.clear();
        // reset cuboids
        for (int i = 0; i <= n + 1; i++) {
            for (int j = 0; j <= m + 1; j++) {
                if (i > 0 && j > 0 && i <= n && j <= m) {
                    c[i][j] = cuboid(i, j);
                    c[i][j].p = &c[i][j];
                    // fill heap
                    q.push_back(&c[i][j]);
                } else {
                    c[i][j].p = &c[0][0];
                }
                c[i][j].t = 0;
            }
        }
        // read input
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> c[i][j].h;
                c[i][j].orig_h = c[i][j].h;
            }
        }
        // init heap
        make_heap(q.begin(), q.end(), cmp);
        int volume = 0;
        int t = 0;
        while (!q.empty()) {
            t++;
            cuboid * s = q.front();
            pop_heap(q.begin(), q.end(), cmp);
            q.pop_back();

            // reject those which were already flooded
            if (s != s->p) {
                continue;
            }
            s->t = t;
            cuboid * bfs[10000];
            int b = 0;
            int e = 0;
            bfs[0] = s;
            int h = INF;
            // spill water by BFS starting from s
            while (b <= e) {
                cuboid * u = bfs[b++];
                int dx[] = {1, 0, -1, 0};
                int dy[] = {0, -1, 0, 1};
                for (int i = 0; i < 4; i++) {
                    int x = u->x + dx[i];
                    int y = u->y + dy[i];
                    if (x >= 0 && y >= 0 && y <= N + 1 && x <= M + 1) {
                        cuboid * next = &c[y][x];
                        if (next->t < t && next->p->h == s->h && x > 0 && y > 0 && y < N + 1 && x < M + 1) {
                            // connect puddles
                            next->t = t;
                            next->p = s;
                            bfs[++e] = next;
                        } else if (next->p->h != s->h) {
                            // reached border of a puddle
                            if (next->p->h < h) {
                                h = next->p->h;
                            }
                        }
                    }
                }
            }
            if (h != INF && h > s->h) {
                // elevate puddle to the height of the border
                s->h = h;
                q.push_back(s);
                push_heap(q.begin(), q.end(), cmp);
            }
        }
        // calculate volume
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                volume += c[i][j].p->h - c[i][j].orig_h;
            }
        }
        cout << volume << endl;
    }

    void print() {
        for (int i = 0; i <= N + 1; i++) {
            for (int j = 0; j <= M + 1; j++) {
                cout << c[i][j].p->h << "\t";
            }
            cout << endl;
        }
    }

    cuboid c[102][102];
    int N;
    int M;
};

bool cmp(void * c1, void * c2) {
    return ((mesh::cuboid *)c1)->h > ((mesh::cuboid *)c2)->h;
}

int main(void) {
    mesh terrain;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        terrain.init(n, m);
    }
    return 0;
}
