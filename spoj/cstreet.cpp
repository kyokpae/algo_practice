// http://www.spoj.pl/problems/CSTREET/
#include <cstdio>
#include <cstdlib>

#define REP(x, n) for (int x = 0; x < (n); ++x)

struct Edge {
    short u, v;
    unsigned int c;
};

Edge E[300000];
short V[1001];
short R[1001];

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

int edge_cmp(const void * a, const void * b) {
    const Edge * A = (const Edge *) a;
    const Edge * B = (const Edge *) b;
    return (A->c < B->c) ? -1 : (A->c > B->c) ? 1 : 0;
}

int main(void) {
    int t;
    scanf("%d", &t);
    while (t--) {
        int p, n, m;
        scanf("%d %d %d", &p, &n, &m);
        REP(i, m) {
            scanf("%hd %hd %u", &(E[i].u), &(E[i].v), &(E[i].c)); 
        }
        REP(i, n) {
            V[i] = i;
            R[i] = 0;
        }
        qsort(E, m, sizeof(Edge), edge_cmp);
        unsigned int c = 0;
        int l = 1;
        int i = 0;
        while (l < n) {
            int U = findSet(E[i].u);
            int V = findSet(E[i].v);
            if (U != V) {
                c += E[i].c;
                linkSet(U, V);
                l++;
            }
            i++;
        }
        printf("%d\n", p * c);
    }
    return 0;
}
