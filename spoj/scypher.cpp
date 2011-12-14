// http://www.spoj.pl/problems/SCYPHER/
#include <cstdio>
#include <cstring>

using namespace std;

#define FORD(x, b, e) for (int x = b; x >= (e); --x)
#define REP(x, n) for (int x = 0; x < (n); ++x)

bool E[26][26];
char V[26];
char d[26];
char res[26];
bool ok[26];
char subst[26];
char isubst[26];
char topo[26];
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
    REP(v, a) {
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
    scanf("%d", &n);
    while (n--) {
        int k;
        scanf("%d %d", &a, &k);

        char buf[2][100000];
        char * curr = &buf[0][0];
        char * prev = &buf[1][0];
        prev[0] = 0;
        int prev_l = 0;

        gets(curr);

        memset(E, 0, sizeof(E));
        memset(V, 0, sizeof(V));

        REP(i, 26) {
            subst[i] = i;
            isubst[i] = i;
            res[i] = 0;
            ok[i] = 0;
            d[i] = 0;
            if (i >= a && i < 25) {
                E[i][i+1] = true;
            } else if (i < a && a < 26) {
                E[i][a] = true;
            }
        }

        REP(i, k) {
            curr = buf[i % 2];
            gets(curr);
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
        REP(v, a) {
            if (!V[v]) {
                dfsTopo(v, order);
            }
        }
        REP(v, a) {
            memset(V, 0, sizeof(V));
            res[v] = a - dfsCount(E, isubst[v]);
        }
        REP(v, 26) {
            if (v >= a) {
                ok[v] = true;
            } else {
                ok[v] = (res[v] == v && d[isubst[v]] == v);
            }
        }
        gets(curr);

        bool hopeless = false;
        int i = 0;
        char c;
        while ((c = curr[i]) && !hopeless) {
            if (c >= 'a' && c <= 'z') {
                int enc = c - 'a';
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
            printf("Message cannot be decrypted.\n");
        } else {
            printf("%s\n", curr);
        }
    }
    return 0;
}
