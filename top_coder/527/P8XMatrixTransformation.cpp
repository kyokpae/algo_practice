#include <string>
#include <vector>

using namespace std;

#define FOR(x, b, e) for (int x = b; x <= (e); ++x)
#define FORD(x, b, e) for (int x = b; x >= (e); --x)
#define REP(x, n) for (int x = 0; x < (n); x++)
#define VAR(v, n) __typeof(n) v=(n)
#define FOREACH(i, c) for ( VAR(i, (c).begin()); i != (c).end(); ++i)

class P8XMatrixTransformation {
public:
    string solve(vector<string>& A, vector<string>& B) {
        int count_a = 0;
        FOREACH(a, A) {
            REP(i, (*a).size()) {
                count_a += ((*a)[i] == '1');
            }
        }
        int count_b = 0;
        FOREACH(b, B) {
            REP(i, (*b).size()) {
                count_b += ((*b)[i] == '1');
            }
        }
        return (count_a == count_b) ? "YES" : "NO";
    }
};

int main(void) {
    
}
