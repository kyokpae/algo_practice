// http://www.spoj.pl/problems/BLINNET/
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(x, n) for (int x = 0; x < (n); ++x)
#define VAR(v, n) __typeof(n) v=(n)
#define FOREACH(i, c) for ( VAR(i, (c).begin()); i != (c).end(); ++i)

struct Edge {
    Edge(short u, short v, unsigned int c) : u(u), v(v), c(c) {}
    short u, v;
    unsigned int c;
};

vector<Edge> E;
short V[10001];
short R[10001];

short findSet(short v) {
    if (V[v] != v) {
        V[v] = findSet(V[v]);
    }
    return V[v];
}
    
inline void linkSet(short u, short v) {
    if (R[u] > R[v]) {
        V[v] = u;
    } else {
        V[u] = v;
    }
    if (R[u] == R[v]) {
        R[v]++;
    }
}

bool edge_cmp(const Edge& A, const Edge& B) {
    return (A.c < B.c);
}

int main(void) {
    int t;
    scanf("%d", &t);
    E.reserve(100000);
    while (t--) {
        E.clear();        
        int n;
        scanf("%d", &n);
        REP(u, n) {
            V[u] = u;
            R[u] = 0;

            char name[20];
            int e;
            scanf("%s %d", name, &e);
            REP(i, e) {
                int v;
                unsigned int c;
                scanf("%d %u", &v, &c);
                E.push_back(Edge(u, v-1, c));
            }
        }
        std::sort(E.begin(), E.end(), edge_cmp);        
        unsigned int c = 0;
        int l = 1;
        FOREACH(it, E) {
            int U = findSet(it->u);
            int V = findSet(it->v);
            if (U != V) {
                c += it->c;
                linkSet(U, V);
                l++;
                if (l < n) {
                    continue;
                }                
            }
        }
        printf("%d\n", c);
    }
    return 0;
}
