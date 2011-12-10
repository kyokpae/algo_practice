// http://www.spoj.pl/problems/BENEFACT/
#include <iostream>
#include <vector>

using namespace std;

#define REP(x, n) for (int x = 0; x < (n); x++)
#define VAR(v, n) __typeof(n) v=(n)
#define FOREACH(i, c) for ( VAR(i, (c).begin()); i != (c).end(); ++i)

struct Edge {
    Edge(int v, int l) : v(v), l(l) {}
    int v;
    int l;
};

struct Vertex {
    int L;
    vector<Edge> E;
};

Vertex M[50000];
int tentative;

struct Frame {
    Frame(int u, int l) : u(u), l(l), e(0), l1(0), l2(0) { M[u].L = 0;}
    int u, e, l, l1, l2;
};

int visit(int u, int l) {
    int l1 = 0;
    int l2 = 0;
    M[u].L = 0;
    FOREACH(e, M[u].E) {
        if (M[e->v].L == -1) {
            int L = visit(e->v, e->l);
            if (L > l1) {
                l2 = l1;
                l1 = L;
            } else if (L > l2) {
                l2 = L;
            }
            if (l1 + l2 > tentative) {
                tentative = l1 + l2;
            }
        }
    }
    M[u].L = l1 + l;
    return M[u].L;
}

vector<Frame> stack;

inline int dfs(int u) {
    stack.clear();
    stack.push_back(Frame(u, 0));
    int end = 0;
    while (end >= 0) {
        int here = end;
        Frame& frame = stack[end];
        int& u = frame.u;
        int& e = frame.e;        
        if (e == M[u].E.size()) {
            int L = frame.l1 + frame.l;
            M[u].L = L;
            stack.pop_back();
            end--;
            if (!stack.empty()) {
                Frame& frame = stack.back();
                int& l1 = frame.l1;
                int& l2 = frame.l2;
                if (L > l1) {
                    l2 = l1;
                    l1 = L;
                } else if (L > l2) {
                    l2 = L;
                }
                if (l1 + l2 > tentative) {
                    tentative = l1 + l2;
                }
            }
            continue;
        }
        Edge& ed = M[u].E[e];
        if (M[ed.v].L == -1) {
            stack.push_back(Frame(ed.v, ed.l));
            end++;
        }
        stack[here].e++;
    }
}

int main(void) {
    int t;
    cin >> t;
    stack.reserve(50000);
    REP(i, 50000) {
        M[i].E.reserve(10);
    }
    while (t--) {
        int n;
        cin >> n;

        // reset data structures
        tentative = 0;
        REP(i, n) {
            M[i].L = -1;
            M[i].E.clear();
        }

        // read input
        int start;
        REP(i, n - 1) {
            int u, v, l;
            cin >> u >> v >> l;
            u--;
            v--;
            M[u].E.push_back(Edge(v, l));
            M[v].E.push_back(Edge(u, l));
        }

        // solve
        REP (i, n) {
            if (M[i].L == -1) {
                dfs(i);
            }
        }
        cout << tentative << endl;
    }
    return 0;
}
