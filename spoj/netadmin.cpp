// http://www.spoj.pl/problems/NETADMIN/
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define REP(x, n) for (int x = 0; x < (n); x++)
#define VAR(v, n) __typeof(n) v=(n)
#define FOREACH(i, c) for ( VAR(i, (c).begin()); i != (c).end(); ++i)

struct Edge {
    Edge(int v) : v(v), used(false) {}
    int v;
    bool used;
};

struct Vertex {
    Vertex() : user(false), p(-1), e(NULL) {}
    bool user;
    int p;
    Edge * e;
    vector<Edge> E;
};

struct Graph {

    void solve() {
        int n, m, users;
        cin >> n >> m >> users;
        // read users
        REP(i, users) {
            int h;
            cin >> h;
            V[--h].user = true;
        }
        // read streets
        REP(i, m) {
            int u, v;
            cin >> u >> v;
            edgeU(--u, --v);
        }
        int flow = 0;
        while (true) {
            int q[500];
            int b = 0;
            int e = 0;
            int found = -1;
            REP(i, n) {
                V[i].p = -1;
                V[i].e = NULL;
            }
            q[0] = 0;
            V[0].p = 0;
            while (b <= e && found == -1) {
                int v = q[b++];
                //cout << v << " " << colors << endl;
                FOREACH(it, V[v].E) {
                    Edge& edge = *it;
                    if (!edge.used && V[edge.v].p == -1 && edge.v > 0) {
                        found = edge.v;
                        V[found].p = v;
                        V[found].e = &edge;                        
                        if (V[found].user) {
                            V[found].user = false;
                            flow++;
                            //cout << "Found " << found << endl;
                            break;
                        } else {
                            q[++e] = found;
                            found = -1;
                        }
                    }
                }
            }
            if (found == -1) {
                break;
            } else {
                //cout << "Found user in " << found << ". Connecting " << endl;
                while (found) {
                    //cout << "F " << found << endl;
                    //cout << "C " << V[found].c << endl;
                    V[found].e->used = true;
                    found = V[found].p;
                    //cout << found << " " << endl;
                }
                //cout << endl;
            }
        }
        int colors = (users / flow) + ((users % flow > 0) ? 1 : 0);
        cout << colors << endl;
    }

    void edgeU(int u, int v) {
        V[u].E.push_back(Edge(v));
        V[v].E.push_back(Edge(u));
    }

    Vertex V[500];
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        Graph g;
        g.solve();
    }
    return 0;
}

