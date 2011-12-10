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
        cuboid() : x(0), y(0), p(NULL), d(0), h(0), orig_h(0), t(0) {}
        cuboid(int y, int x) : x(x), y(y), d(0), h(0), orig_h(0), p(NULL), t(0) {}
        void reset() {
            if (p) {
                p = this;
            }
        }
        
        inline cuboid& findSet() {
            if (p == this) {
                return *this;
            } else {
                cuboid& ret = p->findSet();
                // path compression
                p = &ret;
                return ret;
            }
        }

        inline cuboid& unionSet(cuboid& C) {
            cuboid& c1 = findSet();
            cuboid& c2 = C.findSet();
            // subtree merge by rank heuristic
            if (c1.d <= c2.d) {
                c1.p = &c2;
                if (c1.d == c2.d) {
                    c2.d++;
                }
                return c2;
            } else {
                c2.p = &c1;
                return c1;
            }
        }
        
        friend ostream& operator<<(ostream& os, cuboid& c) {
            return os << c.findSet().h;
        }
        
        int x, y, d, orig_h, h, t;
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
            cuboid& C = s->findSet();
            // reject those which were already flooded
            if (&C != s) {
                continue;
            }
            cuboid * bfs[10000];
            int b = 0;
            int e = 0;
            bfs[0] = s;
            s->t = t;
            int h = INF;
            // spill water by BFS starting from s            
            while (b <= e) {
                cuboid * s = bfs[b++];
                cuboid& S = s->findSet();
                int dx[] = {1, 0, -1, 0};
                int dy[] = {0, -1, 0, 1};
                for (int i = 0; i < 4; i++) {
                    int x = s->x + dx[i];
                    int y = s->y + dy[i];
                    if (x >= 0 && y >= 0 && y <= N + 1 && x <= M + 1) {
                        cuboid& V = c[y][x].findSet();
                        if (c[y][x].t < t && V.h == S.h && x > 0 && y > 0 && y < N + 1 && x < M + 1) {
                            // connect puddles                            
                            c[y][x].t = t;
                            S.unionSet(c[y][x]);
                            bfs[++e] = &c[y][x];
                        } else if (V.h != S.h) {
                            // reached border of a puddle
                            if (V.h < h) {
                                h = V.h;
                            }
                        }
                    }
                }                
            }
            cuboid& D = C.findSet();
            if (h != INF && h > D.h) {
                // elevate puddle to the height of the border
                D.h = h;
                q.push_back(&D);
                push_heap(q.begin(), q.end(), cmp);
            }
        }
        // calculate volume
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                volume += c[i][j].findSet().h - c[i][j].orig_h;
            }
        }
        cout << volume << endl;        
    }
    
    void print() {
        for (int i = 0; i <= N + 1; i++) {
            for (int j = 0; j <= M + 1; j++) {
                cout << c[i][j].findSet().h << "\t";
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
