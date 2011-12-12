// http://www.spoj.pl/problems/TOUR/
#include <iostream>
#include <vector>

using namespace std;

#define FOR(x, b, e) for (int x = b; x <= (e); ++x)
#define FORD(x, b, e) for (int x = b; x >= (e); --x)
#define REP(x, n) for (int x = 0; x < (n); x++)
#define VAR(v, n) __typeof(n) v=(n)
#define FOREACH(i, c) for ( VAR(i, (c).begin()); i != (c).end(); ++i)

struct Vertex {
    Vertex() : p(-1), s(-1), f(-1) {}
    int p, s, f;
    vector<int> E;
};

void dfsVisit(Vertex * V, vector<int>& order, int u, int& t) {
    V[u].s = ++t;     
    FOREACH(it, V[u].E) {
        int v = *it;
        if (V[v].s == -1) {
            V[v].p = u;
            dfsVisit(V, order, v, t);
        }
    }
    order.push_back(u);    
    V[u].f = ++t;
}

int main(void) {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        Vertex V[1000];
        Vertex IV[1000];
        Vertex SSC[1000];
        vector<int> order;
        vector<int> iorder;
        //read input
        REP(i, n) {
            int m;
            cin >> m;
            REP(j, m) {
                int f;
                cin >> f;
                f--;
                V[f].E.push_back(i);
                IV[i].E.push_back(f);
            }
        }
        // first pass of dfs, on G
        int t = 0;
        REP(i, n) {
            if (V[i].s == -1) {
                dfsVisit(V, order, i, t);
            }
        }
        // second pass of dfs, on G in topological order
        int it = 0;
        FORD(i, n - 1, 0) {
            int v = order[i];
            if (IV[v].s == -1) {
                dfsVisit(IV, iorder, v, it); 
            }
        }
        REP(i, n) {
            V[i].s = 0;
        }
        // generated subtrees are strongly connected components
        // fold forest of ssc trees into single vertices (V[i].f)
        REP(i, n) {
            int v = i;
            while (IV[v].p != -1) {
                v = IV[v].p;
            }
            V[i].f = v;
            V[v].s++;
        }
        
        bool winners[1000];
        REP(i, n) {
            winners[i] = true;
        }
        // mark beatable SSC's
        REP(i, n) {
            FOREACH(it, V[i].E) {
                int v = *it;
                if (V[i].f != V[v].f || (V[i].f == -1 && V[v].f == -1)) {
                    winners[V[v].f] = false;
                }                 
            }
        }
        int result = 0;
        int count = 0;
        // check if there's only one unbeatable SSC
        REP(i, n) {
            if (winners[i] && V[i].s > 0) {
                result = V[i].s;
                count++;
            }

        }
        // if only one unbeatable SSC exists, return its cardinality
        cout << ((count == 1) ? result : 0 ) << endl;
    }
    return 0;
}
