// http://www.spoj.pl/problems/BLINNET/
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

#define REP(x, n) for (int x = 0; x < (n); ++x)
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
Vertex V[10001];
#define INF UINT_MAX

int main(void) {
    int t;
    scanf("%d", &t);
    while (t--) {
        q.clear();        
        int n;
        scanf("%d", &n);
        REP(u, n) {
            V[u].d = INF;
            V[u].E.clear();
            V[u].used = false;

            char name[20];
            int e;
            scanf("%s %d", name, &e);
            REP(i, e) {
                int v;
                Edge edge;                
                scanf("%d %u", &v, &(edge.c));
                v--;
                edge.v = &(V[v]);
                V[u].E.push_back(edge);
            }
        }    
        V[0].d = 0;
        q.insert(&V[0]);
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
        printf("%d\n", c);
    }
    return 0;
}
