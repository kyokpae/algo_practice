// http://www.spoj.pl/problems/CSTREET/
#include <set>
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
    Vertex * v;
    unsigned int c;
};

struct Vertex {
    unsigned int d;
    vector<Edge> E;
    bool used;
};

struct vertex_cmp {
bool operator()(const Vertex* a, const Vertex * b) const {
    return (a->d == b->d) ? a < b : a->d < b->d;
}
};

set<Vertex*, vertex_cmp> q;
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
        q.clear();
        q.insert(&V[1]);

        REP(i, m) {
            short u, v;
            Edge edge;
            scanf("%hd %hd %u", &(u), &(v), &(edge.c));
            edge.v = &V[v];
            V[u].E.push_back(edge);
            // in Prim's MST algorithm vertices can be reached through any of the edge's ends
            edge.v = &V[u];
            V[v].E.push_back(edge);
        }

        // Prim's MST algorithm
        unsigned int c = 0;
        int l = 0;
        while (!q.empty()) {
            // remove front vertex
            Vertex * v = *(q.begin());
            v->used = true;
            q.erase(q.begin());
            c += v->d;
            //for each of its neighbours
            FOREACH(e, v->E) {
                //decrement d if possible
                if (!e->v->used && e->v->d > e->c) {
                    q.erase(e->v);
                    e->v->d = e->c;
                    q.insert(e->v);
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
