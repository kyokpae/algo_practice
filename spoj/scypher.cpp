// http://www.spoj.pl/problems/SCYPHER/
#include <iostream>
#include <cstring>

using namespace std;

#define FORD(x, b, e) for (int x = b; x >= (e); --x)
#define REP(x, n) for (int x = 0; x < (n); ++x)

bool E[26][26];
int V[26];
int d[26];
int res[26];
bool ok[26];
int subst[26];
int isubst[26];
int topo[26];
int a;

void dfsTopo(int u, int& order) {
    V[u] = 1;
    REP(v, 26) {
        if (E[u][v]) {
            if (V[v] == 0) {
                dfsTopo(v, order);
            }
        }
    }
    isubst[25-order] = u;
    subst[u] = 25 - order;
    order++;
}

int dfsCount(bool e[26][26], int u) {
    V[u] = 1;
    REP(v, 26) {
        if (e[u][v]) {
            if (!V[v]) {
                d[v]++;                
                V[u] += dfsCount(e, v);
            }
        }
    }
    return V[u];
}

int main(void) {
    int n;
    cin >> n;
    while (n--) {
        int k;
        cin >> a >> k;

        char buf[2][2000000];
        char * curr = &buf[0][0];
        char * prev = &buf[1][0];
        prev[0] = 0;
        int prev_l = 0;

        cin.getline(curr, 2000000);
        memset(E, 0, sizeof(E));
        memset(V, 0, sizeof(V));
        memset(d, 0, sizeof(d));
        memset(ok, 0, sizeof(ok));
        memset(res, 0, sizeof(res));

        REP(i, 26) {
            subst[i] = i;
            isubst[i] = i;
            if (i >= a && i < 25) {
                E[i][i+1] = true;
            } else if (i < a && a < 26) {
                E[i][a] = true;
            }
        }

        REP(i, k) {
            curr = buf[i % 2];
            cin.getline(curr, 2000000);
            int c = 0;
            while (curr[c] && curr[c] == prev[c]) {
                c++;
            }
            if (prev[c] && curr[c] && prev[c] >= 'a' && curr[c] >= 'a' && prev[c] <= 'z' && curr[c] <= 'z') {
                int u = prev[c] - 'a';
                int v = curr[c] - 'a';
                E[u][v] = true;
            }
            prev = curr;
        }

        int order = 0;
        REP(v, 26) {
            if (!V[v]) {
                dfsTopo(v, order);
            }
        }
        int A = 0;
        bool stop = false;
        REP(v, 26) {
            memset(V, 0, sizeof(V));
            res[v] = 26 - dfsCount(E, isubst[v]);
        }
        int Z = 26;
        REP(v, 26) {
            ok[v] = (res[v] == v && d[isubst[v]] == v);
        }
        cin.getline(curr, 2000000);

        bool hopeless = false;
        int i = 0;
        while (curr[i]) {
            if (curr[i] >= 'a' && curr[i] <= 'z') {
                int enc = curr[i] - 'a';
                int dec = subst[enc];
                if (ok[dec]) {
                    curr[i] = 'a' + dec;
                } else {
                    hopeless = true;
                }
            }
            i++;
        }
        if (hopeless) {
            cout << "Message cannot be decrypted.";
        } else {
            cout << curr;
        }
        cout << endl;
    }
    return 0;
}
