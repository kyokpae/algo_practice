// http://www.spoj.pl/problems/RELATS1/
#include <cstdio>
#include <vector>

using namespace std;

#define FOR(x, b, e) for (int x = b; x <= (e); ++x)
#define FORD(x, b, e) for (int x = b; x >= (e); --x)
#define REP(x, n) for (int x = 0; x < (n); x++)
#define VAR(v, n) __typeof(n) v=(n)
#define FOREACH(i, c) for ( VAR(i, (c).begin()); i != (c).end(); ++i)

struct Vertex {
    Vertex() {}
    Vertex(int ss) {
        E.reserve(1001);
        reset(ss);
    }
    
    inline void reset(int ss) {
        E.clear();
        f = -1;
        d = -1;
        s = ss;
        r = 1;
    }

    vector<int> E;
    int f, d, r, s;
};

Vertex V[1000];

int findS(int v) {
    if (V[v].s != v) {
        V[v].s = findS(V[v].s);
    }
    return V[v].s;
}

inline void unionS(int u, int v) {
    int a = findS(u);
    int b = findS(v);
    if (V[a].r > V[b].r) {
        V[b].s = a;
    } else {
        V[a].s = b;
    }
    if (V[a].r == V[b].r) {
        V[b].r++;
    }
}

int topoDFS(int u, int& f) {
    V[u].d = 0;
    FOREACH(it, V[u].E) {
        int v = findS(*it);
        if (V[v].d == -1) {
            topoDFS(v, f);
        }
        V[u].d = max(V[u].d, 1 + V[v].d);
    }
    V[u].f = ++f;
    return V[u].d;
}

int main(void) {
    int d;
    scanf("%d", &d);
    while (d--) {
        int n, m;
        scanf("%d %d", &n, &m);
        REP(i, n) {
            V[i].reset(i);
        }
        REP(i, m) {
            int u, v, r;
            scanf("%d %d %d", &u, &v, &r);
            u--;
            v--;
            switch (r) {
            case -1: V[u].E.push_back(v); break;
            case  1: V[v].E.push_back(u); break;
            case  0: unionS(u, v);
            }
        }
        int f = 0;
        REP(i, n) {
            if (V[i].d == -1) {
                topoDFS(i, f);
            }
        }
        int result = 0;
        int cycle = false;
        REP(i, n) {
            int u = findS(i);
            result = max(result, V[u].d);
            FOREACH(it, V[i].E) {
                int v = findS(*it);
                if (V[u].f < V[v].f) {
                    cycle = true;
                }
            }
            if (cycle) {
                break;
            }
        }
        if (cycle) {
            printf("NO\n");
        } else {
            printf("%d\n", result);
        }
    }    
    return 0;
}

