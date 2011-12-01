#include <string>
#include <vector>

using namespace std;

#define REPi(from, to) for (int i=from; i<to; i++)
#define REPj(from, to) for (int j=from; j<to; j++)

class RainyRoad {
public:
    string isReachable(vector<string>& road) {
        REPi(0, road[0].size()) {
            if (road[0][i] == 'W' && road[1][i] == 'W') {
                return "NO";
            }
        }
        return "YES";
    }
};
