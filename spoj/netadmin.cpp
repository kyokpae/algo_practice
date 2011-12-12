// Graph
#include <iostream>
#include <vector>

using namespace std;

#define REP(x, n) for (int x = 0; x < (n); x++)
#define VAR(v, n) __typeof(n) v=(n)
#define FOREACH(i, c) for ( VAR(i, (c).begin()); i != (c).end(); ++i)

template <int N> class Graph {
public:
    class Edge {
    public:
        Edge() : v(-1), c(0), u(0) {}
        Edge(int v) : v(v), c(0), u(0) {}
        int v;
        //////////////////////////////////////
        bool ok() {
            return (c - u) > 0;
        }
        
        void visit() {
            //cout << "e" << endl;
            u++;
        }

        int c, u;
    };
    
    class Vertex {
    public:
        Vertex() : s(-1), f(-1), p(-1), user(false), connected(false) {}
                
        void reset(int c) {
            f = s = p = -1; connected = false;
            FOREACH(it, E) {
                Edge& e = *it;
                if (e.v == -1) {
                    e.c = 1;
                } else {
                    e.c = c;
                }
            }
        }
        void clear() { E.clear(); reset(); }
        int s, f, p;
        vector<Edge> E;
        ///////////////////////////////////////
        void visit(int v) {
            p = v;
        }

        bool user, connected;
    };
    
    void edgeU(int from, int to) {
        edgeD(from, to);
        edgeD(to, from);
    }
    
    void edgeD(int from, int to) {
        V[from].E.push_back(Edge(to));
    }
    
    void dfs(int n) {
        int t = 0;
        REP(i, n) {
            if (V[i].s == -1) {
                dfsVisit(i, t);
            }
        }
    }
    
    int maxFlow(int n) {
        int flow = 0;
        while (true) {
            REP(i, n) {
                V[i].s = -1;
            }
            int t = 0;
            if (!dfsVisit(0, t)) {
                break;
            }
            flow++;
        }
        return flow;
    }    
    
    bool dfsVisit(int i, int& t) {
        //cout << "dfs " << i << endl;
        V[i].s = ++t;
        FOREACH(it, V[i].E) {
            Edge& e = *it;
            if (e.v == -1) {
                //cout << "reached sink" << endl;
                e.visit();
                return true;
            } else            
            if (V[e.v].s == -1 && e.ok()) {
                V[e.v].visit(i);
                int ret = dfsVisit(e.v, t);
                if (ret) {
                    e.visit();
                    return true;
                }
            }
        }
        return false;
        V[i].f = ++t;
    }
    
    void solve() {
        int n, m, users;
        cin >> n >> m >> users;
        // read users
        REP(i, users) {
            int h;
            cin >> h;
            V[--h].user = true;
            edgeD(h, -1);
        }
        // read streets
        REP(i, m) {
            int u, v;
            cin >> u >> v;
            edgeU(--u, --v);
        }        
        int l = 1;
        //int m = 250;
        int r = 499;
        //cout << "SOlve" << endl;
        int flow = 0;
        while (l != r) {
            REP(i, n) {
                V[i].reset(l);
            }
            flow += maxFlow(n);
            
            //cout << "c: " << l << ", flow: " << flow << endl; 
            if (flow == users) {
                cout << l << endl;
                break;
            }
            l++;
            /*
            if (result < h) {
                l = m;
                m = (l+r) / 2;
            } else {
                if (result == h) {
                    cout << m << endl;
                    break;
                }
                if (result >= h) {
                    r = m;
                    m = (l+r) / 2;
                }
            }*/
        }        
    }
    
    Vertex V[N];    
};

int main(void) {
    int t;
    cin >> t;
    while (t--) {
        Graph<500> g;
        g.solve();        
    }
    return 0;
}
