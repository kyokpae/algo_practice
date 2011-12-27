// http://www.spoj.pl/problems/CSTREET/
#include <queue>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <climits>

using namespace std;

#define FOR(x, b, e) for (int x = b; x <= (e); ++x)
#define FORD(x, b, e) for (int x = b; x >= (e); --x)
#define REP(x, n) for (int x = 0; x < (n); x++)
#define VAR(v, n) __typeof(n) v=(n)
#define FOREACH(i, c) for ( VAR(i, (c).begin()); i != (c).end(); ++i)

struct Vertex;
struct Edge {
    int v;
    unsigned int c;
};

struct Vertex {
    unsigned int d;
    vector<Edge> E;
    bool used;
};

struct VertexIndex {
    VertexIndex(int v, unsigned int d) : v(v), d(d) {}
    int v;
    unsigned int d;
};

struct vertex_index_cmp {
bool operator()(const VertexIndex& b, const VertexIndex& a) const {
    return (a.d == b.d) ? &a < &b : a.d < b.d;
}
};

Vertex V[1001];
#define INF UINT_MAX

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        int p, n, m;
        scanf("%d %d %d", &p, &n, &m);
        FOR(i, 2, n) {
            V[i].E.clear();
            V[i].d = INF;
            V[i].used = false;
        }
        V[1].d = 0;
        priority_queue<VertexIndex, vector<VertexIndex>, vertex_index_cmp> q;
        q.push(VertexIndex(1, 0));

        REP(i, m) {
            short u, v;
            Edge edge;
            scanf("%hd %hd %u", &(u), &(v), &(edge.c));
            edge.v = v;
            V[u].E.push_back(edge);
            // in Prim's MST algorithm vertices can be reached through any of the edge's ends
            edge.v = u;
            V[v].E.push_back(edge);
        }

        // Prim's MST algorithm
        unsigned int c = 0;
        int l = 0;
        while (!q.empty()) {
            VertexIndex vi = q.top();
            Vertex& v = V[vi.v];
            q.pop();
            if (v.used) {
                continue;
            }
            //printf("%d %d\n", vi.v, v.d);
            v.used = true;
            c += v.d;
            //for each of its neighbours
            FOREACH(e, v.E) {
                //decrement d if possible
                if (!V[e->v].used && V[e->v].d > e->c) {
                    V[e->v].d = e->c;
                    q.push(VertexIndex(e->v, e->c));
                    //printf("push %d %d\n", e->v, e->c);
                }
            }
            l++;
            if (l >= n) {
                break;
            }

        }
        printf("%d\n", c * p);
    }
    return 0;
}
