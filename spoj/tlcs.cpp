// http://www.spoj.pl/problems/TLCS/
#include <cstdio>

using namespace std;

inline int max(int a, int b) {
    return (a > b) ? a : b;
}

class LCS {
public:
    // constructor
    LCS ( int tc, const char * A, const char * B, const int m, const int n ) :
        tc ( tc ),
        A ( A ),
        B ( B ),
        m ( m ),
        n ( n )
    {
        // solve LCS problem
        L [m] [n] = 0;
        // zero last row
        for ( int i = 0; i < n; i++) {
            L [m] [i] = 0;
        }
        for ( int i = m - 1; i >= 0; i--) {
            // zero last column
            L [i] [n] = 0;
            for ( int j = n - 1; j >= 0; j--) {
                if ( A [i] == B [j] ) {
                    // trailing letter of LCS present at the end of A and B string
                    L [i] [j] = 1 + L [i+1] [j+1];
                } else {
                    // trailing letters differ, only one of them can be part of LCS at most
                    L [i] [j] = max ( L[i+1] [j], L[i] [j+1] );
                }
            }
        }
    }

    void report () {
        int i = 0;
        int j = 0;
        printf("case %d %c\n", tc, (( hasSolution () ) ? 'Y' : 'N' ));
        if ( hasSolution () ) {
            printf("%d\n", length() );
            while ( i < m && j < n ) {
                if ( A [i] == B [j] ) {
                    printf("%c %d %d\n", A [i], i + 1, j + 1);
                    i++;
                    j++;
                } else {
                    (L [i+1] [j] >= L [i] [j+1] ) ? i++ : j++;
                }
            }
        }
    }
           
    bool hasSolution () const {
        return length() > 0;
    }
    
    int length () const {
        return L [0][0];
    }
    
    static void initMatrix () {
        LCS::L = new short * [1001];
        for ( int i = 0; i <= 1001; i++ ) {
            LCS::L [i] = new short [1001];
        }
    }

private:
    int tc;
    const char * A;
    const char * B;
    int m;
    int n;
    static short ** L;
};

short ** LCS::L;

int main ( void ) {
    // init matrix
    LCS::initMatrix ();
    
    int n = 0;
    scanf("%d", &n);
    for ( int i = 1; i <= n; i++ ) {
        char a [1001];
        char b [1001];
        int m, n;
        scanf("%d %s", &m, a);
        scanf("%d %s", &n, b);
        // find lcs
        LCS lcs ( i, a, b, m, n );
        lcs.report ();
    }

    return 0;
}
